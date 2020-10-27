#include "MainPrompt.h"
#include <iostream>
#include <sstream>
#include "exceptions.h"
#include <typeinfo>

#include "book_tags.h"
#include "operation_tags.h"

Tag* MainPrompt::GetTag(const std::string str) const
{
	if (str == ":title:") {
		return new Title();
	}
	else if (str == ":author:") {
		return new Author();
	}
	else if (str == ":publisher:") {
		return new Publisher();
	}
	else if (str == ":date:") {
		return new Date();
	}
	else if (str == ":id:") {
		return new ID();
	}
	else if (str == ":add:") {
		return new Add();
	}
	else if (str == ":edit:") {
		return new Edit();
	}
	else if (str == ":del:") {
		return new Del();
	}
	else if (str == ":clear:") {
		return new Clear();
	}
	else if (str == ":exit:") {
		return new Exit();
	}
	else if (str == ":page:") {
		return new Page()
	}
	else if (str == ":help:") {
		return new Help();
	}
	throw InvalidTag(str.c_str());
}

void MainPrompt::Prompt()
{
	// ������Ʈ ���
	std::cout << "���� ������ �˻��ϰų� �����ϱ� ���� ������ �Է��ϼ���.\n\nBooking:������Ʈ>";
	std::getline(std::cin, _raw_input);

	// �Է� ���ڿ��� ���� ��Ģ �˻�
	if (_raw_input.empty()) {
		throw InvalidInput(_raw_input.c_str());
	}
	if (_raw_input.length() >= 2) {
		for (unsigned int i = 0; i < _raw_input.length(); i++) {
			if (_raw_input.at(i) < ' ' || _raw_input.at > '~') {
				throw InvalidInput(_raw_input.c_str());
			}
			if (i > 0) {
				if (_raw_input.at(i - 1) == ' ' && _raw_input.at(i) == ' ') {
					throw InvalidInput(_raw_input.c_str());
				}
			}

		}
	}

	// ������ ��ġ�� :title: ����
	std::stringstream ss(_raw_input);
	std::string token;
	bool tag_found = false;
	while (ss >> token) {
		if (Tag::is_tag(token)) {
			tag_found = true;
		}
	}
	if (!tag_found) {
		ss.str(_raw_input);
		ss.clear();
		_raw_input = ":title: " + _raw_input + " :";
		while (ss >> token) {
			token = ":title: " + token + " :";
			if (_raw_input.find(token) != std::string::npos) {
				_raw_input = _raw_input.substr(0, _raw_input.length() - 1) + token;
			}
		}
		_raw_input = _raw_input.substr(0, _raw_input.length() - 2);
	}

	// ���ڿ� -> �±� ����
	ss.str(_raw_input);
	ss.clear();
	_input_bundle = TagBundle();
	Tag* current_tag;
	while (ss >> token) {
		if (Tag::is_tag(token)) {
			if (current_tag != nullptr) {
				_input_bundle.tags.push_back(current_tag);
			}
			current_tag = GetTag(token);
		}
		else {
			if (current_tag == nullptr) {
				throw InvalidInput(_raw_input.c_str());
			}
			(*current_tag) << token;
		}
	}
	if (current_tag != nullptr) {
		_input_bundle.tags.push_back(current_tag);
	}

	// �±� ������ ��Ģ �˻�
	_input_bundle.Validate();
	if (_input_bundle.tags.empty()) {	// �±� ������ ����ִ� ���
		throw InvalidInput(_raw_input.c_str());
	}
	TagBundle operation_tags = _input_bundle.GetTagByType<OperationTag>();
	TagBundle book_tags = _input_bundle.GetTagByType<BookTag>();
	if (operation_tags.tags.size() > 1) {	// ��� �±װ� ���� ���� ���
		throw MultipleOperationTags();
	}
	else if (operation_tags.tags.size() == 1) {	// ��� �±װ� �� ���� ���
		const type_info& operation_type = typeid(*(operation_tags.tags.at(0)));
		OperationTag* operation_tag = (OperationTag*)operation_tags.tags.at(0);
		bool title_found = _input_bundle.GetTagByType<Title>().tags.size();
		bool author_found = _input_bundle.GetTagByType<Author>().tags.size();
		bool publisher_found = _input_bundle.GetTagByType<Publisher>().tags.size();
		bool date_found = _input_bundle.GetTagByType<Date>().tags.size();
		if (operation_type == typeid(Add)) {	// :add:�� ���� �� �ٸ� ���� �±װ� ���� ���
			if (!(title_found && author_found && publisher_found && date_found)) {
				throw NeedEveryBookTag();
			}
		}
		else if (operation_type == typeid(Edit)) {	// :edit:�� ���� ��
			if (!(title_found || author_found || publisher_found || date_found)) {	// �ٸ� ���� �±װ� ���� ���
				throw NeedOneOrMoreBookTag();
			}
			_entire_books.IdSearch(operation_tags.tags.at(0));	// ������ id�� �������� �ʴ� ���
		}
		else if (operation_type == typeid(Del)) {	// :del:�� ���� �� ������ id�� �������� �ʴ� ���
			_entire_books.IdSearch(operation_tags.tags.at(0));
		}
		else if (operation_type == typeid(Page)) {
			// �������� �����ϴ��� Ȯ���ؾ� ��
		}
	}
	TagBundle id_tags = book_tags.GetTagByType<ID>();
	for (unsigned int i = 0; i < id_tags.tags.size(); i++) {	// :id:�� ���� �� ������ id�� �������� �ʴ� ���
		_entire_books.IdSearch(id_tags.tags.at(i));
	}

	// �Է¿� ���� ó��
	if (operation_tags.tags.empty()) {
		_entire_books.search(_input_bundle);	// �̰� �´��� Ȯ���ؾ� ��
	}
	else {
		((OperationTag*)operation_tags.tags.at(0))->Operate(*this);
	}
}
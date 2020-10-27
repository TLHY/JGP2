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
	// 프롬프트 출력
	std::cout << "도서 정보를 검색하거나 관리하기 위한 구문을 입력하세요.\n\nBooking:프롬프트>";
	std::getline(std::cin, _raw_input);

	// 입력 문자열의 문법 규칙 검사
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

	// 적절한 위치에 :title: 삽입
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

	// 문자열 -> 태그 번들
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

	// 태그 번들의 규칙 검사
	_input_bundle.Validate();
	if (_input_bundle.tags.empty()) {	// 태그 번들이 비어있는 경우
		throw InvalidInput(_raw_input.c_str());
	}
	TagBundle operation_tags = _input_bundle.GetTagByType<OperationTag>();
	TagBundle book_tags = _input_bundle.GetTagByType<BookTag>();
	if (operation_tags.tags.size() > 1) {	// 명령 태그가 여러 개인 경우
		throw MultipleOperationTags();
	}
	else if (operation_tags.tags.size() == 1) {	// 명령 태그가 한 개인 경우
		const type_info& operation_type = typeid(*(operation_tags.tags.at(0)));
		OperationTag* operation_tag = (OperationTag*)operation_tags.tags.at(0);
		bool title_found = _input_bundle.GetTagByType<Title>().tags.size();
		bool author_found = _input_bundle.GetTagByType<Author>().tags.size();
		bool publisher_found = _input_bundle.GetTagByType<Publisher>().tags.size();
		bool date_found = _input_bundle.GetTagByType<Date>().tags.size();
		if (operation_type == typeid(Add)) {	// :add:가 사용될 때 다른 도서 태그가 없는 경우
			if (!(title_found && author_found && publisher_found && date_found)) {
				throw NeedEveryBookTag();
			}
		}
		else if (operation_type == typeid(Edit)) {	// :edit:이 사용될 때
			if (!(title_found || author_found || publisher_found || date_found)) {	// 다른 도서 태그가 없는 경우
				throw NeedOneOrMoreBookTag();
			}
			_entire_books.IdSearch(operation_tags.tags.at(0));	// 인자의 id가 존재하지 않는 경우
		}
		else if (operation_type == typeid(Del)) {	// :del:이 사용될 때 인자의 id가 존재하지 않는 경우
			_entire_books.IdSearch(operation_tags.tags.at(0));
		}
		else if (operation_type == typeid(Page)) {
			// 페이지가 존재하는지 확인해야 함
		}
	}
	TagBundle id_tags = book_tags.GetTagByType<ID>();
	for (unsigned int i = 0; i < id_tags.tags.size(); i++) {	// :id:가 사용될 때 인자의 id가 존재하지 않는 경우
		_entire_books.IdSearch(id_tags.tags.at(i));
	}

	// 입력에 대한 처리
	if (operation_tags.tags.empty()) {
		_entire_books.search(_input_bundle);	// 이게 맞는지 확인해야 함
	}
	else {
		((OperationTag*)operation_tags.tags.at(0))->Operate(*this);
	}
}
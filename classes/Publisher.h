#pragma once
#include <iostream>
#include "tag_parents.h"
#include <vector>
#include "exceptions.h"
using namespace std;
class Publisher :public BookTag {
public:
	Tag* copy() const;
	string get_Publisher();
	void Validate();
	void Print() const;
	bool Match(const BookTag* search) const;
};
Tag* Publisher::copy() const {
	return new Publisher(*this);
}
string Publisher::get_Publisher() {
	return this->strarg();
}
void Publisher::Validate(){
	/*���� ����: ���������� �ùٸ� ���ǻ������ �Ʒ� ������ ��� ���� ��Ű�� ���ڿ��Դϴ�.
		�ǻ� ���ڿ� ���� ���ڷ� �̷���� ���̰� 1 �̻��� ���ڿ�
		�ǻ� ���ڰ� �� �� �̻� ���Ե� ���ڿ�
		ù ���ڿ� ������ ���ڰ� �ǻ� ������ ���ڿ�
		���� ���ڰ� ���ԵǴ� ��� ������ �ٷ� �հ� �ڿ� ���� ���ڰ� �ǻ� ������ ���ڿ�*/

	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	// 6.2.3. �˻�
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	int blanks = 0;	// ������ ��
	for (int i = 0; i < _strarg.length(); i++) {
		char c = _strarg.at(i);
		blanks += blanks == ' ';
		if (c < ' ' || c > '~') {	// �ƽ�Ű �ڵ忡�� SP���� ~������ �ǻ� ���ڿ� �ش��մϴ�.
			throw InvalidArgument(this);
		}
		if (i > 0 && i < _strarg.length() - 1) {
			if (c == ' ' && (_strarg.at(i - 1) == ' ' || _strarg.at(i + 1) == ' ')) {
				throw InvalidArgument(this);
			}
		}
	}
	if (blanks == _strarg.length()) {
		throw InvalidArgument(this);
	}
}
void Publisher::Print() const {
	std::cout << ":publisher: " << _strarg;
}
bool Publisher::Match(const BookTag* search) const {
	std::string my_arg = _strarg;
	std::string search_arg = search->strarg();
	// ���ڿ��� ��� �ҹ��ڷ� ������ �� �˻�
	std::transform(my_arg.begin(), my_arg.end(), my_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	std::transform(search_arg.begin(), search_arg.end(), search_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	return my_arg.find(search_arg) != std::string::npos;
}



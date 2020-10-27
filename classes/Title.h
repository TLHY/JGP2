#pragma once
#include <iostream>
#include "tag_parents.h"
#include <vector>
#include "exceptions.h"
using namespace std;

class Title :public BookTag {
public:
	string get_Title();
	Tag* copy() const;
	void Validate();
	void Print() const;
	bool Match(const BookTag* search) const;
};
Tag* Title::copy() const {
	return new Title(*this);
}
string Title::get_Title() {
	return this->strarg();
}
void Title::Validate(){
	/*���� ���� : ���������� �ùٸ� �������� �Ʒ� ������ ��� ���� ��Ű�� ���ڿ��Դϴ�.
		�ǻ� ���ڿ� ���� ���ڷ� �̷���� ���̰� 1 �̻��� ���ڿ�
		�ǻ� ���ڰ� �� �� �̻� ���Ե� ���ڿ�
		ù ���ڿ� ������ ���ڰ� �ǻ� ������ ���ڿ�
		���� ���ڰ� ���ԵǴ� ��� ������ �ٷ� �հ� �ڿ� ���� ���ڰ� �ǻ� ������ ���ڿ�*/
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
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
		// 6.2.4. �˻�
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
void Title::Print() const {
	std::cout << ":title: " << _strarg;
}
bool Title::Match(const BookTag* search) const {
	std::string my_arg = _strarg;
	std::string search_arg = search->strarg();
	// ���ڿ��� ��� �ҹ��ڷ� ������ �� �˻�
	std::transform(my_arg.begin(), my_arg.end(), my_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	std::transform(search_arg.begin(), search_arg.end(), search_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	return my_arg.find(search_arg) != std::string::npos;

}



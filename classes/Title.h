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
	/*문법 형식 : 문법적으로 올바른 도서명은 아래 조건을 모두 만족 시키는 문자열입니다.
		실상 문자와 공백 문자로 이루어진 길이가 1 이상인 문자열
		실상 문자가 한 개 이상 포함된 문자열
		첫 문자와 마지막 문자가 실상 문자인 문자열
		공백 문자가 포함되는 경우 공백의 바로 앞과 뒤에 오는 문자가 실상 문자인 문자열*/
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	int blanks = 0;	// 공백의 수
	for (int i = 0; i < _strarg.length(); i++) {
		char c = _strarg.at(i);
		blanks += blanks == ' ';
		if (c < ' ' || c > '~') {	// 아스키 코드에서 SP부터 ~까지가 실상 문자에 해당합니다.
			throw InvalidArgument(this);
		}
		// 6.2.4. 검사
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
	// 문자열을 모두 소문자로 변경한 뒤 검사
	std::transform(my_arg.begin(), my_arg.end(), my_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	std::transform(search_arg.begin(), search_arg.end(), search_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	return my_arg.find(search_arg) != std::string::npos;

}



#pragma once
#include <iostream>
#include "tag_parents.h"
#include <vector>
#include "exceptions.h"
#include <regex>
using namespace std;
class Date :public BookTag {
public:
	Tag* copy() const;
	string get_Date();
	void Validate();
	void Print() const;
	bool Match(const BookTag* search) const;
};
Tag* Date::copy() const {
	return new Date(*this);
}
string Date::get_Date() {
	return this->strarg();
}
void Date::Validate(){
	/*문법 형식 : 문자 d가 아무 숫자에 대응되는 문자일 때, 문법적으로 올바른 출판년도는 다음 네가지 형식에 부합하는 문자열입니다 :
		1ddd
		200d
		201d
		2020
		*/
	try {
		int a = stoi(_strarg);
		_intarg = a;
	}
	catch (const std::out_of_range& e) {
		throw InvalidArgument(this);
	}
	if (_strarg.empty() || _strarg.length() != 4) {
		throw InvalidArgument(this);
	}
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	if (_intarg > 2020 || _intarg < 1900) {
		throw InvalidArgument(this);
	}
}
void Date::Print() const {
	std::cout << ":date: " << _strarg;
}
bool Date::Match(const BookTag* search) const {
	std::string my_arg = _strarg;
	std::string search_arg = search->strarg();
	// 문자열을 모두 숫자로 변경한 뒤 검사
	int my_num = stoi(my_arg);
	int search_num = stoi(search_arg);
	return my_num != search_num;
}



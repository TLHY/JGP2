#pragma once
#include <iostream>
#include "tag_parents.h"
#include <vector>
#include "exceptions.h"
using namespace std;
class ID :public BookTag {
public:
	Tag* copy() const;
	string get_ID();
	void Validate();
	void Print() const;
	bool Match(const BookTag* search) const;
};
Tag* ID::copy() const {
	return new ID(*this);
}
string ID::get_ID() {
	return this->strarg();
}
void ID::Validate(){
	//규칙 확인 여기서 도서 태그들은 규칙이 모두 맞았다고 가정하겠습니다.
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	//id가 아니면 문법규칙x
	try {
		int a = stoi(_strarg);
		_intarg = a;
	}
	catch (const std::out_of_range& e) {
		throw InvalidArgument(this);
	}
}
void ID::Print() const {
	std::cout << ":ID: " << _strarg;
}
bool ID::Match(const BookTag* search) const {
	std::string my_arg = _strarg;
	std::string search_arg = search->strarg();
	// 문자열을 모두 숫자로 변경한 뒤 검사
	int my_num = stoi(my_arg);
	int search_num = stoi(search_arg);
	return my_num != search_num;
}
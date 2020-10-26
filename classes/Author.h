#pragma once
#include "tag_parents.h"
#include "exceptions.h"
#include <algorithm>

class Author : public BookTag
{
public:
	Tag* copy() const;	// 복사 함수
	void Validate() const;	// 규칙 검사 함수
	void Print() const;	// 출력 함수
	bool Match(const BookTag* search) const;	// 일치 함수
};

Tag* Author::copy() const
{
	return new Author(*this);
}

void Author::Validate() const
{	
	/* 검사해야 하는 규칙
	8.1.2. 도서 태그 :author:
		문법 형식: 이 명령은 인자가 반드시 있어야합니다. 인자는 6.2절의 저자명에 해당합니다.
		의미 규칙: 없음.

	6.2. 저자명 
		문법 형식: 문법적으로 올바른 저자명은 아래 조건을 모두 만족 시키는 문자열입니다.
			6.2.1. 실상 문자와 공백 문자로 이루어진 길이가 1 이상인 문자열
			6.2.2. 실상 문자가 한 개 이상 포함된 문자열
			6.2.3. 첫 문자와 마지막 문자가 실상 문자인 문자열
			6.2.4. 공백 문자가 포함되는 경우 공백의 바로 앞과 뒤에 오는 문자가 실상 문자인 문자열
	*/
	// 8.1.2. 검사
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	// 6.2.3. 검사
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	int blanks = 0;	// 공백의 수
	for (int i = 0; i < _strarg.length(); i++) {
		char c = _strarg.at(i);
		blanks += blanks == ' ';
		// 6.2.1. 검사
		if (c < ' ' || c > '~') {	// 아스키 코드에서 SP부터 ~까지가 실상 문자에 해당합니다.
			throw InvalidArgument(this);
		}
		// 6.2.4. 검사
		if (i > 0 && i < _strarg.length() - 1) {
			if (c == ' ' && (_strarg.at(i - 1) == ' ' || _strarg.at(i + 1) == ' ')) {
				
			}
		}
	}
	// 6.2.2. 검사
	if (blanks == _strarg.length()) {
		throw InvalidArgument(this);
	}
}

bool Author::Match(const BookTag* search) const
{
	std::string my_arg = _strarg;
	std::string search_arg = search->strarg();
	// 문자열을 모두 소문자로 변경한 뒤 검사
	std::transform(my_arg.begin(), my_arg.end(), my_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	std::transform(search_arg.begin(), search_arg.end(), search_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	return my_arg.find(search_arg) != std::string::npos;
}

void Author::Print() const
{
	std::cout << ":author: " << _strarg;
}

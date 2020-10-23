#pragma once
#include "BookTag.h"

// !!! 이 클래스는 사용 예시를 위해 만든 테스트용 클래스로 구현물에 사용할 수 없으니 참고만 해주세요 !!!
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
	/* 규칙 검사
		실제 구현시에는 여기에 인자의 문법 규칙과 의미 규칙을 검사하는 부분이 들어갑니다.
		규칙을 검사하다가 위반을 발견하면 예외를 발생시켜야 합니다.
	*/ 
}

bool Author::Match(const BookTag* search) const
{
	return false;
}

void Author::Print() const
{
	std::cout << ":author: " << _strarg;
}

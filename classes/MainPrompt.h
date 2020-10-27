#pragma once
#include <string>
#include "TagBundle.h"

class BookList {};

class MainPrompt
{
private:
	BookList _entire_books;
	BookList _searched_books;
	std::string _raw_input;
	TagBundle _input_bundle;

	/* 문자열에 해당하는 태그를 동적할당하여 반환하는 함수
		올바르지 않은 문자열을 인자로 전달하면 예외를 발생시킵니다.
	*/
	Tag* GetTag(const std::string str) const;

public:
	/* 주 프롬프트 실행 함수
		사용자로부터 문자열을 입력받아 검사, 해석, 처리를 하는 함수입니다.
	*/
	void Prompt();
};



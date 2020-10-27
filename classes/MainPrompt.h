#pragma once
#include <string>
#include "TagBundle.h"
#include "FileIO.h"

class BookList {};

class MainPrompt
{
private:
	BookList _entire_books;
	BookList _searched_books;
	std::string _raw_input;
	TagBundle _input_bundle;
	File _file;

	/* 문자열에 해당하는 태그를 동적할당하여 반환하는 함수
		올바르지 않은 문자열을 인자로 전달하면 예외를 발생시킵니다.
	*/
	Tag* GetTag(const std::string str) const;

public:
	// 생성자
	MainPrompt();

	// 멤버 변수 접근 함수
	BookList& entire_books() { return _entire_books; };
	BookList& searched_books() { return _searched_books; };
	std::string& raw_input() { return _raw_input; };
	TagBundle& input_bundle() { return _input_bundle; };

	/* 주 프롬프트 실행 함수
		사용자로부터 문자열을 입력받아 검사, 해석, 처리를 하는 함수입니다.
	*/
	void Prompt();
};



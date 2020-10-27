#pragma once
#include <iostream>
#include <vector>
#include "tag_parents.h"
#include "book_tags.h"
#include "operation_tags.h"
#include <string>
using namespace std;
class Del :public OperationTag {
public:
	Tag* copy() const;
	void Validate();
	void Print() const;
	void Operate(MainPrompt& main_prompt);
};
Tag* Del::copy() const {
	return new Del(*this);
}
void Del::Validate(){
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
	catch(const std::out_of_range& e){
		throw InvalidArgument(this);
	}
}
void Del::Print() const {
	cout <<":Del: "<<_intarg << _strarg << endl;
}
void Del::Operate(MainPrompt& main){
	main.entire_books().DelOP(main.input_bundle());
}
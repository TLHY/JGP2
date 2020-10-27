#pragma once
#include <iostream>
#include <vector>
#include "tag_parents.h"
#include "book_tags.h"
#include "TagBundle.h"
#include "MainPrompt.h"

class Add:public OperationTag{
public:
	Tag* copy() const;
	void Validate();
	void Print() const;
	void Operate(MainPrompt& main_prompt);
};
Tag* Add::copy() const {
	return new Add(*this);
}
void Add::Validate(){
	if (!_strarg.empty()) {
		throw InvalidArgument(this);
	}
}
void Add::Print() const{
	cout << _strarg << "added" << endl;
}
void Add::Operate(MainPrompt& main){
	main.entire_books().AddOP(main.input_bundle());
} 

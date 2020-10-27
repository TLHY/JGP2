#pragma once
#include <iostream>
#include <vector>
#include "exceptions.h"
using namespace std;
class Exit :public OperationTag {
public:
	Tag* copy() const;
	void Validate();
	void Print() const;
	void Operate(MainPrompt& main_prompt);
};
Tag* Exit::copy() const {
	return new Exit(*this);
}
void Exit::Validate() {
	if (!_strarg.empty()) {
		throw InvalidArgument(this);
	}
}
void Exit::Print() const {
	cout << ":Exit:" << endl;
}
void Exit::Operate(MainPrompt& main) {
	terminate();
}

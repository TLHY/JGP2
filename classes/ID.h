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
	//��Ģ Ȯ�� ���⼭ ���� �±׵��� ��Ģ�� ��� �¾Ҵٰ� �����ϰڽ��ϴ�.
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	//id�� �ƴϸ� ������Ģx
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
	// ���ڿ��� ��� ���ڷ� ������ �� �˻�
	int my_num = stoi(my_arg);
	int search_num = stoi(search_arg);
	return my_num != search_num;
}
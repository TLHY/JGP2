#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "tag_parents.h"
#include <string>
#include "book.h"

using namespace std;
class Clear :public OperationTag {
public:
	void Operate();
	void Operate(vector<Book*> book) const;
	Tag* copy() const;
	void Validate() const;
	void Validate(vector<Book*> book) const;
	void Print() const;
};
Tag* Clear::copy() const {
	return new Clear(*this);
}
void Clear::Operate() {

}
void Clear::Validate() const {

}
void Clear::Print() const {

}
void Clear::Validate(vector<Book*> book) const {
	try {
		if (book.empty()) {
			Clear c;
			throw ResultNotFound(&c);
		}
		else {
		}
	}
	catch (ResultNotFound& e) {
		cout << e.what() << endl;
	}
}
void Clear::Operate(vector<Book*> book) const {
	Validate(book);
	book.erase(book.begin(), book.end());
}
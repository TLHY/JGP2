#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "tag_parents.h"
#include <string>
#include "book.h"

using namespace std;
class Page :public OperationTag {
public:
	void Operate();
	void Operate(int mpage, vector<Book*> book) const;
	Tag* copy() const;
	void Validate();
	void Validate(int mpage, vector<Book*> book) const;
	void Print() const;
};
Tag* Page::copy() const {
	return new Page(*this);
}
void Page::Operate() {

}
void Page::Validate() {

}
void Page::Print() const {

}
void Page::Validate(int mpage, vector<Book*> book) const {
	try {
		if (mpage > book.size()) {
			Page p;
			throw PageNotFound(&p);
		}
		else {
		}
	}catch (PageNotFound& e) {
		cout << e.what() << endl;
	}catch (InvalidArgument& e) {
		cout << e.what() << endl;
	}catch (ArgumentNotFound& e) {
		cout << e.what() << endl;
	}
}
void Page::Operate(int mpage, vector<Book*> book) const {
	int page = book.size() / 10 + 1;
	Validate(mpage, book);
	cout << "=== 검색 결과(" << book.size() << "개 검색됨, " << mpage << "페이지) ===" << endl;
	cout << "#   도서명 | 저자명 | 출판사명 | 출판년도" << endl;
	if (mpage == page) {
		for (unsigned int j = (mpage - 1) * 10; j < book.size(); j++)
			book[j]->print();
	}
	else {
		for (unsigned int j = (mpage - 1) * 10; j < mpage * 10; j++)
			book[j]->print();
	}
}
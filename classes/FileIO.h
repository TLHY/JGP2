#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>
#include <regex>
#include <conio.h>
#include "Book.h"
using namespace std;

//파일 클래스 헤더

class File {
private:
	string address;
public:
	File() {
	
	}
	File(string a) {
		this->address = a;
	}

	vector<Book*> import_book_list();
	void export_book_list(vector<Book*>bl);
	void export_book_unit(Book* book);
	bool is_Right_Data(string s);
	string get_address() {
		return this->address;
	}
};

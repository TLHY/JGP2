#pragma once
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include "FileIO.h"
#include "book_tags.h"
#include "operation_tags.h"
#include "book.h"
#include "exceptions.h"
#include "TagBundle.h"
#include "Subprompt.h"
#include "page.h"
#include "clear.h"

using namespace std;

class BookList {
public:
	vector<Book*> book;
	vector<TagBundle*> filters;

	//생성자 
	BookList() {};
	BookList(string path) {};

	//검색하기
	vector<Book*> search(TagBundle filters);

	void AddOP(TagBundle* input);

	void EditOP(TagBundle* input);

	void DelOP(TagBundle* input);

	//도서목록찾기
	vector<Book> IdSearch(int ID);

	//수정하기
	void Book_Edit(vector<Book*> book);

	//파괴자 
	~BookList();
};

BookList::BookList(string path) : BookList() {
	File f;
	f.import_book_list().at(0);
	for (int i = 0; i < book.size(); i++) {
		book[i] = &f.import_book_list().at(i);
	}
}

vector<Book*> BookList::search(TagBundle filters) {
	vector<Book*> nbooks;
	vector<int> index;
	int count;
	int hcount = 0;
	int page = 0;
	int n = 0;
	try
	{
		cout << "== = 검색 조건 == =" << endl;
		for (unsigned int i = 0; i < filters.tags.size(); i++) {
			cout << filters.tags[i] << endl;
			cout << filters.tags.at(i) << endl;
		}

		for (unsigned int i = 0; i < book.size(); i++) {
			Title t;
			Author a;
			Publisher p;
			Date d;
			count = 0;
			for (unsigned int i = 0; i < filters.tags.size(); i++) {
				if (t.Match(filters.tags[i])) {
					count++;
				}
				else if (a.Match(filters.tags[i])) {
					count++;
				}
				else if (p.Match(filters.tags[i])) {
					count++;
				}
				else if (d.Match(filters.tags[i])) {
					count++;
				}
			}
			index[i] = count;
			if (hcount < count)
				hcount = count;
		}
		for (unsigned int j = hcount; j > 0; j--) {
			for (unsigned int i = 0; i > book.size(); i++) {
				if (index[i] == j) {
					nbooks[n]->set_ID(book[i]->get_ID());
					nbooks[n]->set_Title(book[i]->get_Title());
					nbooks[n]->set_Author(book[i]->get_Author());
					nbooks[n]->set_Publisher(book[i]->get_Publisher());
					nbooks[n]->set_Date(book[i]->get_Date());
					n++;
				}
			}
		}
		page = nbooks.size() / 10 + 1;
		cout << "=== 검색 결과(" << nbooks.size() << "개 검색됨, " << page << "페이지) ===" << endl;
		cout << "#   도서명 | 저자명 | 출판사명 | 출판년도" << endl;
		for (unsigned int i = 1; i <= page; i++) {
			if (i == page) {
				for (unsigned int j = (page - 1) * 10; j < nbooks.size(); j++)
					nbooks[j]->print();
			}
			else {
				for (unsigned int j = (page - 1) * 10; j < page * 10; j++)
					nbooks[j]->print();
			}
		}
		if (tag[0] == ":clear:") {
			Clear c;
			c.Operate(nbooks);

		}
		else {
			cout << "이전 검색 결과 내에서 검색합니다." << endl;
		}
		if (tag[0] == ":page:") {
			Page p;
			p.Operate(tag->intarg(), nbooks);
		}
		return nbooks;
	}
	catch (IDNotFound& e){
		cout << e.what() << endl;
	}
}

void BookList::AddOP(TagBundle* input) {
	SubPrompt sp;
	SubPrompt("도서 정보를 저장하시겠습니까 ? (Y / N) >");
	if (sp.is_real()) {
		string s;
		int emptyIndex = input->tags[0]->intarg();
		for (int i = 0; i < book.size(); i++) {
			if (book.at(i)->get_ID() == "EMPTY") {
				emptyIndex = i;
				break;
			}
		}
		for (int i = 0; i < input->tags.size(); i++) {
			if (typeid(input->tags[i]) == typeid(ID)) {
				book.at(emptyIndex)->set_ID(to_string(emptyIndex));
			}
			else if (typeid(input->tags[i]) == typeid(Title)) {
				book.at(emptyIndex)->set_Title(input->tags[i]->strarg());
			}
			else if (typeid(input->tags[i]) == typeid(Author)) {
				book.at(emptyIndex)->set_Author(input->tags[i]->strarg());
			}
			else if (typeid(input->tags[i]) == typeid(Publisher)) {
				book.at(emptyIndex)->set_Publisher(input->tags[i]->strarg());
			}
			else if (typeid(input->tags[i]) == typeid(Date)) {
				book.at(emptyIndex)->set_Date(input->tags[i]->strarg());
			}
		}
	}
}
void BookList::EditOP(TagBundle* input) {
	SubPrompt sp;
	SubPrompt("도서 정보를 저장하시겠습니까 ? (Y / N) >");
	if (sp.is_real()) {
		int index = input->tags[0]->intarg() - 1;
		for (int i = 0; i < input->tags.size(); i++) {
			if (typeid(input->tags[i]) == typeid(Title)) {
				book.at(index)->set_Title(input->tags[i]->strarg());
			}
			if (typeid(input->tags[i]) == typeid(Author)) {
				book.at(index)->set_Author(input->tags[i]->strarg());
			}
			if (typeid(input->tags[i]) == typeid(Publisher)) {
				book.at(index)->set_Publisher(input->tags[i]->strarg());
			}
			if (typeid(input->tags[i]) == typeid(Date)) {
				book.at(index)->set_Date(input->tags[i]->strarg());
			}
		}
	}
}
void BookList::DelOP(TagBundle* input) {
	SubPrompt sp;
	SubPrompt("도서 정보를 삭제하시겠습니까 ? (Y / N) >");
	if (sp.is_real()) {
		for (int i = 0; i < input->tags.size(); i++) {
			if (typeid(input->tags[i]) == typeid(ID)) {
				int index = input->tags[i]->intarg() - 1;
				book.at(index)->set_Title("");
				book.at(index)->set_Author("");
				book.at(index)->set_Publisher("");
				book.at(index)->set_Date("");
				book.at(index)->set_ID("EMPTY");
			}
		}
	}
}


vector<Book> BookList::IdSearch(int ID) {
	vector<Book> IdBook;
	IdBook[0].set_Title(book[ID]->get_Title());
	IdBook[0].set_Author(book[ID]->get_Author());
	IdBook[0].set_Publisher(book[ID]->get_Publisher());
	IdBook[0].set_Date(book[ID]->get_Date());
	return IdBook;
}

BookList::~BookList() {
	for (unsigned int i = 0; i < book.size(); i++) {
		delete book.at(i);
	}
}
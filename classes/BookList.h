#pragma once
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include "FileIO.h"
#include "tags.h"
#include "tags2.h"
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

	//������ 
	BookList() {};
	BookList(string path) {};

	//�˻��ϱ�
	vector<Book*> search(TagBundle filters);

	//�������ã��
	vector<Book> IdSearch(int ID);

	//�����ϱ�
	void Book_Edit(vector<Book*> book);

	//�ı��� 
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
		cout << "== = �˻� ���� == =" << endl;
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
		cout << "=== �˻� ���(" << nbooks.size() << "�� �˻���, " << page << "������) ===" << endl;
		cout << "#   ������ | ���ڸ� | ���ǻ�� | ���ǳ⵵" << endl;
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
			cout << "���� �˻� ��� ������ �˻��մϴ�." << endl;
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

void BookList::Book_Edit(vector<Book*> book) {
	SubPrompt sp;
	if (tag[0] == ":add:") {
		SubPrompt("���� ������ �����Ͻðڽ��ϱ� ? (Y / N) >");
		if (sp.is_real()) {
			Add().Operate();
		}
	}
	if (tag[0] == ":edit:"){
		SubPrompt("���� ������ �����Ͻðڽ��ϱ� ? (Y / N) >");
		if (sp.is_real()) {
			edit().Operate();
		}
	}
	if (tag[0] == ":del:") {
		SubPrompt("���� ������ �����Ͻðڽ��ϱ� ? (Y / N) >");
		if (sp.is_real()) {
			Del().Operate();
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
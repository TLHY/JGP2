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

	/* ���ڿ��� �ش��ϴ� �±׸� �����Ҵ��Ͽ� ��ȯ�ϴ� �Լ�
		�ùٸ��� ���� ���ڿ��� ���ڷ� �����ϸ� ���ܸ� �߻���ŵ�ϴ�.
	*/
	Tag* GetTag(const std::string str) const;

public:
	// ������
	MainPrompt();

	// ��� ���� ���� �Լ�
	BookList& entire_books() { return _entire_books; };
	BookList& searched_books() { return _searched_books; };
	std::string& raw_input() { return _raw_input; };
	TagBundle& input_bundle() { return _input_bundle; };

	/* �� ������Ʈ ���� �Լ�
		����ڷκ��� ���ڿ��� �Է¹޾� �˻�, �ؼ�, ó���� �ϴ� �Լ��Դϴ�.
	*/
	void Prompt();
};



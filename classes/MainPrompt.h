#pragma once
#include <string>
#include "TagBundle.h"

class BookList {};

class MainPrompt
{
private:
	BookList _entire_books;
	BookList _searched_books;
	std::string _raw_input;
	TagBundle _input_bundle;

	/* ���ڿ��� �ش��ϴ� �±׸� �����Ҵ��Ͽ� ��ȯ�ϴ� �Լ�
		�ùٸ��� ���� ���ڿ��� ���ڷ� �����ϸ� ���ܸ� �߻���ŵ�ϴ�.
	*/
	Tag* GetTag(const std::string str) const;

public:
	/* �� ������Ʈ ���� �Լ�
		����ڷκ��� ���ڿ��� �Է¹޾� �˻�, �ؼ�, ó���� �ϴ� �Լ��Դϴ�.
	*/
	void Prompt();
};



#pragma once
#include "tag_parents.h"
#include "exceptions.h"
#include <algorithm>

class Author : public BookTag
{
public:
	Tag* copy() const;	// ���� �Լ�
	void Validate() const;	// ��Ģ �˻� �Լ�
	void Print() const;	// ��� �Լ�
	bool Match(const BookTag* search) const;	// ��ġ �Լ�
};

Tag* Author::copy() const
{
	return new Author(*this);
}

void Author::Validate() const
{	
	/* �˻��ؾ� �ϴ� ��Ģ
	8.1.2. ���� �±� :author:
		���� ����: �� ����� ���ڰ� �ݵ�� �־���մϴ�. ���ڴ� 6.2���� ���ڸ� �ش��մϴ�.
		�ǹ� ��Ģ: ����.

	6.2. ���ڸ� 
		���� ����: ���������� �ùٸ� ���ڸ��� �Ʒ� ������ ��� ���� ��Ű�� ���ڿ��Դϴ�.
			6.2.1. �ǻ� ���ڿ� ���� ���ڷ� �̷���� ���̰� 1 �̻��� ���ڿ�
			6.2.2. �ǻ� ���ڰ� �� �� �̻� ���Ե� ���ڿ�
			6.2.3. ù ���ڿ� ������ ���ڰ� �ǻ� ������ ���ڿ�
			6.2.4. ���� ���ڰ� ���ԵǴ� ��� ������ �ٷ� �հ� �ڿ� ���� ���ڰ� �ǻ� ������ ���ڿ�
	*/
	// 8.1.2. �˻�
	if (_strarg.empty()) {
		throw InvalidArgument(this);
	}
	// 6.2.3. �˻�
	if (_strarg.at(0) == ' ' || _strarg.at(_strarg.length() - 1) == ' ') {
		throw InvalidArgument(this);
	}
	int blanks = 0;	// ������ ��
	for (int i = 0; i < _strarg.length(); i++) {
		char c = _strarg.at(i);
		blanks += blanks == ' ';
		// 6.2.1. �˻�
		if (c < ' ' || c > '~') {	// �ƽ�Ű �ڵ忡�� SP���� ~������ �ǻ� ���ڿ� �ش��մϴ�.
			throw InvalidArgument(this);
		}
		// 6.2.4. �˻�
		if (i > 0 && i < _strarg.length() - 1) {
			if (c == ' ' && (_strarg.at(i - 1) == ' ' || _strarg.at(i + 1) == ' ')) {
				
			}
		}
	}
	// 6.2.2. �˻�
	if (blanks == _strarg.length()) {
		throw InvalidArgument(this);
	}
}

bool Author::Match(const BookTag* search) const
{
	std::string my_arg = _strarg;
	std::string search_arg = search->strarg();
	// ���ڿ��� ��� �ҹ��ڷ� ������ �� �˻�
	std::transform(my_arg.begin(), my_arg.end(), my_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	std::transform(search_arg.begin(), search_arg.end(), search_arg.begin(), [](unsigned char c) { return std::tolower(c); });
	return my_arg.find(search_arg) != std::string::npos;
}

void Author::Print() const
{
	std::cout << ":author: " << _strarg;
}

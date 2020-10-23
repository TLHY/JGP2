#pragma once
#include "BookTag.h"

// !!! �� Ŭ������ ��� ���ø� ���� ���� �׽�Ʈ�� Ŭ������ �������� ����� �� ������ ���� ���ּ��� !!!
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
	/* ��Ģ �˻�
		���� �����ÿ��� ���⿡ ������ ���� ��Ģ�� �ǹ� ��Ģ�� �˻��ϴ� �κ��� ���ϴ�.
		��Ģ�� �˻��ϴٰ� ������ �߰��ϸ� ���ܸ� �߻����Ѿ� �մϴ�.
	*/ 
}

bool Author::Match(const BookTag* search) const
{
	return false;
}

void Author::Print() const
{
	std::cout << ":author: " << _strarg;
}

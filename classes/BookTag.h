#pragma once
#include "Tag.h"

class BookTag : public Tag
{
public:
	/* �±� ��ġ �Լ�
		���ڷ� ���� �±׿� �ڽ��� ��ġ�ϴ���, ������ ����� �˻� ���ǿ� ���� �Ǵ��Ͽ� ��ȯ�մϴ�.
	*/
	virtual bool Match(const BookTag* search) const = 0;
};


#pragma once
#include "Tag.h"

class OperationTag : public Tag
{
public:
	/* ��� �Լ�
		�±׿� �°� �����ؾ� �ϴ� ������ �����ؾ� �մϴ�.
	*/
	virtual void Operate() = 0;
};


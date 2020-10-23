#pragma once
#include "Tag.h"

class OperationTag : public Tag
{
public:
	/* 태그에 따른 기능을 정의하는 함수

	*/
	virtual void Operate() = 0;
};


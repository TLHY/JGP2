#pragma once
#include "Tag.h"

class OperationTag : public Tag
{
public:
	/* 기능 함수
		태그에 맞게 수행해야 하는 동작을 정의해야 합니다.
	*/
	virtual void Operate() = 0;
};


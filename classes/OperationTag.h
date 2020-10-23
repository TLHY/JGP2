#pragma once
#include "Tag.h"

class OperationTag : public Tag
{
public:
	virtual void Operate() = 0;
};


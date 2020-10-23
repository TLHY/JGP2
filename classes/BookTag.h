#pragma once
#include "Tag.h"

class BookTag : public Tag
{
public:
	virtual bool Match(const BookTag* tag) const = 0;
};


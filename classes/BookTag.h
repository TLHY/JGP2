#pragma once
#include "Tag.h"

class BookTag : public Tag
{
public:
	/* 태그 일치 함수
		인자로 받은 태그와 자신이 일치하는지, 데이터 요소의 검색 조건에 따라 판단하여 반환합니다.
	*/
	virtual bool Match(const BookTag* search) const = 0;
};


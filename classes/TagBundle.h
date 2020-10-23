#pragma once
#include <vector>
#include <typeinfo>
#include <iostream>
#include "Tag.h"

class TagBundle
{
public:
	std::vector<Tag*> tags;	// 동적 할당된 Tag를 저장하는 vector

	// 생성자
	TagBundle() : tags() {};
	TagBundle(std::vector<Tag*>& tags);
	TagBundle(const TagBundle& old);
	TagBundle(TagBundle&& old);
	
	// 대입 연산자
	TagBundle& operator=(const TagBundle& other);
	TagBundle& operator=(TagBundle&& other);
	
	/* 규칙 검사
		_tags에 포함된 Tag들에 대해 Tag.Validate()를 호출합니다.
	*/
	void Validate() const;

	/* 출력 함수
		_tags에 포함된 tag들에 대해 Tag.Print()를 호출합니다.
	*/
	void Print() const;

	/* 클래스로 태그를 찾는 함수
		특정 클래스를 상속한 Tag만 새로운 TagBundle로 묶어서 반환합니다.
		예를 들어, GetTagByType<BookTag>()는 BookTag를 상속하는 Tag만 포함하는 새로운 TagBundle을 반환합니다.
	*/
	template<typename T> TagBundle GetTagByType();
	
	// 파괴자
	~TagBundle();
};

// ostream에 대한 left-shift 연산; 출력 함수 사용
inline std::ostream& operator<<(std::ostream& out, const TagBundle& tag_bundle) {
	tag_bundle.Print();
	return out;
}

/* 상속 여부를 확인하는 함수
	포인터가 가리키는 객체가 정해진 클래스를 상속했는지 검사합니다.
	TagBundle::GetTagByType<T>()에서만 사용합니다. 
*/
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

template<typename T> TagBundle TagBundle::GetTagByType()
{
	std::vector<Tag*> found;
	Tag* cur;
	for (unsigned int i = 0; i < tags.size(); i++) {
		cur = tags.at(i);
		if (instanceof<T>(cur)) {
			found.push_back(cur->copy());
		}
	}
	return TagBundle(found);
}

TagBundle::TagBundle(std::vector<Tag*>& tags)
	: TagBundle()
{
	tags.insert(tags.begin(), tags.begin(), tags.end());
}

TagBundle::TagBundle(const TagBundle& old) : TagBundle()
{
	for (unsigned int i = 0; i < old.tags.size(); i++) {
		tags.push_back(old.tags.at(i)->copy());
	}
}

TagBundle::TagBundle(TagBundle&& old) : TagBundle(old.tags)
{
	old.tags.clear();
}

TagBundle& TagBundle::operator=(const TagBundle& other)
{
	for (unsigned int i = 0; i < tags.size(); i++) {
		delete tags.at(i);
	}
	tags.clear();
	for (unsigned int i = 0; i < other.tags.size(); i++) {
		tags.push_back(other.tags.at(i)->copy());
	}
	return *this;
}

TagBundle& TagBundle::operator=(TagBundle&& other)
{
	for (unsigned int i = 0; i < tags.size(); i++) {
		delete tags.at(i);
	}
	tags.clear();
	tags.insert(tags.begin(), other.tags.begin(), other.tags.end());
	other.tags.clear();
	return *this;
}


void TagBundle::Validate() const
{
	for (unsigned int i = 0; i < tags.size(); i++) {
		tags.at(i)->Validate();
	}
}

void TagBundle::Print() const
{
	for (unsigned int i = 0; i < tags.size(); i++) {
		tags.at(i)->Print();
		std::cout << "\n";
	}
}

TagBundle::~TagBundle()
{
	for (unsigned int i = 0; i < tags.size(); i++) {
		delete tags.at(i);
	}
}

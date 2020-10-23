#pragma once
#include <vector>
#include <typeinfo>
#include <iostream>
#include "Tag.h"

class TagBundle
{
public:
	std::vector<Tag*> tags;	// ���� �Ҵ�� Tag�� �����ϴ� vector

	// ������
	TagBundle() : tags() {};
	TagBundle(std::vector<Tag*>& tags);
	TagBundle(const TagBundle& old);
	TagBundle(TagBundle&& old);
	
	// ���� ������
	TagBundle& operator=(const TagBundle& other);
	TagBundle& operator=(TagBundle&& other);
	
	/* ��Ģ �˻�
		_tags�� ���Ե� Tag�鿡 ���� Tag.Validate()�� ȣ���մϴ�.
	*/
	void Validate() const;

	/* ��� �Լ�
		_tags�� ���Ե� tag�鿡 ���� Tag.Print()�� ȣ���մϴ�.
	*/
	void Print() const;

	/* Ŭ������ �±׸� ã�� �Լ�
		Ư�� Ŭ������ ����� Tag�� ���ο� TagBundle�� ��� ��ȯ�մϴ�.
		���� ���, GetTagByType<BookTag>()�� BookTag�� ����ϴ� Tag�� �����ϴ� ���ο� TagBundle�� ��ȯ�մϴ�.
	*/
	template<typename T> TagBundle GetTagByType();
	
	// �ı���
	~TagBundle();
};

// ostream�� ���� left-shift ����; ��� �Լ� ���
inline std::ostream& operator<<(std::ostream& out, const TagBundle& tag_bundle) {
	tag_bundle.Print();
	return out;
}

/* ��� ���θ� Ȯ���ϴ� �Լ�
	�����Ͱ� ����Ű�� ��ü�� ������ Ŭ������ ����ߴ��� �˻��մϴ�.
	TagBundle::GetTagByType<T>()������ ����մϴ�. 
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

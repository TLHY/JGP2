#pragma once
#include "book_tags.h"
#include "TagBundle.h"
class Book
{
private:
	ID _id;
	Title _title;
	Author _author;
	Publisher _publisher;
	Date _date;
public:
	void set_ID(std::string id) { _id << id; };
	void set_Title(std::string title) { _title << title; };
	void set_Author(std::string author) { _author << author; };
	void set_Publisher(std::string publisher) { _publisher << publisher; };
	void set_Date(std::string date) { _date << date; };

	void Validate();

	int Match(const TagBundle& bundle) const;
};

void Book::Validate()
{
	_id.Validate();
	_title.Validate();
	_author.Validate();
	_publisher.Validate();
	_date.Validate();
}

int Book::Match(const TagBundle& bundle) const
{
	int match = 0;
	BookTag* t;
	for (unsigned int i = 0; i < bundle.tags.size(); i++) {
		t = (BookTag*) bundle.tags.at(i);
		match += _id.Match(t)
			+ _title.Match(t)
			+ _author.Match(t)
			+ _publisher.Match(t)
			+ _date.Match(t);
	}
	return match;
}

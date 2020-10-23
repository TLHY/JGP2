// 테스트용 main 함수

#include <iostream>
#include "Author.h"
#include "tag_parents.h"
#include "TagBundle.h"
#include "exceptions.h"

int main_3() {	// 예외를 처리하는 예시
	try
	{
		throw InvalidTag(":aaaa:");
	}
	catch (const InvalidTag& e)
	{
		std::cout << e.what() << "\b: " << e.name() << "\n";
	}
	return 0;
}

int main_2() {	// 인자를 파싱하는 예시
	std::string s = ":author: author name :author: author 2 :title: book 2";
	std::stringstream ss(s);
	std::string t;

	while (ss >> t) {
		Author a;
		std::getline(ss, s);
		s = a.ParseArgument(s);
		ss.str(s);
		ss.clear();
		std::cout << a << ", left: " << s << "\n";
	}

	return 0;
}

int main() {	// 태그 번들에서 특정 타입의 태그만 골라내는 예시
	TagBundle bundle;
	
	bundle.tags.push_back(new Author);
	bundle.tags.push_back(new Author);

	std::cout << "=== entire tags ===\n" << bundle << "\n";

	TagBundle authors = bundle.GetTagByType<Author>();
	std::cout << "=== Author ===\n" << bundle << "\n";

	TagBundle books = bundle.GetTagByType<BookTag>();
	std::cout << "=== BookTag ===\n" << books << "\n";
	
	TagBundle operations = bundle.GetTagByType<OperationTag>();
	std::cout << "=== OperationTag ===\n" << operations << "\n";

	std::cout << "=== entire tags ===\n" << bundle << "\n";
	return 0;
}

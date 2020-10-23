// �׽�Ʈ�� main �Լ�

#include <iostream>
#include "Author.h"
#include "tag_parents.h"
#include "TagBundle.h"
#include "exceptions.h"

int main_3() {	// ���ܸ� ó���ϴ� ����
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

int main_2() {	// ���ڸ� �Ľ��ϴ� ����
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

int main() {	// �±� ���鿡�� Ư�� Ÿ���� �±׸� ��󳻴� ����
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

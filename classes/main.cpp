// �׽�Ʈ�� main �Լ�

#include <iostream>
#include "Author.h"
#include "tag_parents.h"
#include "TagBundle.h"
#include "exceptions.h"

int main() {	// Author ��� ����
	Author* a = new Author;
	a->ParseArgument("John Doe");

	Author* search1 = new Author;
	search1->ParseArgument("doe");
	
	Author* search2 = new Author;
	search2->ParseArgument("JOhn trio");

	std::cout << *a << ", " << *search1 << ", " << *search2 << "\n\n";

	std::cout << a->Match(search1) << "\n"	// John Doe���� doe�� ã��: ����
		<< a->Match(search2) << "\n"		// John Doe���� JOhn trio�� ã��: ����
		<< a->Match(a) << "\n";				// John Doe���� John Doe�� ã��: ����

	/* output:
	:author: John Doe, :author: doe, :author: JOhn trio

	1
	0
	1
	*/

	return 0;
}

int main_4() {	// Author ��� ����
	std::vector<std::string> args;
	args.push_back("nice name");
	args.push_back("�ޡޡ�");
	args.push_back("����� �� ���� ���ڿ�");
	args.push_back("author");
	args.push_back("");

	TagBundle bundle;

	for (int i = 0; i < args.size(); i++) {
		Author* a = new Author;
		a->ParseArgument(args[i]);
		bundle.tags.push_back(a);
		try
		{
			a->Validate();	// Tag::Validate()�� ��� �±׿� ���� �� ���� ȣ���ϴ� �κ�
		}
		catch (const InvalidArgument& e)	// ���ܰ� �߻��ϸ�
		{
			std::cout << e.what() << "\b: " << *(e.tag()) << "\n";	// ���� ó��
			continue;
		}
		std::cout << *a << "\n";	// ���ܰ� ������ �׳� ���
	}

	std::cout << "\n= bundle =\n" << bundle << "\n";
	try
	{
		bundle.Validate();	// TagBundle::Validate()�� ȣ���ϴ� �κ�
	}
	catch (const InvalidArgument& e)
	{
		std::cout << e.what() << "\b: " << *(e.tag()) << "\n";
	}
	
	/* output:
	:author: nice name
	[!] �±��� ���ڰ� �ùٸ��� �ʽ��ϴ�: :author: �ޡޡ�
	[!] �±��� ���ڰ� �ùٸ��� �ʽ��ϴ�: :author: ����� �� ���� ���ڿ�
	:author: author
	[!] �±��� ���ڰ� �ùٸ��� �ʽ��ϴ�: :author:

	= bundle =
	:author: nice name
	:author: �ޡޡ�
	:author: ����� �� ���� ���ڿ�
	:author: author
	:author:

	[!] �±��� ���ڰ� �ùٸ��� �ʽ��ϴ�: :author: �ޡޡ�
	*/

	return 0;
}

int main_3() {	// ���ܸ� ó���ϴ� ����
	try
	{
		throw InvalidTag(":aaaa:");
	}
	catch (const InvalidTag& e)
	{
		std::cout << e.what() << "\b: " << e.name() << "\n";
	}
	try {
		Author a;
		throw InvalidArgument(&a);
	}
	catch (const InvalidArgument & e) {
		std::cout << e.what() << "\b: " << *(e.tag()) << "\n";
	}

	/* output:
	[!] ����� �� ���� �±��Դϴ�: :aaaa:
	[!] �±��� ���ڰ� �ùٸ��� �ʽ��ϴ�: :author:
	*/

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
		std::cout << "<" << a << "> left: \"" << s << "\"\n";
	}

	/* output:
	<:author: author name> left: ":author: author 2 :title: book 2"
	<:author: author 2> left: ":title: book 2"
	<:author: book 2> left: ""
	*/

	return 0;
}

int main_1() {	// �±� ���鿡�� Ư�� Ÿ���� �±׸� ��󳻴� ����
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

	/* output:
	=== entire tags ===
	:author:
	:author:

	=== Author ===
	:author:
	:author:

	=== BookTag ===

	=== OperationTag ===

	=== entire tags ===
	:author:
	:author:
	*/

	return 0;
}

// �׽�Ʈ�� main �Լ�

#include <iostream>
#include "Author.h"
#include "tag_parents.h"
#include "TagBundle.h"
#include "exceptions.h"

int main() {
	std::string _raw_input;
	std::getline(std::cin, _raw_input);

	std::stringstream ss(_raw_input);
	std::string token;
	bool tag_found = false;
	while (ss >> token) {
		if (Tag::is_tag(token)) {
			tag_found = true;
		}
	}
	if (!tag_found) {
		ss.str(_raw_input);
		ss.clear();
		_raw_input = ":title: " + _raw_input + " :";
		std::cout << "| " << _raw_input << "\n";
		while (ss >> token) {
			token = ":title: " + token + " :";
			std::cout << "| " << token << "\n";
			if (_raw_input.find(token) == std::string::npos) {
				_raw_input = _raw_input.substr(0, _raw_input.length() - 1) + token;
			}
		}
		_raw_input = _raw_input.substr(0, _raw_input.length() - 2);
	}
	
	std::cout << "\n'" << _raw_input << "'\n";

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
		*a << args[i];
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

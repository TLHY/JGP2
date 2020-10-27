// 테스트용 main 함수

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


int main_4() {	// Author 사용 예시
	std::vector<std::string> args;
	args.push_back("nice name");
	args.push_back("◇◇◇");
	args.push_back("사용할 수 없는 문자열");
	args.push_back("author");
	args.push_back("");

	TagBundle bundle;

	for (int i = 0; i < args.size(); i++) {
		Author* a = new Author;
		*a << args[i];
		bundle.tags.push_back(a);
		try
		{
			a->Validate();	// Tag::Validate()를 모든 태그에 대해 한 번씩 호출하는 부분
		}
		catch (const InvalidArgument& e)	// 예외가 발생하면
		{
			std::cout << e.what() << "\b: " << *(e.tag()) << "\n";	// 예외 처리
			continue;
		}
		std::cout << *a << "\n";	// 예외가 없으면 그냥 출력
	}

	std::cout << "\n= bundle =\n" << bundle << "\n";
	try
	{
		bundle.Validate();	// TagBundle::Validate()를 호출하는 부분
	}
	catch (const InvalidArgument& e)
	{
		std::cout << e.what() << "\b: " << *(e.tag()) << "\n";
	}
	
	/* output:
	:author: nice name
	[!] 태그의 인자가 올바르지 않습니다: :author: ◇◇◇
	[!] 태그의 인자가 올바르지 않습니다: :author: 사용할 수 없는 문자열
	:author: author
	[!] 태그의 인자가 올바르지 않습니다: :author:

	= bundle =
	:author: nice name
	:author: ◇◇◇
	:author: 사용할 수 없는 문자열
	:author: author
	:author:

	[!] 태그의 인자가 올바르지 않습니다: :author: ◇◇◇
	*/

	return 0;
}

int main_3() {	// 예외를 처리하는 예시
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
	[!] 사용할 수 없는 태그입니다: :aaaa:
	[!] 태그의 인자가 올바르지 않습니다: :author:
	*/

	return 0;
}

int main_1() {	// 태그 번들에서 특정 타입의 태그만 골라내는 예시
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

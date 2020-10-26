// 테스트용 main 함수

#include <iostream>
#include "Author.h"
#include "tag_parents.h"
#include "TagBundle.h"
#include "exceptions.h"

int main() {	// Author 사용 예시
	Author* a = new Author;
	a->ParseArgument("John Doe");

	Author* search1 = new Author;
	search1->ParseArgument("doe");
	
	Author* search2 = new Author;
	search2->ParseArgument("JOhn trio");

	std::cout << *a << ", " << *search1 << ", " << *search2 << "\n\n";

	std::cout << a->Match(search1) << "\n"	// John Doe에서 doe를 찾음: 성공
		<< a->Match(search2) << "\n"		// John Doe에서 JOhn trio를 찾음: 실패
		<< a->Match(a) << "\n";				// John Doe에서 John Doe를 찾음: 성공

	/* output:
	:author: John Doe, :author: doe, :author: JOhn trio

	1
	0
	1
	*/

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
		a->ParseArgument(args[i]);
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
		std::cout << "<" << a << "> left: \"" << s << "\"\n";
	}

	/* output:
	<:author: author name> left: ":author: author 2 :title: book 2"
	<:author: author 2> left: ":title: book 2"
	<:author: book 2> left: ""
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

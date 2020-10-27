#pragma once
#include <iostream>
#include <string>
#include <sstream>

/* 태그 클래스
	태그의 상위 추상 클래스입니다.
*/
class Tag
{
protected:
	// 필요한 인자를 골라서 사용하면 됩니다. 일단 둘 다 만들어 뒀어요.
	std::string _strarg;	// 문자열 인자
	int _intarg;			// 정수 인자
public:
	// 생성자
	Tag(const std::string& strarg, const int& intarg) : _strarg(strarg), _intarg(intarg) {};
	Tag(const std::string& strarg) : Tag(strarg, 0) {};
	Tag(const int& intarg) : Tag("", intarg) {};
	Tag() : Tag("", 0) {};

	// 멤버 변수에 대한 접근 함수
	std::string strarg() const { return _strarg; };
	int intarg() const { return _intarg; };

	/* 태그 검사
		인자로 전달된 문자열이 태그인지를 문법 규칙을 기준으로 판단하여 반환합니다.
	*/
	static bool is_tag(const std::string& str);

	/* 인자 추가
		멤버 변수인 _strarg에 인자로 받은 str을 붙입니다.
		다음과 같습니다.
		_strarg += " " + str;
	*/
	Tag& operator<<(std::string str);

	/* 인자 파싱 [삭제됨]
		문자열로부터 인자를 파싱하는 함수입니다.
		인자로 받은 문자열에서 다른 태그가 나오기 직전까지를 인자로 인식하여 _strarg에 저장합니다.
		인식한 부분을 제외한 나머지 문자열을 반환합니다.

		이 함수는 인자를 파싱하면서 모든 종류의 공백 문자와 연속으로 사용되는 공백 문자들을 모두 하나의 공백 문자(SP)로 치환합니다.
		따라서 인자를 파싱한 이후에는 공백과 관련된 예외를 처리하는 것이 불가능합니다.
		인자를 파싱하기 이전에 입력 문자열을 가지고 공백과 관련된 예외를 처리해주세요.
	*/
	// std::string ParseArgument(std::string str);

	/* 객체 복사
		객체를 복제하는 기능을 구현해야 합니다.
	*/ 
	virtual Tag* copy() const = 0;
	
	/* 규칙 검사
		인자가 문법 및 의미 규칙을 위반하지 않는지 검사하는 기능을 구현해야 합니다.
		규칙 위반이 발생하면 적절한 예외를 발생시켜주세요.
		발생한 예외는 주 프롬프트에서 처리합니다.
		+ _intarg를 사용하는 태그의 경우, 이 함수 안에서 _strarg의 데이터로부터 _intarg를 초기화하는 것을 권장합니다.
	*/
	virtual void Validate() const = 0;

	/* 출력 함수
		":tag-name: argument"와 같이 태그 내용을 출력합니다.
	*/
	virtual void Print() const = 0;
};

/* 도서 태그 클래스
	도서 태그의 상위 추상 클래스입니다.
	태그 클래스를 상속합니다.
*/
class BookTag : public Tag
{
public:
	/* 태그 일치 함수
		인자로 받은 태그와 자신이 일치하는지, 데이터 요소의 검색 조건에 따라 판단하여 반환합니다.
	*/
	virtual bool Match(const BookTag* search) const = 0;
};

class MainPrompt;	// 주 프롬프트 클래스가 아직 없으므로 일단 이름만 만들어줍니다.

/* 명령 태그 클래스
	명령 태그의 상위 추상 클래스입니다.
	태그 클래스를 상속합니다.
*/
class OperationTag : public Tag
{
public:
	/* 기능 함수
		태그에 맞게 수행해야 하는 동작을 정의해야 합니다.
	*/
	virtual void Operate(MainPrompt& main_prompt) = 0;
};

// ostream에 대한 left-shift 연산; 출력 함수 사용
inline std::ostream& operator<<(std::ostream& out, const Tag& tag) {
	tag.Print();
	return out;
}

inline bool Tag::is_tag(const std::string& str)
{
	if (str.length() < 3) {
		return false;
	}
	if (str.at(0) != ':' || str.at(str.length() - 1) != ':') {
		return false;
	}
	for (unsigned int i = 1; i < str.length() - 1; i++) {
		if (str.at(i) < 'a' || str.at(i) > 'z') {
			return false;
		}
	}
	return true;
}

inline Tag& Tag::operator<<(std::string str)
{
	if (!_strarg.empty()) {
		_strarg += " ";
	}
	_strarg +=  str;
	return *this;
}

/*
std::string Tag::ParseArgument(std::string str)
{
	std::stringstream stream(str), args;
	std::string tmp, result;
	while (stream >> tmp) {
		if (is_tag(tmp)) {
			result = tmp;
			break;
		}
		if (!args.str().empty()) {
			args << " ";
		}
		args << tmp;
	}
	tmp = "";
	if (!result.empty()) {
		tmp = result;
	}
	_strarg = args.str();
	std::getline(stream, result);
	if (!tmp.empty()) {
		result = tmp + result;
	}
	return result;
}
*/

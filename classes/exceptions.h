#pragma once
#include <exception>
#include "Tag.h"

/* 파일 내의 식별 번호 충돌
	파일에서 식별 번호 충돌이 발견되면 이 예외를 발생시킵니다.
*/
class ReduplicatedID : public std::exception {
private:
	const int _line;
public:
	ReduplicatedID(const int line) : std::exception(), _line(line) {};
	const char* what() const { return "[!] 식별 번호 충돌이 발견되었습니다. 데이터 파일을 직접 수정해주세요."; };
	const int line() const { return _line; };
};

/* 파일 내의 유효하지 않은 행
	파일에서 해석할 수 없는 행이 발견되면 이 예외를 발생시킵니다.
*/
class InvalidLine : public std::exception {
private:
	const int _line;
public:
	InvalidLine(const int line) : std::exception(), _line(line) {};
	const char* what() const { return "[오류] 도서 정보로 해석할 수 없는 행이 발견되었습니다. 데이터 파일을 직접 수정해주세요."; }
	const int line() const { return _line; };
};

/* 사용할 수 없는 태그
	정의되지 않은 태그를 입력하면 이 예외를 발생시킵니다.
	예를 들어, :abcdef:와 같은 태그는 문법적으로는 올바르지만 정의가 존재하지 않으므로 사용할 수 없는 태그입니다.
*/
class InvalidTag : public std::exception {
private:
	const char* _name;
public:
	InvalidTag(const char* name) : std::exception(), _name(name) {};
	const char* what() const { return "[!] 사용할 수 없는 태그입니다."; };
	const char* name() const { return _name; };
};

/* 여러 명령 태그 사용
	한 입력에 여러 개의 명령 태그가 사용되었을 때 이 예외를 발생시킵니다.
*/
class MultipleOperationTags : public std::exception {
public:
	const char* what() const { return "[!] 동시에 여러 명령 태그를 사용할 수 없습니다."; };
};

/* 하나 이상의 도서 태그 필요
	edit 태그가 사용될 때 id 태그를 제외한 하나 이상의 도서 태그가 같이 입력되지 않으면 이 예외를 발생시킵니다.
*/
class NeedOneOrMoreBookTag : public std::exception {
public:
	const char* what() const { return "[!] 식별 번호 태그를 제외한 하나 이상의 도서 정보 태그가 필요합니다."; };
};

/* 모든 도서 태그 필요
	add 태그가 사용될 때 id 태그를 제외한 모든 도서 태그가 같이 입력되지 않으면 이 예외를 발생시킵니다.
*/
class NeedEveryBookTag : public std::exception {
public:
	const char* what() const { return "[!] 식별 번호 태그를 제외한 모든 도서 정보 태그가 필요합니다."; };
};

// TODO: add, edit 태그 사용시 중복된 도서 태그 사용도 예외로 처리해야 함

/* 태그 정보를 포함하는 예외
	태그 정보를 포함해야 하는 모든 예외의 상위 추상 클래스입니다.
	태그 정보가 필요한 예외 클래스는 이 클래스를 상속받아서 정의하면 됩니다.
	생성자로 예외가 발생한 태그를 저장하고 접근 함수로 태그에 접근할 수 있습니다.
*/
class TagException : public std::exception {
private:
	const Tag* _tag;
public:
	TagException(const Tag* tag) : std::exception(), _tag(tag) {};
	const Tag* tag() const { return _tag; }
};

/* 올바르지 않은 인자
	태그가 규칙 검사를 할 때 인자가 문법 형식을 위반하면 이 예외를 발생시킵니다.
*/
class InvlidArgument : public TagException
{
public:
	InvlidArgument(const Tag* tag) : TagException(tag) {};
	const char* what() const { return "[!] 태그의 인자가 올바르지 않습니다."; }
};

/* 조회할 수 없는 식별 번호
	id 태그의 인자가 존재하지 않는 id일 때 이 예외를 발생시킵니다.
*/
class IDNotFound : public TagException {
public:
	IDNotFound(const Tag* tag) : TagException(tag) {};
	const char* what() const { return "[!] 조회할 수 없는 식별 번호입니다."; }
};

/* 조회할 수 없는 페이지
	page 태그의 인자가 검색 결과 내에 존재하지 않는 페이지일 때 이 예외를 발생시킵니다.
*/
class PageNotFound : public TagException {
public:
	PageNotFound(const Tag* tag) : TagException(tag) {};
	const char* what() const { return "[!] 조회할 수 없는 페이지입니다."; };
};
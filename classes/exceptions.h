#pragma once
#include <exception>
#include "Tag.h"

/* ���� ���� �ĺ� ��ȣ �浹
	���Ͽ��� �ĺ� ��ȣ �浹�� �߰ߵǸ� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class ReduplicatedID : public std::exception {
private:
	const int _line;
public:
	ReduplicatedID(const int line) : std::exception(), _line(line) {};
	const char* what() { return "[!] �ĺ� ��ȣ �浹�� �߰ߵǾ����ϴ�. ������ ������ ���� �������ּ���."; };
	const int line() { return _line; };
};

/* ���� ���� ��ȿ���� ���� ��
	���Ͽ��� �ؼ��� �� ���� ���� �߰ߵǸ� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class InvalidLine : public std::exception {
private:
	const int _line;
public:
	InvalidLine(const int line) : std::exception(), _line(line) {};
	const char* what() { return "[����] ���� ������ �ؼ��� �� ���� ���� �߰ߵǾ����ϴ�. ������ ������ ���� �������ּ���."; }
	const int line() { return _line; };
};

/* ���� ��� �±� ���
	�� �Է¿� ���� ���� ��� �±װ� ���Ǿ��� �� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class MultipleOperationTags : public std::exception {
public:
	const char* what() { return "[!] ���ÿ� ���� ��� �±׸� ����� �� �����ϴ�."; };
};

/* �ϳ� �̻��� ���� �±� �ʿ�
	edit �±װ� ���� �� id �±׸� ������ �ϳ� �̻��� ���� �±װ� ���� �Էµ��� ������ �� ���ܸ� �߻���ŵ�ϴ�.
*/
class NeedOneOrMoreBookTag : public std::exception {
public:
	const char* what() { return "[!] �ĺ� ��ȣ �±׸� ������ �ϳ� �̻��� ���� ���� �±װ� �ʿ��մϴ�."; };
};

/* ��� ���� �±� �ʿ�
	add �±װ� ���� �� id �±׸� ������ ��� ���� �±װ� ���� �Էµ��� ������ �� ���ܸ� �߻���ŵ�ϴ�.
*/
class NeedEveryBookTag : public std::exception {
public:
	const char* what() { return "[!] �ĺ� ��ȣ �±׸� ������ ��� ���� ���� �±װ� �ʿ��մϴ�."; };
};

// TODO: add, edit �±� ���� �ߺ��� ���� �±� ��뵵 ���ܷ� ó���ؾ� ��

/* �±� ������ �����ϴ� ����
	�±� ������ �����ؾ� �ϴ� ��� ������ ���� �߻� Ŭ�����Դϴ�.
	�±� ������ �ʿ��� ���� Ŭ������ �� Ŭ������ ��ӹ޾Ƽ� �����ϸ� �˴ϴ�.
	�����ڷ� ���ܰ� �߻��� �±׸� �����ϰ� ���� �Լ��� �±׿� ������ �� �ֽ��ϴ�.
*/
class TagException : public std::exception {
private:
	const Tag* _tag;
public:
	TagException(const Tag* tag) : std::exception(), _tag(tag) {};
	const Tag* tag() { return _tag; }
};

/* �ùٸ��� ���� ����
	�±װ� ��Ģ �˻縦 �� �� ���ڰ� ���� ������ �����ϸ� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class InvlidArgument : public TagException
{
public:
	InvlidArgument(const Tag* tag) : TagException(tag) {};
	const char* what() { return "[!] �±��� ���ڰ� �ùٸ��� �ʽ��ϴ�."; }
};

/* ��ȸ�� �� ���� �ĺ� ��ȣ
	id �±��� ���ڰ� �������� �ʴ� id�� �� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class IDNotFound : public TagException {
public:
	IDNotFound(const Tag* tag) : TagException(tag) {};
	const char* what() { return "[!] ��ȸ�� �� ���� �ĺ� ��ȣ�Դϴ�."; }
};

/* ��ȸ�� �� ���� ������
	page �±��� ���ڰ� �˻� ��� ���� �������� �ʴ� �������� �� �� ���ܸ� �߻���ŵ�ϴ�.
*/
class PageNotFound : public TagException {
public:
	PageNotFound(const Tag* tag) : TagException(tag) {};
	const char* what() { return "[!] ��ȸ�� �� ���� �������Դϴ�."; };
};
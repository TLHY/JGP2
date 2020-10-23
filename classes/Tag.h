#pragma once
#include <iostream>
#include <string>
#include <sstream>

class Tag
{
protected:
	// �ʿ��� ���ڸ� ��� ����ϸ� �˴ϴ�. �ϴ� �� �� ����� �׾��.
	std::string _strarg;	// ���ڿ� ����
	int _intarg;			// ���� ����
public:
	// ������
	Tag(const std::string& strarg, const int& intarg) : _strarg(strarg), _intarg(intarg) {};
	Tag(const std::string& strarg) : Tag(strarg, 0) {};
	Tag(const int& intarg) : Tag("", intarg) {};
	Tag() : Tag("", 0) {};

	// ��� ������ ���� ���� �Լ�
	std::string strarg() const { return _strarg; };
	int intarg() const { return _intarg; };

	/* �±� �˻�
		� ���ڿ��� �±׿� �ش��ϴ����� ��ȯ�մϴ�.
	*/
	static bool is_tag(const std::string& str);

	/* ���� �Ľ�
		���ڿ��κ��� ���ڸ� �Ľ��ϴ� �Լ��Դϴ�.
		���ڷ� ���� ���ڿ����� �ٸ� �±װ� ������ ���������� ���ڷ� �ν��Ͽ� _strarg�� �����մϴ�.
		�ν��� �κ��� ������ ������ ���ڿ��� ��ȯ�մϴ�.
	*/
	std::string ParseArgument(std::string str);	// TODO �̰� �񰡻� �Լ��� �����ϴ� �� �����ڴ�.

	/* ��ü ����
		��ü�� �����ϴ� ����� �����ؾ� �մϴ�.
	*/ 
	virtual Tag* copy() const = 0;
	
	/* ��Ģ �˻�
		���ڰ� ���� �� �ǹ� ��Ģ�� �������� �ʴ��� �˻��ϴ� ����� �����ؾ� �մϴ�.
		��Ģ ������ �߻��ϸ� ������ ���ܸ� �߻������ּ���.
		�߻��� ���ܴ� �� ������Ʈ���� ó���մϴ�.
		+ _intarg�� ����ϴ� �±��� ���, �� �Լ� �ȿ��� _strarg�� �����ͷκ��� _intarg�� �ʱ�ȭ�ϴ� ���� �����մϴ�.
	*/
	virtual void Validate() const = 0;

	/* ��� �Լ�
		":tag-name: argument"�� ���� �±� ������ ����մϴ�.
	*/
	virtual void Print() const = 0;
};

// ostream�� ���� left-shift ����; ��� �Լ� ���
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

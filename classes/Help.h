#pragma once
#pragma once
#include<iostream>
#include "tag_parents.h"
#include "TagBundle.h"
#include "exceptions.h"
#include "MainPrompt.h";
using namespace std;
class Help :public OperationTag {
	Tag* copy() const;
	void Validate();
	void Print() const;
	void Operate(MainPrompt& main_prompt);
};
Tag* Help::copy() const {
	return new Help(*this);
}
void Help::Validate() {
	if (!_strarg.empty()) {
		throw InvalidArgument(this);
	}
}
void Print() {
	cout << ":Help:" << endl;
}
void Operate(MainPrompt& main) {
	cout << "도서 태그 설명/규칙" << endl;
	cout << "1):title: 도서명을 의미하며, 인자가 반드시 있어야합니다. 검색란에 태그없이 입력하는 경우 :title:이 태그로 붙습니다." << endl;
	cout << "2):author: 저자명을 의미하며, 인자가 반드시 있어야합니다." << endl;
	cout << "3):publisher: 출판사명을 의미하며, 인자가 반드시 있어야합니다." << endl;
	cout << "4):date: 출판년도를 의미하며, 인자가 반드시 있어야합니다." << endl;
	cout << "5):ID: 각 도서의 식별 번호를 의미하며, 인자가 반드시 숫자형이여야 합니다." << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "명령 태그 규칙" << endl;
	cout << "1):add: 입력받은 도서 정보를 데이터 파일에 추가합니다.같은 입력에 식별 번호 태그를 제외한 모든 도서 태그가 포함되어야 합니다. 도서 태그들의 인자를 이용하여 추가할 도서의 정보를 구성합니다.";
	cout << ":add:의 예시) :add: :title: title :author: author :publisher: publisher :date: 2020" << endl;
	cout << "2):edit: 입력받은 식별 번호의 도서 정보를 편집합니다. 같은 입력에 해당 식별 번호를 가지는 도서 정보가 존재해야 합니다. 또, 같은 입력에 식별 번호 태그를 제외한 하나 이상의 도서 정보 태그가 포함되어야 합니다." << endl;
	cout << ":edit:의 예시) :edit: 10 :title: fun :author: cool" << endl;
	cout << "3):del: 입력받은 식별 번호의 도서 정보를 데이터 파일에서 삭제합니다. 해당 식별 번호를 가지는 도서 정보가 있어야 합니다." << endl;
	cout << ":del:의 예시) :del: 10" << endl;
	cout << "4):page: 이전 검색 결과의 특정 페이지를 출력합니다. 검색 결과가 가지는 페이지의 범위에 포함되는 양의 정수를 입력해야합니다." << endl;
	cout << ":page:의 예시) :page: 4" << endl;
	cout << "5):help: 프로그램에 대한 설명을 출력합니다." << endl;
	cout << ":help:의 예시) :help:" << endl;
	cout << "6):clear: 이전 검색 결과를 초기화합니다." << endl;
	cout << ":clear:의 예시) :clear:" << endl;
	cout << "7):exit: 프로그램을 종료합니다." << endl;
	cout << ":exit:의 예시) :exit:" << endl;
}

#include "FileIO.h"
using namespace std;

//해당 파일에 쓰인 것들이 올바르게 쓰였는지 검사가 필요함

vector<Book*> File::import_book_list()
{
	cout << "도서 정보 불러오기 중..." << endl;
	/*
	this->address 경로에 저장된 파일로 부터 데이터를 읽어들인다
	*/
	ifstream readFile;
	readFile.open(this->address);

	if (readFile.is_open())
	{
		vector<Book*>tempbl;
		int bi = 0;
		string samplebook[100];
		char book[100];

		while (!readFile.eof())
		{
			int book_data_index = 0;
			readFile.getline(book, 100);

			if (this->is_Right_Data(book)) 
			{
				cerr << endl << "데이터의 형식이 올바르지 않습니다." << endl << endl;
				cout << "해당 라인의 데이터 : " << book << endl << endl;
				cout << "이 창을 닫으려면 아무키나 눌러주세요.";
				getch();
				exit(-1);
			}

			Book* sample = new Book();
			char* parsing = strtok(book, "\t");
			while (parsing != NULL) {
				samplebook[book_data_index] = parsing;
				book_data_index++;
				parsing = strtok(NULL, "\t");
			}

			//중복되는 ID가 있는지 검사
			int dup_flag = 0;
			for (int t = 0; t < tempbl.size(); t++)
			{
				if (tempbl.at(t)->get_ID() == atoi(samplebook[0].c_str()))
				{
					cout << "이미 정보가 있는 ID 발견 : " << samplebook[0] << endl;
					cout << "이 정보는 현재 텍스트 파일엔 존재하지만 프로그램 상에서 제외됩니다." << endl;
					cout << "다음 도서 정보부터 저장을 재개합니다" << endl << endl;
					dup_flag++;
					break;
				}
			}

			if (dup_flag > 0) {
				continue;
			}

			//도서 정보를 태그별로 대입
			for (int k = 0; k < book_data_index; k++) {
				if (k == 0) {
					sample->set_ID(samplebook[0]);
				}
				else if (k == 1) {
					sample->set_Title(samplebook[1]);
				}
				else if (k == 2) {
					sample->set_Author(samplebook[2]);
				}
				else if (k == 3) {
					sample->set_Publisher(samplebook[3]);
				}
				else if (k == 4) {
					sample->set_Date(samplebook[4]);
				}
			}
			
			//벡터에 도서 정보 푸시
			tempbl.push_back(sample);
			bi++;
		}

		cout << "도서 정보 불러오기 성공" << endl;

		readFile.close();
		return tempbl;

	}
	else {
		perror("Fail to Open File");
		exit(-1);
	}
}


void File::export_book_list(vector<Book*>bl) {
	cout << "도서 정보 내보내기 중..." << endl;
	ofstream writeFile;
	writeFile.open(this->address);

	/*
	매개 변수에 저장된 Book들을 태그별로 파일쓰기 마지막 행은 개행문자를 생략
	여기로 넘어오는 데이터는 문법 검사들을 거친 올바른 데이터라 믿음
	*/
	if (writeFile.is_open()) {

		for (int i = 0; i < bl.size(); i++) {
			if (i == bl.size()-1)
			{
				writeFile << bl.at(i)->get_ID() << "\t";
				writeFile << bl.at(i)->get_Title() << "\t";
				writeFile << bl.at(i)->get_Author() << "\t";
				writeFile << bl.at(i)->get_Publisher() << "\t";
				writeFile << bl.at(i)->get_Date();
			}
			else {
				writeFile << bl.at(i)->get_ID() << "\t";
				writeFile << bl.at(i)->get_Title() << "\t";
				writeFile << bl.at(i)->get_Author() << "\t";
				writeFile << bl.at(i)->get_Publisher() << "\t";
				writeFile << bl.at(i)->get_Date() << endl;
			}

		}	

		writeFile.close();

		cout << "도서 정보 내보내기 성공" << endl;

	}
	else
	{
		perror("도서 정보 내보내기 실패 : Failed to open File\n");
		exit(-1);
	}

}

void File::export_book_unit(Book* bl){
	/*
	한 도서 정보 별로 파일에 데이터를 덮어 씌우거나 추가할 때
	*/
	ofstream readFile;
	readFile.open("");//파일의 링크가 들어갈 것
	if (!readFile.is_open()) {
		while (!readFile.eof())
		{

		}
	}
	else {
		perror("Failed to Open File");
		exit(-1);
	}
}

bool File::is_Right_Data(string s) {
	/*
	정규표현식 정교한 확인 필요
	*/
	regex data_check("^[0-9]+\t([ -~]\t)+(\t|\n)?");

	if (regex_match(s, data_check)) {
		return true;
	}
	else {
		return false;
	}
}

#include "FileIO.h"
using namespace std;

//�ش� ���Ͽ� ���� �͵��� �ùٸ��� �������� �˻簡 �ʿ���

vector<Book*> File::import_book_list()
{
	cout << "���� ���� �ҷ����� ��..." << endl;
	/*
	this->address ��ο� ����� ���Ϸ� ���� �����͸� �о���δ�
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
				cerr << endl << "�������� ������ �ùٸ��� �ʽ��ϴ�." << endl << endl;
				cout << "�ش� ������ ������ : " << book << endl << endl;
				cout << "�� â�� �������� �ƹ�Ű�� �����ּ���.";
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

			//�ߺ��Ǵ� ID�� �ִ��� �˻�
			int dup_flag = 0;
			for (int t = 0; t < tempbl.size(); t++)
			{
				if (tempbl.at(t)->get_ID() == atoi(samplebook[0].c_str()))
				{
					cout << "�̹� ������ �ִ� ID �߰� : " << samplebook[0] << endl;
					cout << "�� ������ ���� �ؽ�Ʈ ���Ͽ� ���������� ���α׷� �󿡼� ���ܵ˴ϴ�." << endl;
					cout << "���� ���� �������� ������ �簳�մϴ�" << endl << endl;
					dup_flag++;
					break;
				}
			}

			if (dup_flag > 0) {
				continue;
			}

			//���� ������ �±׺��� ����
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
			
			//���Ϳ� ���� ���� Ǫ��
			tempbl.push_back(sample);
			bi++;
		}

		cout << "���� ���� �ҷ����� ����" << endl;

		readFile.close();
		return tempbl;

	}
	else {
		perror("Fail to Open File");
		exit(-1);
	}
}


void File::export_book_list(vector<Book*>bl) {
	cout << "���� ���� �������� ��..." << endl;
	ofstream writeFile;
	writeFile.open(this->address);

	/*
	�Ű� ������ ����� Book���� �±׺��� ���Ͼ��� ������ ���� ���๮�ڸ� ����
	����� �Ѿ���� �����ʹ� ���� �˻���� ��ģ �ùٸ� �����Ͷ� ����
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

		cout << "���� ���� �������� ����" << endl;

	}
	else
	{
		perror("���� ���� �������� ���� : Failed to open File\n");
		exit(-1);
	}

}

void File::export_book_unit(Book* bl){
	/*
	�� ���� ���� ���� ���Ͽ� �����͸� ���� ����ų� �߰��� ��
	*/
	ofstream readFile;
	readFile.open("");//������ ��ũ�� �� ��
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
	����ǥ���� ������ Ȯ�� �ʿ�
	*/
	regex data_check("^[0-9]+\t([ -~]\t)+(\t|\n)?");

	if (regex_match(s, data_check)) {
		return true;
	}
	else {
		return false;
	}
}

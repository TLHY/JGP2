#pragma once
#include <string>

using namespace std;

class SubPrompt {
private:
	string message;
public:
	SubPrompt() {};
	SubPrompt(string m) {
		this->message = m;
	}

	virtual	bool is_real();
};

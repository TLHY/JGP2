#include <iostream>
#include "Subprompt.h"

bool SubPrompt::is_real() {
	cout << this->message << endl;

	while (true) {
		char answer;
		cin >> answer;

		if (answer == 'Y' || 'y')
		{
			return true;
		}
		else if (answer == 'N' || 'n')
		{
			return false;
		}
		else
		{
			cout << "다시 입력해 주세요" << endl;
			continue;
		}
	}
}
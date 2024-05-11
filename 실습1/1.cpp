#include "std_lib_facilities.h"

int main()
{
	string input;
	string originalInput;
	char targetChar;
	char cont = 'y';

	cout << "문자열을 입력하세요 : ";
	getline(cin, input);
	cout << "입력한 문자열 : " << input << '.' << '\n';
	originalInput = input;

	while (cont == 'y') {
		cout << "소문자를 입력하세요 : ";
		cin >> targetChar;
		cin.ignore();

		for (int i = 0; i < input.length(); ++i) {
			if (input[i] == targetChar || input[i] == targetChar + 32 || input[i] == targetChar - 32) {
				input[i] = '*';
			}
		}

		cout << "바뀐 문자열 : " << input << '\n';

		cout << "원래대로 되돌아가세요 : ";
		cin >> targetChar;

		input = originalInput;

		cout << "원래 : " << originalInput << '\n';

		cout << "계속 하시겠습니까? (y/n) : ";
		cin >> cont;
		cin.ignore();
	}
	while (cont == 'n') {
		int targetNum;
		cout << "0~5까지의 숫자를 입력하세요 : ";
		cin >> targetNum;
		cin.ignore();

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, 3);

		char randomChars[] = { '@', '%', '#', '.' };

		switch (targetNum) {
		case 1:
		{
			for (char& c : input) {
				if (c == ' ') {
					int randomIndex = dis(gen);
					c = randomChars[randomIndex];
				}
			}
			cout << "모든 공백에 다음 네문자 중 한 개를 넣고 출력 : " << input << '\n';
		}
		continue;

		case 2:
		{
			stringstream ss(originalInput);
			string word;
			int count = 0;

			while (ss >> word) {
				count++;
			}

			cout << "단어의 개수 : " << count << '\n';
		}
		continue;

		case 3:
		{
			for (char& c : input) {
				if (isupper(c)) {
					c = tolower(c);
				}
				else if (islower(c)) {
					c = toupper(c);
				}
			}
			cout << "대문자는 소문자로, 소문자는 대문자로 : " << input << '\n';
		}
		continue;

		case 4:
		{
			char firstChar = input[0];
			for (size_t i = 0; i < input.length() - 1; ++i) {
				input[i] = input[i + 1];
			}
			input[input.length() - 1] = firstChar;

			cout << "좌측으로 한 문자씩 이동 : " << input << '\n';
		}
		continue;

		case 5:
		{
			char lastChar = input[input.length() - 1];
			for (size_t i = input.length() - 1; i > 0; --i) {
				input[i] = input[i - 1];
			}
			input[0] = lastChar;

			cout << "우측으로 한 문자씩 이동 : " << input << '\n';
			continue;
		}
		case 0:
		{
			cout << "프로그램을 종료.\n";
			return 0;
		}
		cout << "계속 하시겠습니까? (y/n): ";
		cin >> cont;
		cin.ignore();
		}
	}
}
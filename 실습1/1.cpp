#include "std_lib_facilities.h"

int main()
{
	string input;
	string originalInput;
	char targetChar;
	char cont = 'y';

	cout << "���ڿ��� �Է��ϼ��� : ";
	getline(cin, input);
	cout << "�Է��� ���ڿ� : " << input << '.' << '\n';
	originalInput = input;

	while (cont == 'y') {
		cout << "�ҹ��ڸ� �Է��ϼ��� : ";
		cin >> targetChar;
		cin.ignore();

		for (int i = 0; i < input.length(); ++i) {
			if (input[i] == targetChar || input[i] == targetChar + 32 || input[i] == targetChar - 32) {
				input[i] = '*';
			}
		}

		cout << "�ٲ� ���ڿ� : " << input << '\n';

		cout << "������� �ǵ��ư����� : ";
		cin >> targetChar;

		input = originalInput;

		cout << "���� : " << originalInput << '\n';

		cout << "��� �Ͻðڽ��ϱ�? (y/n) : ";
		cin >> cont;
		cin.ignore();
	}
	while (cont == 'n') {
		int targetNum;
		cout << "0~5������ ���ڸ� �Է��ϼ��� : ";
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
			cout << "��� ���鿡 ���� �׹��� �� �� ���� �ְ� ��� : " << input << '\n';
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

			cout << "�ܾ��� ���� : " << count << '\n';
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
			cout << "�빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� : " << input << '\n';
		}
		continue;

		case 4:
		{
			char firstChar = input[0];
			for (size_t i = 0; i < input.length() - 1; ++i) {
				input[i] = input[i + 1];
			}
			input[input.length() - 1] = firstChar;

			cout << "�������� �� ���ھ� �̵� : " << input << '\n';
		}
		continue;

		case 5:
		{
			char lastChar = input[input.length() - 1];
			for (size_t i = input.length() - 1; i > 0; --i) {
				input[i] = input[i - 1];
			}
			input[0] = lastChar;

			cout << "�������� �� ���ھ� �̵� : " << input << '\n';
			continue;
		}
		case 0:
		{
			cout << "���α׷��� ����.\n";
			return 0;
		}
		cout << "��� �Ͻðڽ��ϱ�? (y/n): ";
		cin >> cont;
		cin.ignore();
		}
	}
}
#include "std_lib_facilities.h"

vector<int> printNum(const vector<int>& numbers) {
	int count = 0;
	for (int num : numbers) {
		cout << num << " ";
		count++;
		if (count % 10 == 0) {
			cout << '\n';
		}
	}
	cout << '\n';
	return numbers;
}

int main()
{
	int inputNum;
	char cont = 'y';
	cout << "숫자를 입력하세요 : ";
	cin >> inputNum;

	if (inputNum >= 100) {
		cout << inputNum << "보다 작은 랜덤한 수 50개" << '\n';

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(1, inputNum - 1);

		vector<int> numbers;

		for (int i = 0; i < 50; ++i) {
			numbers.push_back(dis(gen));
		}
		vector<int> originalNum = printNum(numbers);

		while (cont == 'y') {
			cout << "명령어를 입력하세요 : ";
			string command;
			cin >> command;
			cin.ignore();

			if (command == "a") {
				sort(numbers.begin(), numbers.end());
				cout << "오름차순으로 정렬" << '\n';
				printNum(numbers);
			}
			else if (command == "d") {
				sort(numbers.begin(), numbers.end(), greater<int>());
				cout << "내림차순으로 정렬" << '\n';
				printNum(numbers);
			}
			else if (command == "e") {
				cout << "3의 배수 출력" << '\n';
				int sum = 0;
				int count = 0;
				for (int num : numbers) {
					if (num % 3 == 0) {
						cout << num << " ";
						sum += num;
						count++;
						if (count % 10 == 0) {
							cout << '\n';
						}
					}
				}
				cout << '\n';
				cout << "3의 배수의 합계 : " << sum << '\n';
			}
			else if (command == "f") {
				cout << "5의 배수 출력" << '\n';
				int sum = 0;
				int count = 0;
				for (int num : numbers) {
					if (num % 5 == 0) {
						cout << num << " ";
						sum += num;
						count++;
						if (count % 10 == 0) {
							cout << '\n';
						}
					}
				}
				cout << '\n';
				cout << "5의 배수의 합계 : " << sum << '\n';
			}
			else if (command == "m") {
				cout << "3의 배수와 5의 배수 둘 다 출력" << '\n';
				int count = 0;
				for (int num : numbers) {
					if (num % 3 == 0 || num % 5 == 0) {
						cout << num << " ";
						count++;
						if (count % 10 == 0) {
							cout << '\n';
						}
					}
				}
				cout << '\n';
				cout << "1을 더한 값" << '\n';
				count = 0;
				for (int num : numbers) {
					if (num % 3 == 0 || num % 5 == 0) {
						cout << num + 1 << " ";
						count++;
						if (count % 10 == 0) {
							cout << '\n';
						}
					}
				}
			}
			else if (command == "n") {
				cout << "3의 배수와 5의 배수 둘 다 출력" << '\n';
				int count = 0;
				for (int num : numbers) {
					if (num % 3 == 0 || num % 5 == 0) {
						cout << num << " ";
						count++;
						if (count % 10 == 0) {
							cout << '\n';
						}
					}
				}
				cout << '\n';
				cout << "1을 뺀 값" << '\n';
				count = 0;
				for (int num : numbers) {
					if (num % 3 == 0 || num % 5 == 0) {
						cout << num - 1 << " ";
						count++;
						if (count % 10 == 0) {
							cout << '\n';
						}
					}
				}
			}
			else if (command == "r") {
				cout << "재정렬" << '\n';
				printNum(originalNum);
			}
			else if (command == "p") {
				int inputNum;
				char cont = 'y';
				cout << "숫자를 입력하세요 : ";
				cin >> inputNum;

				if (inputNum >= 100) {
					cout << inputNum << "보다 작은 랜덤한 수 50개" << '\n';

					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<> dis(1, inputNum - 1);

					vector<int> numbers;

					for (int i = 0; i < 50; ++i) {
						numbers.push_back(dis(gen));
					}
					vector<int> originalNum = printNum(numbers);
				}
			}
			else if (command == "Q") {
				break;
			}
				cout << "계속 하시겠습니까? (y/n) : ";
				cin >> cont;
				cout << '\n';
				cin.ignore();
			
		}
	}
	else if (inputNum < 100 && inputNum > 0) {
	cout << "에러" << '\n';
	}
}
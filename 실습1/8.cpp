#include "std_lib_facilities.h"
#include <ctime>
#include <conio.h>

const int SIZE = 49;
const int ROWS = 7;
const int COLS = 7;

void printBoard(char p1Pos, char p2Pos) {
    int board[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        board[i] = i;
    }

    for (int i = 0; i < SIZE; ++i) {
        if (board[i] == 3 || board[i] == 9 || board[i] == 10 || board[i] == 11 ||
            board[i] == 15 || board[i] == 17 || board[i] == 19 || board[i] == 22 ||
            board[i] == 21 || board[i] == 23 || board[i] == 25 || board[i] == 26 ||
            board[i] == 27 || board[i] == 29 || board[i] == 31 || board[i] == 33 ||
            board[i] == 37 || board[i] == 38 || board[i] == 39 || board[i] == 45) {
            cout << "      ";

        }
        else {
            cout << "  ㅁ  ";
        }

        if ((i + 1) % ROWS == 0 && i != 0) {
            cout << '\n';
            cout << '\n';
        }
    }
}

char getInput() {
    char input;
    input = _getch();
    return input;
}

int rollYut() {
    srand(time(0));
    return rand() % 5;
}

int main() {
    cout << "p를 눌러 게임을 시작해주세요" << '\n';
    bool showBoard = false;

    char p1Pos = SIZE;
    char p2Pos = SIZE;

    int currentPlayer = 1;

    while (true) {
        char input = getInput();
        if (input == 'p') {
            showBoard = true;
            printBoard(p1Pos, p2Pos);
        }
        if (input == '1' && currentPlayer == 1) {
                int yutResult = rollYut();
                cout << "p1의 윷 결과 : ";

                switch (yutResult) {
                case 0:
                    cout << "도";
                    break;
                case 1:
                    cout << "개";
                    break;
                case 2:
                    cout << "걸";
                    break;
                case 3:
                    cout << "윷";
                    break;
                case 4:
                    cout << "모";
                    break;
                }
                cout << '\n';

                printBoard(p1Pos, p2Pos);
                currentPlayer = 2;
            }
            if (input == '2' && currentPlayer == 2) {
                int yutResult = rollYut();
                cout << "p2의 윷 결과 : ";

                switch (yutResult) {
                case 0:
                    cout << "도";
                    break;
                case 1:
                    cout << "개";
                    break;
                case 2:
                    cout << "걸";
                    break;
                case 3:
                    cout << "윷";
                    break;
                case 4:
                    cout << "모";
                    break;
                }
                cout << '\n';

                printBoard(p1Pos, p2Pos);
                currentPlayer = 1;
            }
        }
    return 0;
}
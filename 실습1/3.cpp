#include "std_lib_facilities.h"
#include <set>

int main() {
    const int ROWS = 4;
    const int COLS = 5;

    uniform_int_distribution<> dis(1, 50);
    random_device rd;
    mt19937 gen(rd());

    vector<int> matrix(ROWS * COLS);
    vector<int> originalMatrix(ROWS * COLS);

    cout << "행렬값" << '\n';

    int max_width = 0;

    set<int> generated_numbers;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int new_num;
            do {
                new_num = dis(gen);
            } while (generated_numbers.count(new_num) > 0);

            matrix[i * COLS + j] = new_num;
            originalMatrix[i * COLS + j] = new_num;

            generated_numbers.insert(new_num);

            max_width = max(max_width, static_cast<int>(to_string(matrix[i * COLS + j]).size()));
            cout << setw(max_width) << matrix[i * COLS + j] << " ";
        }
        cout << '\n';
    }
    while (true) {
        cout << "명령어를 입력하세요" << '\n';
        string command;
        cin >> command;

        if (command == "a") {
            sort(matrix.begin(), matrix.end());
            cout << "오름차순으로 정렬" << '\n';
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    cout << setw(max_width) << matrix[i * COLS + j] << " ";
                }
                cout << '\n';
            }
        }
        else if (command == "d") {
            cout << "내림차순으로 정렬" << '\n';

            for (int j = COLS - 1; j >= 0; --j) {
                for (int i = 0; i < ROWS; ++i) {
                    cout << setw(max_width) << matrix[i * COLS + j] << " ";
                }
                cout << '\n';
            }
        }
        else if (command == "e") {
            cout << "짝수만" << '\n';
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (matrix[i * COLS + j] % 2 == 0) {
                        cout << setw(max_width) << matrix[i * COLS + j] << " ";
                    }
                    else {
                        cout << setw(max_width) << "0" << " ";
                    }
                }
                cout << '\n';
            }
        }
        else if (command == "o") {
            cout << "홀수만" << '\n';
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (matrix[i * COLS + j] % 2 == 1) {
                        cout << setw(max_width) << matrix[i * COLS + j] << " ";
                    }
                    else {
                        cout << setw(max_width) << "-" << " ";
                    }
                }
                cout << '\n';
            }
        }
        else if (command == "m") {
            int max_val = originalMatrix[0];
            cout << "최댓값 더하기" << '\n';
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (originalMatrix[i * COLS + j] > max_val) {
                        max_val = originalMatrix[i * COLS + j];
                    }
                }
            }
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    matrix[i * COLS + j] = originalMatrix[i * COLS + j] + max_val;
                    cout << setw(max_width) << matrix[i * COLS + j] << " ";
                }
                cout << '\n';
            }
        }
        else if (command == "n") {
            int min_val = originalMatrix[0];
            cout << "최솟값 빼기" << '\n';
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (originalMatrix[i * COLS + j] < min_val) {
                        min_val = originalMatrix[i * COLS + j];
                    }
                }
            }
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    matrix[i * COLS + j] = originalMatrix[i * COLS + j] - min_val;
                    cout << setw(max_width) << matrix[i * COLS + j] << " ";
                }
                cout << '\n';
            }
        }
        else if (command == "p") {
            matrix = originalMatrix;
            cout << "행의 값을 모두 더해 1열에 저장" << '\n';
            for (int i = 0; i < ROWS; ++i) {
                int row_sum = 0;
                for (int j = 0; j < COLS; ++j) {
                    row_sum += originalMatrix[i * COLS + j];
                }
                matrix[i * COLS] = row_sum;
            }
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    cout << setw(max_width) << matrix[i * COLS + j] << " ";
                }
                cout << '\n';
            }
        }
        else if (command == "u") {
            matrix = originalMatrix;
            cout << "열의 값을 모두 곱해 4열에 저장" << '\n';
            for (int j = 0; j < COLS; ++j) {
                int col_product = 1;
                for (int i = 0; i < ROWS; ++i) {
                    col_product *= matrix[i * COLS + j];
                }
                matrix[3 * COLS + j] = col_product;
            }
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    cout << setw(max_width) << matrix[i * COLS + j] << " ";
                }
                cout << '\n';
            }
        }
        else if (command == "r") {
            matrix = originalMatrix;
            cout << "기존의 것 재정렬" << '\n';
            shuffle(matrix.begin(), matrix.end(), gen);

            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    cout << setw(max_width) << matrix[i * COLS + j] << " ";
                }
                cout << '\n';
            }
        }
        else if (command == "s") {
            cout << "새로운 것" << '\n';
            matrix = originalMatrix;

            set<int> generated_numbers;

            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    int new_num;
                    do {
                        new_num = dis(gen);
                    } while (generated_numbers.count(new_num) > 0);

                    matrix[i * COLS + j] = new_num;
                    generated_numbers.insert(new_num);

                    cout << setw(max_width) << matrix[i * COLS + j] << " ";
                }
                cout << '\n';
            }
        }
        else if (command == "q") {
            cout << "종료" << '\n';
            break;
        }
    }
    return 0;
}
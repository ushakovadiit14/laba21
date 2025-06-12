#include "Header.h"
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    Tree tree;
    int choice;
    vector<int> V;

    cout << "Введите способ заполнения дерева:\n"
         << "1 - С клавиатуры\n"
         << "2 - Из файла\n"
         << "3 - Случайными числами\n";

    string choiceStr;
    while (true) {
        cout << "Ваш выбор: ";
        getline(cin, choiceStr);
        if (IsNumber(choiceStr)) {
            choice = stoi(choiceStr);
            if (choice >= 1 && choice <= 3) break;
        }
        cout << "Недопустимое значение. Введите 1, 2 или 3.\n";
    }

    switch (choice) {
        case 1: { // Ввод с клавиатуры
            string line;
            cout << "Введите числа через пробел: ";
            getline(cin, line);
            stringstream s(line);
            string numStr;
            bool hasInvalidChars = false;

            while (s >> numStr) {
                if (IsNumber(numStr)) {
                    V.push_back(stoi(numStr));
                } else if (!hasInvalidChars) {
                    cout << "Недопустимые символы пропущены.\n";
                    hasInvalidChars = true;
                }
            }

            if (V.empty()) {
                cout << "Ничего не введено.\n";
                return 1;
            }
            break;
        }
        case 2: { // Чтение из файла
            ifstream file("input.txt");
            if (!file.is_open()) {
                cout << "Не удалось открыть файл.\n";
                return 1;
            }

            string numStr;
            bool hasInvalidChars = false;

            while (file >> numStr) {
                if (IsNumber(numStr)) {
                    V.push_back(stoi(numStr));
                } else if (!hasInvalidChars) {
                    cout << "Недопустимые символы в файле пропущены.\n";
                    hasInvalidChars = true;
                }
            }

            file.close();
            if (V.empty()) {
                cout << "Файл не содержит допустимых чисел.\n";
                return 1;
            }
            break;
        }
        case 3: { // Генерация случайных чисел
            srand(time(0)); // Инициализация генератора случайных чисел

            string countStr;
            while (true) {
                cout << "Введите количество случайных чисел: ";
                getline(cin, countStr);
                if (IsNumber(countStr)) {
                    int count = stoi(countStr);
                    if (count > 0) {
                        for (int i = 0; i < count; i++) {
                            V.push_back(1 + rand() % 100); // Числа от 1 до 100
                        }
                        break;
                    }
                }
                cout << "Недопустимое значение. Введите положительное число.\n";
            }
            break;
        }
    }

    // Вставка чисел в дерево
    for (int num : V) {
        tree.insert(num);
    }

    cout << "\nЭлементы дерева: ";
    for (int num : V) {
        cout << num << " ";
    }
    cout << "\n\n";

    // Визуализация дерева
    cout << "Дерево:\n";
    tree.dump4();

    // Поиск второго максимума
    try {
        int secondMax = tree.findSecondMax();
        cout << "\nВторое максимальное значение: " << secondMax << "\n";
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}

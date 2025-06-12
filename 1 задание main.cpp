#include <string>
#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>
#include <stdexcept>
#include <memory>
#include <ctime>
#include <sstream>
#include <fstream>
#include "Header.h"
#include <queue>
using namespace std;

int main() {
    Tree Tree;
    int choice;
    vector<int> V;

    cout << "Введите способ заполнения дерева.\n"
    << "1 - Клавиатура\n"
    << "2 - iz faila\n"
    << "3 - Рандомом\n";
    
    string choiceStr;
    while (true) {
        getline(cin, choiceStr);
        if (IsNumber(choiceStr)) {
            choice = stoi(choiceStr);
            if (choice >= 1 && choice <= 3) break;
        }
        cout << "Недопустимое значение."<<endl<<" ";
    }

    switch (choice) {
    case 1: {
        string line;
        cout << "Введите числа через пробел : ";
        getline(cin, line);
        stringstream s(line);
        string numStr;
        bool net = false;

        while (s >> numStr) {
            if (IsNumber(numStr)) {
                V.push_back(stoi(numStr));
            }
            else if (!net) {
                cout << "Недопустимые символы пропущены" << endl;
                net = true;
            }
        }

        if (V.empty()) {
            cout << "Ничего не введено." << endl;
            return 1;
        }
        break;
    }
    case 2: {
        ifstream file("input.txt");
        if (!file.is_open()) {
            cout << "Не удалось открыть файл." << endl;
            return 1;
        }

        string numStr;
        bool net = false;

        while (file >> numStr) {
            if (IsNumber(numStr)) {
                V.push_back(stoi(numStr));
            }
            else if (!net) {
                cout << "Недопустимые символы в файле будут пропущены" << endl;
                net = true;
            }
        }

        file.close();
        if (V.empty()) {
            cout << "Файл не содержит допустимых значений." << endl;
            return 1;
        }
        break;
    }
    case 3: {
        string countStr;
        while (true) {
            cout << "Введите количество чисел: ";
            getline(cin, countStr);
            if (IsNumber(countStr)) {
                int count = stoi(countStr);
                if (count > 0) {
                    for (int i = 0; i < count; i++) {
                        V.push_back(1 + rand() % 100);
                    }
                    break;
                }
            }
            cout << "Недопустимое значение."<<endl;
        }
        break;
    }
    }

    cout << endl << "Элементы дерева: ";
    for (int num : V) {
        cout << num << " ";
    }
    cout << endl << endl;

    Tree.AddTree(V);
    Tree.dump4_print();
    cout << endl;
    cout << "Листья дерева справа налево: ";
    Tree.sheet_print();

    return 0;
}

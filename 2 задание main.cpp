MAIN
#include "Header.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    Tree tree;
    int choice, n;
    ifstream file("input.txt");

    cout << "Введите способ заполнения дерева:\n"
         << "1 - Клавиатура\n"
         << "2 - Рандомом\n"
         << "3 - Из файла\n";

    choice = Tree::getValidatedInt("Ваш выбор: ");

    switch (choice) {
    case 1:
        n = Tree::getValidatedInt("Введите N: ");
        for (int i = 0; i < n; i++) {
            int nu = Tree::getValidatedInt("Введите число: ");
            tree.addToTree(tree.root, nu);
        }
        break;
    case 2:
        n = Tree::getValidatedInt("Введите N: ");
        srand(time(0));
        cout<<"\nНачальное состояние дерева:\n";
        for (int i = 0; i < n; i++) {
            int num = rand() % 100;
            tree.addToTree(tree.root, num);
            cout << (tree.root, num) << " ";
        }
        cout << endl;
        break;
    case 3:
        if (!file.is_open()) {
            cout << "Ошибка открытия файла!\n";
            return 1;
        }
        int k;
        while (file >> k) {
            tree.addToTree(tree.root, k);
        }
        file.close();
        break;
    default:
        cout << "Некорректный выбор!\n";
        return 1;
    }

    cout << "Указатель на корень: " << tree.root << endl;
    if (tree.root)
        cout << "Значение корня: " << tree.root->key << endl;

    cout << "Наше дерево:\n";
    tree.dump4();

    cout << "Элементы в инфиксном порядке:\n";
    tree.printElements(tree.root);

    return 0;
}

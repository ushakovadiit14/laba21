
#include "Header.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

Tree::Tree() : root(nullptr) {}

void Tree::addToTree(Node*& tree, int data) {
    if (!tree) {
        tree = new Node(data);
        return;
    }
    if (data < tree->key)
        addToTree(tree->left, data);
    else
        addToTree(tree->right, data);
}

void Tree::printElements(Node* tree) const {
    if (!tree) return;
    printElements(tree->left);
    cout << tree->key << " ";
    printElements(tree->right);
}

int Tree::getValidatedInt(const char* prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            break;
        }
        cout << "Ошибка ввода! Пожалуйста, введите нормальное число.\n";
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
    return value;
}

void Tree::dump4() const {
    dump4Impl_print(root, true, {}, {}, {}, true, false, nullptr);
}

void Tree::dump4Impl_print(const Node* node, bool high,
    vector<string> const& lpref,
    vector<string> const& cpref,
    vector<string> const& rpref,
    bool is_root, bool is_left,
    shared_ptr<vector<vector<string>>> lines) const {
    if (!node) return;
    static string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";
    typedef vector<string> VS;
    auto VSCat = [](VS const& a, VS const& b) {
        auto r = a;
        r.insert(r.end(), b.begin(), b.end());
        return r;
    };

    if (is_root) lines = make_shared<vector<VS>>();

    if (node->left)
        dump4Impl_print(node->left, high,
            VSCat(lpref, high ? VS({ " ", " " }) : VS({ " " })),
            VSCat(lpref, high ? VS({ ch_ddia, ch_ver }) : VS({ ch_ddia })),
            VSCat(lpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })),
            false, true, lines);

    auto sval = to_string(node->key);
    size_t sm = is_left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);

    for (size_t i = 0; i < sval.size(); ++i)
        lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref,
            { string(1, sval[i]) }));

    if (node->right)
        dump4Impl_print(node->right, high,
            VSCat(rpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })),
            VSCat(rpref, high ? VS({ ch_rddia, ch_ver }) : VS({ ch_rddia })),
            VSCat(rpref, high ? VS({ " ", " " }) : VS({ " " })),
            false, false, lines);

    if (is_root) {
        VS out;
        for (size_t l = 0;; ++l) {
            bool last = true;
            string line;
            for (size_t i = 0; i < lines->size(); ++i)
                if (l < (*lines).at(i).size()) {
                    line += lines->at(i)[l];
                    last = false;
                }
                else line += " ";
            if (last) break;
            out.push_back(line);
        }
        for (size_t i = 0; i < out.size(); ++i)
            cout << out[i] << endl;
    }
}

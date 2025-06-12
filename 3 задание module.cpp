#include "Header.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

bool IsNumber(const string& str) {
    if (str.empty()) return false;
    int start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
    if (start == 1 && str.length() == 1) return false;
    for (int i = start; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

Tree::Tree() : root(nullptr) {}

Node* Tree::insertRec(Node* node, int val) {
    if (!node) return new Node(val);
    if (val < node->x)
        node->left = insertRec(node->left, val);
    else if (val > node->x)
        node->right = insertRec(node->right, val);
    return node;
}

void Tree::insert(int val) {
    root = insertRec(root, val);
}

int Tree::findSecondMax() {
    if (!root || (!root->left && !root->right)) {
        throw std::runtime_error("Дерево должно содержать хотя бы два узла");
    }

    Node* current = root;

    while (current) {
        // Случай 1: самый правый узел имеет левое поддерево
        if (current->right && !current->right->right && current->right->left) {
            Node* temp = current->right->left;
            while (temp->right) {
                temp = temp->right;
            }
            return temp->x;
        }

        // Случай 2: самый правый узел — лист, возвращаем его родителя
        if (current->right && !current->right->right && !current->right->left) {
            return current->x;
        }

        // Двигаемся вправо
        current = current->right;
    }

    // Если не зашли ни в одно условие — левое поддерево root содержит второй максимум
    Node* temp = root->left;
    while (temp->right) {
        temp = temp->right;
    }
    return temp->x;
}


void Tree::dump4() const {
    dump4Impl_print(root, true, {}, {}, {}, true, false, nullptr);
}

void Tree::dump4Impl_print(const Node* node, bool high,
    std::vector<std::string> const& lpref,
    std::vector<std::string> const& cpref,
    std::vector<std::string> const& rpref,
    bool is_root, bool is_left,
    std::shared_ptr<std::vector<std::vector<std::string>>> lines) const {
    if (!node) return;
    static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";
    typedef std::vector<std::string> VS;
    auto VSCat = [](VS const& a, VS const& b) {
        auto r = a;
        r.insert(r.end(), b.begin(), b.end());
        return r;
        };

    if (is_root) lines = std::make_shared<std::vector<VS>>();

    if (node->left)
        dump4Impl_print(node->left, high,
            VSCat(lpref, high ? VS({ " ", " " }) : VS({ " " })),
            VSCat(lpref, high ? VS({ ch_ddia, ch_ver }) : VS({ ch_ddia })),
            VSCat(lpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })),
            false, true, lines);

    auto sval = std::to_string(node->x);
    size_t sm = is_left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);

    for (size_t i = 0; i < sval.size(); ++i)
        lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref,
            { std::string(1, sval[i]) }));

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
            std::string line;
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
            std::cout << out[i] << std::endl;
    }
}

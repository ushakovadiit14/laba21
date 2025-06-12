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
#include <queue>
#include "Header.h"
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

Tree::~Tree() {
    Clear(root);
}

void Tree::Clear(Node* node) {
    if (node) {
        Clear(node->left);
        Clear(node->right);
        delete node;
    }
}

void Tree::addNode(Node*& node, int x) {
    if (!root) {
        root = new Node(x);
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* num = q.front();
        q.pop();

        if (!num->left) {
            num->left = new Node(x);
            return;
        }
        else {
            q.push(num->left);
        }

        if (!num->right) {
            num->right = new Node(x);
            return;
        }
        else {
            q.push(num->right);
        }
    }
}
void Tree::AddTree(const vector<int>& values) {
    for (int val : values) {
        addNode(root, val);
    }
}

void Tree::sheet_print() const {
    if (!root) return;
    sheet_prints(root);
}

void Tree::sheet_prints(const Node* node) const {
    if (!node) return;
    sheet_prints(node->right);
    if (!node->left && !node->right) {
        cout << node->x << " ";
    }
    sheet_prints(node->left);
}

void Tree::dump4_print() const {
    dump4Impl_print(root, true, {}, {}, {}, true, true, nullptr);
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

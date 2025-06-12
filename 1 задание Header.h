
#pragma once
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
using namespace std;

bool IsNumber(const string& str);

class Tree {
private:
    struct Node {
        int x;
        Node* left;
        Node* right;

        Node(int val) : x(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void dump4Impl_print(const Node* node, bool high,
        vector<string> const& lpref,
        vector<string> const& cpref,
        vector<string> const& rpref,
        bool is_root, bool is_left,
        shared_ptr<vector<vector<string>>> lines) const;

    void Clear(Node* node);
    void addNode(Node*& node, int value);
    void sheet_prints(const Node* node) const;

public:
    Tree();
    ~Tree();

    void sheet_print() const;
    void AddTree(const vector<int>& values);
    void dump4_print() const;
};

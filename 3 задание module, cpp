#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <memory>
#include <string>

using namespace std; 

bool IsNumber(const string& str);

struct Node {
    int x;
    Node* left;
    Node* right;
    Node(int val) : x(val), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Node* root;

    Tree();
    void insert(int val);
    int findSecondMax();
    void dump4() const;

private:
    Node* insertRec(Node* node, int val);
    void dump4Impl_print(const Node* node, bool high,
        std::vector<std::string> const& lpref,
        std::vector<std::string> const& cpref,
        std::vector<std::string> const& rpref,
        bool is_root, bool is_left,
        std::shared_ptr<std::vector<std::vector<std::string>>> lines) const;
};

#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Tree {
public:
    class Node {
    public:
        int key;
        Node* left;
        Node* right;
        Node(int val) : key(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Tree();
    void addToTree(Node*& tree, int data);
    void printElements(Node* tree) const;
    void dump4() const;
    static int getValidatedInt(const char* prompt);

private:
    void dump4Impl_print(const Node* node, bool high,
        vector<string> const& lpref,
        vector<string> const& cpref,
        vector<string> const& rpref,
        bool is_root, bool is_left,
        shared_ptr<vector<vector<string>>> lines) const;
};

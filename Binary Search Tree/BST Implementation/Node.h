#ifndef NODE_H
#define NODE_H
#include <iostream>

struct Node {
    // atributos de um Node
    int key;
    Node* left; 
    Node* right;

    //: key(k), left(l), right(r) - poderia usar isso ao lado do constrututor
    Node(int key, Node* left, Node* right) // Construtor
    {
        this->key = key;
        this->left = left;
        this->right = right;
    }

    ~Node() {
        std::cout << "node " << key << " deletado\n";
    }
};

#endif 
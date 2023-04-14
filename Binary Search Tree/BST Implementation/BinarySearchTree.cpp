#include <iostream>
#include "BinarySearchTree.h"

// Função que recebe uma raiz e uma chave, e então retorna null <=> key
// não está na árvore, ou retorna o ponteiro para o nó, caso contrário
Node* BST::search(Node *node, int key) {
    if (node==nullptr || node->key == key) { return node; }

    if (node->key < key) { return search(node->right, key); }
    else { return search(node->left, key); }
}

bool BST::contains(int key) {
    if (search(root, key) == nullptr) { return false; }
    else { return true; }
}

Node* BST::add(Node *node, int key) {
    if (node == nullptr) { return new Node(key, nullptr, nullptr); }
    if (node->key < key) { node->right = add(node->right, key); }
    else if (node->key > key) { node->left = add(node->left, key); }

    return node;
}
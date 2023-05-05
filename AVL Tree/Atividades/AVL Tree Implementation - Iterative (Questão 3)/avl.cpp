#include <iostream>
#include "node.h"
#include "avl.h"
#include <stack>
using namespace std;

// retorna a altura do nó.
int avl_tree::height(Node *node) {
    return (node == nullptr) ? 0 : node->height;
}

// retorna o balanço do nó.
int avl_tree::balance(Node *node) {
    return height(node->right) - height(node->left);
}

// realiza uma rotação simples a direita
Node* avl_tree::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

// realiza uma rotação simples a esquerda
Node* avl_tree::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->right),height(p->left));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

  // função recursiva privada que recebe uma raiz de arvore
// e uma chave e insere a chave na tree se e somente se 
// ela nao for repetida. Claro, tem que deixar AVL novamente

// Função iterativa que recebe a raiz de uma arvore e uma chave.
// Insere a chave na arvore se e somente se ela nao for repetida, a deixando AVL novamente
Node* avl_tree::add(Node *p, int key) {

    if (p == nullptr) { return new Node(key); }

    stack <Node*> nodeStack;
    Node *currentNode = p;
    while (currentNode != nullptr) {
        nodeStack.push(currentNode);
        if (currentNode->key == key) { return p; }
        else if (currentNode->key > key) { currentNode = currentNode->left; }
        else { currentNode = currentNode->right; }
    }

    Node *newNode = new Node(key);
    currentNode = nodeStack.top();
    if (currentNode->key > key) { currentNode->left = newNode; }
    else { currentNode->right = newNode; }

    while (!nodeStack.empty()) {
        currentNode = nodeStack.top();
        currentNode = fixup_node(currentNode, key);
        nodeStack.pop();

        if (!nodeStack.empty()) {
            Node *parentNode = nodeStack.top();
            if (parentNode->left == currentNode) { parentNode->left = currentNode; }
            else { parentNode->right = currentNode; }
        }
        else { p = currentNode; }
    }

    return p;
}

void avl_tree::add(int key) {
    root = add(root, key);
}
 
Node* avl_tree::fixup_node(Node *p, int key) {
    // recalcula a altura de p
    p->height = 1 + max(height(p->left),height(p->right));

    // calcula o balanço do p
    int bal = balance(p);

    if(bal >= -1 && bal <= 1) {
        return p;
    }

    if(bal < -1 && key < p->left->key) {
        p = rightRotation(p);
    }
    else if(bal < -1 && key > p->left->key) {
        p->left = leftRotation(p->left);
        p = rightRotation(p);
    }
    else if(bal > 1 && key > p->right->key) {
        p = leftRotation(p);
    }
    else if(bal > 1 && key < p->right->key) {
        p->right = rightRotation(p->right);
        p = leftRotation(p);
    }
    return p;
}

void avl_tree::clear() {
    root = clear(root);
}

Node *avl_tree::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

avl_tree::~avl_tree() {
    clear();
}

void avl_tree::bshow() const {
    bshow(root, "");
}

void avl_tree::bshow(Node *node, std::string heranca) const {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}
#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
using namespace std;

/******************************
 * Definicao do struct Node
 ******************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/***********************************
 * Declaracao da classe
 ***********************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    void preorder();  // --> Implementar
    void inorder();   // --> Implementar
    void clear();     // --> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
};

/***********************************
 * Implementacao da classe
 ***********************************/
BST::BST() {
    root = nullptr;
}
 
BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow(){
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
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

BST::~BST() {
    clear();
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    //TODO: adicione aqui o codigo feito no primeiro exercicio
    if (root == nullptr) { root = new Node(k); return true; }
    Node *node = root;
    while (node != nullptr) {
        if (node->key == k) { return false; }
        else if (node->key < k) {
            if (node->right == nullptr) { node->right = new Node(k); return true; }
            else { node = node->right; }
        }
        else if (node->key > k) {
            if (node->left == nullptr) { node->left = new Node(k); return true; }
            else { node = node->left; }
        }
    }
    return false;
}

// Funcao publica 'preorder'
// Percorre os nos da arvore em pre-ordem imprimindo os 
// valores das chaves. Dica: use a estrutura de dados pilha (stack)
void BST::preorder() {
    stack<Node* > nodeStack; // Pilha nodeStack que armazena ponteiros para nós
    nodeStack.push(this->root); // Empilha a raíz da árvore
    while (!(nodeStack.empty())) {
        Node *currentNode = nodeStack.top();
        nodeStack.pop();
        if (currentNode != nullptr) {
            cout << currentNode->key << " ";
            nodeStack.push(currentNode->right);
            nodeStack.push(currentNode->left);
        }
    }
}

// Funcao publica 'inorder'
// Percorre os nos da arvore em ordem simetrica imprimindo os 
// valores das chaves. Dica: use a estrutura de dados pilha (stack)
void BST::inorder() {
    stack<Node* > nodeStack; // Pilha nodeStack que armazena ponteiros para nós
    Node *currentNode = this->root;
    while (!(nodeStack.empty()) || currentNode != nullptr) {
        if (currentNode != nullptr) {
            nodeStack.push(currentNode);
            currentNode = currentNode->left;
        }
        else {
            currentNode = nodeStack.top();
            nodeStack.pop();
            cout << currentNode->key << " ";
            currentNode = currentNode->right;
        }
    }
}

// Funcao publica 'clear'
// Libera todos os nos da arvore deixando ela vazia.
// Dica: use a estrutura de dados pilha (stack)
void BST::clear() {
    stack<Node* > nodeStack; // Pilha nodeStack que armazena ponteiros para nós
    Node *currentNode = this->root;
    while (!(nodeStack.empty()) || currentNode != nullptr) {
        while (currentNode != nullptr) {
            nodeStack.push(currentNode);
            currentNode = currentNode->left;
        }
        currentNode = nodeStack.top();
        nodeStack.pop();
        Node *rightNode = currentNode->right;
        delete currentNode;
        currentNode = rightNode;
    }
    this->root = nullptr;
}
//alteração

#endif 
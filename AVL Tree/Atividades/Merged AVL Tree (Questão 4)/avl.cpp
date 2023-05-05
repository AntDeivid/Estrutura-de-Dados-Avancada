#include <iostream>
#include "node.h"
#include "avl.h"
using namespace std;

// retorna a altura do nó.
// se a arvore for vazia ela tem altura 0
// caso contrario, retorna o valor que está no campo height
int avl_tree::height(Node *node) {
    return (node == nullptr) ? 0 : node->height;
}

int avl_tree::balance(Node *node) {
    return height(node->right) - height(node->left);
}

Node* avl_tree::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

Node* avl_tree::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->right),height(p->left));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

// função pública que recebe uma chave e a insere
// somente se ela não for repetida
void avl_tree::add(int key) {
    root = add(root, key);
}

  // função recursiva privada que recebe uma raiz de arvore
// e uma chave e insere a chave na tree se e somente se 
// ela nao for repetida. Claro, tem que deixar AVL novamente
Node* avl_tree::add(Node *p, int key) {
    if(p == nullptr)
        return new Node(key);
    if(key == p->key) 
        return p;
    if(key < p->key)
        p->left = add(p->left, key);
    else 
        p->right = add(p->right, key);
    
    p = fixup_node(p, key);

    return p;
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

// Processa a árvore em ordem simétrica
void avl_tree::inorder(Node* node, vector<int>& keys) {
    if(node != nullptr) { // Caso geral: arvore nao vazia
        inorder(node->left, keys);
        keys.push_back(node->key);
        inorder(node->right, keys);
    }
}

// Ordena um vetor com base em outros dois
vector<int> vectorOrdenado(vector<int>& keys1, vector<int>& keys2) {

    vector<int> keys;

    int i = 0, j = 0;
    while (i < keys1.size() && j < keys2.size()) {
        if (keys1[i] < keys2[j]) { keys.push_back(keys1[i]); i++; }
        else { keys.push_back(keys2[j]); j++; }
    }

    // Insere as chaves restantes da primeira árvore
    while (i < keys1.size()) { keys.push_back(keys1[i]); i++; }

    // Insere as chaves restantes da segunda árvore
    while (j < keys2.size()) { keys.push_back(keys2[j]); j++; }

    return keys;
}

// constroi a árvore
void construir(avl_tree *t, vector<int>& keys, int p, int q) {
	if (p > q) { return; } // Se não houver mais elementos no vetor, retorna e encerra a função
	int indiceMedio = (p + q) / 2; // Para que a árvore seja balanceada, o índice médio deve ser o nó raiz
	t->add(keys[indiceMedio]);
	construir(t, keys, p, indiceMedio-1); // Criando a subárvore esquerda
	construir(t, keys, indiceMedio+1, q); // Criando a subárvore direita
}

avl_tree *avl_tree::mergeTrees(avl_tree &av1, avl_tree &av2) {
    // Nova árvore
    avl_tree *newTree = new avl_tree();

    // Percorre as duas arvores em ordem simétrica e armazena as chaves em vetores
    vector<int> keys1, keys2;
    inorder(av1.root, keys1);
    inorder(av2.root, keys2);
    // Cria um vector ordenado com base nos dois vetores
    vector<int> keys = vectorOrdenado(keys1, keys2);

    // Chama a função construir para criar a nova árvore
    construir(newTree, keys, 0, keys.size()-1);

    return newTree;
    
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
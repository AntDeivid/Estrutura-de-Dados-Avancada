#ifndef BST_H
#define BST_H
#include <iostream>
#include <stack>
#include <string>
using namespace std;

/***********************************
 * Definicao do struct Node
 ***********************************/
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
    bool add(int k); // ---> Implementar
    bool contains(int k); // ---> Implementar
    void inorderParent();
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *clear(Node *node); 
    Node *search(int k); // ---> Implementar
};

/************************************
 * Implementacao da classe
 ************************************/
// Constructor 1
BST::BST() {
    root = nullptr;
}

// Constructor 2
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

Node *BST::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

BST::~BST() {
    root = clear(root);
}

// Percorre os nos da arvore em ordem simetrica, imprimindo os pais
void BST::inorderParent() {
    stack<Node*> p; // Cria pilha do tipo Node* (ponteiro para Node)
    if(root != nullptr)
        p.push(root);
    while(!p.empty()) {
        Node *no = p.top();
        p.pop();
        if(no->parent != nullptr) cout << no->parent->key << " ";
        if(no->right != nullptr) p.push(no->right);
        if(no->left != nullptr) p.push(no->left);
    }
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    // Criando novo nó com chave 'k'
    Node *newNode = new Node(k);
    // Se a árvore for vazia, o novo nó torna-se a sua raíz
    if (root == nullptr) { root = newNode; return true; }

    Node *currentNode = root; // Nó auxiliar criado para percorrer a árvore
    Node *noPai = nullptr;
    //Enquanto currentNode não for nulo, o loop continua
    while (currentNode != nullptr) {
        noPai = currentNode;
        //Caso a chave já existe na árvore
        if (currentNode->key == k) { return false; }
        // Teste condicional para saber se deve descer pela subárvore esquerda ou direita
        if (k < currentNode->key) { currentNode = currentNode->left; }
        else if (k > currentNode->key) { currentNode = currentNode->right; }
    }
    // noPai se torna o nó pai do novo nó
    newNode->parent = noPai;
    // Teste condicional para saber se newNode será filho esquerdo ou direito
    if (newNode->key < noPai->key) { noPai->left = newNode; }
    else { noPai->right = newNode; }

    return true; // Se a função chegar até o fim, significa que o nó foi adicionado com sucesso
}

// Funcao privada 'search'
// Esta funcao devolve o ponteiro para o no que 
// contem a chave k se ela existir na arvore;
// caso contrario, devolve nullptr;
Node *BST::search(int k) {
    Node *currentNode = root; // Nó auxiliar criado para percorrer a árvore

    while (currentNode != nullptr) {
        if (currentNode->key == k) { return currentNode; } // Se a chave do nó atual for igual a k, retorna ele
        // Teste condicional para saber se deve descer pela subárvore esquerda ou direita
        else if (k < currentNode->key) { currentNode = currentNode->left; }
        else if (k > currentNode->key) { currentNode = currentNode->right; }
    }

    // Se a função chegar até o final, significa que o valor não foi encontrado na árvore e retorna nullptr
    return nullptr;
}

// Funcao publica 'contains'
// Esta funcao devolve 'true' se a arvore contem a chave k; 
// e devolve 'false' caso contrário.
bool BST::contains(int k) {
    return (search(k) != nullptr);
}

#endif 
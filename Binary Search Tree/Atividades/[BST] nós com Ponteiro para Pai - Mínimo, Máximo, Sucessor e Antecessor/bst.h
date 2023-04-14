#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
#include <climits>
using namespace std;

/*****************************
 * Definicao do struct Node
 *****************************/
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

/************************
 * Declaracao da classe
 ************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    int minimum();           // ---> Implementar
    int maximum();           // ---> Implementar
    int predecessor(int k);  // ---> Implementar
    int successor(int k);    // ---> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *minimum(Node *node);       // ---> Implementar
    Node *maximum(Node *node);       // ---> Implementar
    Node *successor(Node *node);     // ---> Implementar
    Node *predecessor(Node *node);     // ---> Implementar
    Node *clear(Node *node);
    Node *search(int k);
};

/*****************************
 * Implementacao da classe
 *****************************/
// Construtor 
BST::BST() {
    root = nullptr;
}

// Construtor 
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

    while (currentNode != nullptr && currentNode->key != k) {
        // Teste condicional para saber se deve descer pela subárvore esquerda ou direita
        if (k < currentNode->key) { currentNode = currentNode->left; }
        else { currentNode = currentNode->right; }
    }

    // Se a função chegar até o final, significa que o valor não foi encontrado na árvore e retorna nullptr
    return currentNode;
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o menor valor de chave da arvore.
int BST::minimum() {
    return minimum(root)->key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a menor chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::minimum(Node *node) {
    /*if (node == nullptr) { return nullptr; }

    Node *currentNode = node; // Nó auxiliar criado para percorrer a árvore
    Node *minimo = currentNode;
    while (currentNode != nullptr) {
        // Comparação a cada início de iteração, verificando se a nova chave de currentNode é menor que minimo
        if(currentNode->key < minimo->key) { minimo->key = currentNode->key; }
        // Como estamos falando de uma bst, o valor minimo sempre estará à esquerda.
        // Logo, enquanto puder ir à esquerda, irá.
        if (currentNode->left != nullptr) { currentNode = currentNode->left; }
        // Em último caso, o currentNode vai para a direita, visto que pode haver subárvores à esquerda
        // desse nó que possuam um nó com uma chave menor
        else { currentNode = currentNode->right; }
    }

    return minimo; // Retorna minimo*/

    if (node == nullptr) { return nullptr; } // Se o nó for nulo, logo é retornado nullptr

    while (node->left != nullptr) { node = node->left; } // Como se trata de uma árvore binária de busca, o menor nó vai estar o máximo à esquerda
    return node;
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o maior valor de chave da arvore
int BST::maximum() {
    return maximum(this->root)->key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a maior chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::maximum(Node *node) {
    /*if (node == nullptr) { return nullptr; }

    Node *currentNode = node; // Nó auxiliar criado para percorrer a árvore
    Node *maximo = currentNode;
    while (currentNode != nullptr) {
        // Comparação a cada início de iteração, verificando se a nova chave de currentNode é maior que maximo
        if(currentNode->key > maximo->key) { maximo->key = currentNode->key; }
        // Como estamos falando de uma bst, o valor maximo sempre estará à direita.
        // Logo, enquanto puder ir à direita, irá.
        if (currentNode->right != nullptr) { currentNode = currentNode->right; }
        // Em último caso, o currentNode vai para a esquerda, visto que pode haver subárvores à direita
        // desse nó que possuam um nó com uma chave menor
        else { currentNode = currentNode->left; }
    }

    return maximo; // Retorna maximo*/

    if (node == nullptr) { return nullptr; } // Se o nó for nulo, logo é retornado nullptr

    while (node->right != nullptr) { node = node->right; } // Como se trata de uma árvore binária de busca, o maior nó vai estar o máximo à direita
    return node;
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MAX se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem sucessor
// (2) caso contrario, devolve o valor inteiro da 
// chave sucessora de k quando esta existe
int BST::successor(int k) {
    // A função search(k) retorna um ponteiro para o nó com chave k.
    // Após, a função privada successor é chamada e busca o sucessor do nó retornado em search
    // e então atribui a successorNode.
    Node *successorNode = successor(search(k));
    if (successorNode != nullptr) { return successorNode->key; } // Se for diferente de nullptr, retorna a chave do nó sucessor
    return INT_MAX; // Caso contrário, retorna INT_MAX
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem sucessor; ou
// (2) caso contrario, devolve o ponteiro para o no sucessor de node.
Node *BST::successor(Node *node) {
    if (node == nullptr) { return nullptr; } // Se o nó for nulo, logo é retornado nullptr
    // Caso sua subárvore direita não seja vazia, a função minimum encontra o mínimo valor maior que node
    if (node->right != nullptr) { return minimum(node->right); }

    Node *currentNode = this->root; // Nó criado para percorrer a árvore
    Node *searcher = nullptr; // Nó auxiliar
    while (currentNode != node) { // Até que chegue ao node
        // Condicionais para encontrar o menor antes de node
        if (currentNode->key < node->key) { currentNode = currentNode->right; }
        else { searcher = currentNode; currentNode = currentNode->left; }
    }
    return searcher;
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MIN se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem antecessor;
// (2) caso contrario, devolve o valor inteiro da chave 
// antecessora de k quando esta existe.
int BST::predecessor(int k) {
    // A função search(k) retorna um ponteiro para o nó com chave k.
    // Após, a função privada predecessor é chamada e busca o antecessor do nó retornado em search
    // e então atribui a predecessorNode.
    Node *predecessorNode = predecessor(search(k));
    if (predecessorNode != nullptr) { return predecessorNode->key; } // Se for diferente de nullptr, retorna a chave do nó antecessor
    return INT_MIN; // Caso contrário, retorna INT_MIN
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem antecessor; ou
// (2) caso contrario, devolve o ponteiro para o no antecessor de node.
Node *BST::predecessor(Node *node) {
    if (node == nullptr) { return nullptr; } // Se o nó for nulo, logo é retornado nullptr

    // Mesma lógica aplicada na função successor(), no entanto, buscando o antecessor.
    Node *currentNode = this->root;
    Node *searcher = nullptr;

    while (currentNode != node) {
        if (currentNode->key > node->key) { currentNode = currentNode->left; }
        else { searcher = currentNode; currentNode = currentNode->right; }
    }
    
    return searcher;
}

#endif 
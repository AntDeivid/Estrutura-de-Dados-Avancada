#include <iostream>
#include "avl.h"
using namespace std;

int main() {

    system("chcp 65001 > nul");

    avl_tree *t1 = new avl_tree;
    avl_tree *t2 = new avl_tree;

    for(int i = 1; i <= 15; i++) {
        t1->add(i);
    }

    for(int i = 16; i <= 30; i++) {
        t2->add(i);
    }

    cout << "Arvore 1:" << endl;
    t1->bshow();
    cout << "Arvore 2:" << endl;
    t2->bshow();

    avl_tree *t3 = t1->mergeTrees(*t1, *t2);
    cout << "Arvore 3:" << endl;
    t3->bshow();
}
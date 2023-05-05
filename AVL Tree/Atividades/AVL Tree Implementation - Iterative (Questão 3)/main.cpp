#include <iostream>
#include "avl.h"
using namespace std;

int main() {

    system("chcp 65001 > nul");

    avl_tree *t = new avl_tree;

    for(int i = 1; i <= 50; i++) {
        t->add(i);
    }

    t->bshow();
}
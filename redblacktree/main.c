/*
    Program do zabawy z bibliotkeką
*/
#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

int main () {

    pnode root = init();

    while (1) {
        int op, klu;
        scanf("%d %d", &op, &klu);
        if (op == 1) {
            insert(&root, klu);
        }
        else {
            pnode v = find(root, klu);
            if (v != NIL)
                deletenode(&root, v);
        }
        info(root);
    }

    return 0;
}
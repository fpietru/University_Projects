#ifndef RB_TREE
#define RB_TREE

#define RED 1
#define BLACK 0

typedef struct node {
    int klucz;
    int kolor;
    struct node *lewy, *prawy, *p;
} node, *pnode;
extern pnode NIL;

pnode init();
pnode newnode(int klu, int kol);
void print(pnode v, int lvl);
void info(pnode root);
void rotacja_w_lewo(pnode *root, pnode x);
void rotacja_w_prawo(pnode *root, pnode x);
void napraw_insert(pnode *root, pnode v);
void insert(pnode *root, int klu);
void przeszczep(pnode *root, pnode v, pnode u);
pnode minimum(pnode v);
void napraw_remove(pnode *root, pnode x);
void deletenode(pnode *root, pnode z);
pnode find(pnode v, int klu);


#endif // RB_TREE
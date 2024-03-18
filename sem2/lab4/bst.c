#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int klucz;
	struct node *lewy, *prawy;
} node, *pnode;

pnode newnode(int k) {
	pnode v = malloc(sizeof(node));
	v->klucz = k;
	v->lewy = NULL;
	v->prawy = NULL;
}

void insert(pnode *v, int k) {
	if ((*v) == NULL) {
		*v = newnode(k);
		return;
	}
	if (k < (*v)->klucz) insert(&((*v)->lewy), k);
	else insert(&((*v)->prawy), k);
}

void print(pnode v) {
	if (v == NULL) return;
	print(v->lewy);
	printf("%d ", v->klucz);
	print(v->prawy);
}

int main () {
	pnode root = NULL;

	insert(&root, 5);
	insert(&root, 2);
	insert(&root, 1);
	insert(&root, 7);
	insert(&root, 9);

	print(root);
	

	return 0;
}
/*
    Zadanie: Napisać funkcję, która usuwa wszystkie powtórzenia z posortowanej pnodey
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int wart;
	struct node *next;
} node, *pnode;

void push(pnode *h, int a) {
	pnode u = malloc(sizeof(node));
	u->wart = a;
	u->next = *h;
	*h = u;
}

void pop(pnode *h) {
	if (*h != NULL) {
		pnode u = *h;
		*h = (*h)->next;
		free(u);
	}
}

void print(pnode h) {
	while (h != NULL) {
		printf("%d ", h->wart);
		h = h->next;
	}
	printf("\n");
}

void zpliku(pnode *h) {
	FILE *fin = fopen("./dane.txt", "r");
	int a;
	while (fscanf(fin, "%d", &a) != EOF)
		push(h, a);
	fclose(fin);
}

void usunpowtorzenia(pnode h) {
	pnode pom;
    while (h != NULL) {
        while (h->next != NULL && h->wart == (h->next)->wart) {
            pom = h->next;
            h->next = (h->next)->next;
            free(pom);
        }
        h = h->next;
    }
}

int main () {
	pnode head = NULL;
	
	zpliku(&head);
    print(head);
    usunpowtorzenia(head);
    print(head);
	
	return 0;
}

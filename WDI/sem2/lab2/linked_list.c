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

pnode find(pnode h, int a) {
	while ((h!=NULL) && (h->wart!=a))
		h = h->next;
	return h;
}

int size(pnode h) {
	int res = 0;
	while (h != NULL) {
		res++;
		h = h->next;
	}
	return res;
}

void print(pnode h) {
	while (h != NULL) {
		printf("%d ", h->wart);
		h = h->next;
	}
	printf("\n");
}

void wczytaj(pnode *h) {
	int a;
	while (scanf("%d", &a) > 0)
		push(h, a);
}

void zpliku(pnode *h) {
	FILE *fin = fopen("dane.txt", "r");
	int a;
	while (fscanf(fin, "%d", &a) != EOF)
		push(h, a);
	fclose(fin);
}

// Rozdziel listę na dwie prawie równe połowy
void split(pnode *h, pnode *h2) {
	pnode pocz = *h;
	int sz = size(*h);
	for (int i=1; i<sz/2; i++)
		(*h) = (*h)->next;
	
	(*h2) = (*h)->next;
	(*h)->next = NULL;
	(*h) = pocz;
}

int main () {
	pnode head = NULL;

	zpliku(&head);	
	print(head);
	
	printf("%d\n", size(head));
	
	pnode head2 = NULL;
	split(&head, &head2);
	print(head);
	print(head2);
	
	
	return 0;
}

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

void print(pnode h) {
	while (h != NULL) {
		printf("%d ", h->wart);
		h = h->next;
	}
	printf("\n");
}

// przeszczep pierwszego node'a z listy n1 na początek listy n2
void przeszczep(pnode *n1, pnode *n2) {
	pnode pom = *n1;
	(*n1) = (*n1)->next;
	pom->next = *n2;
	(*n2) = pom;
}

// odwróć listę
void reverse(pnode *h) {
	pnode h2 = NULL;
	while ((*h) != NULL)
		przeszczep(h, &h2);
	(*h) = h2;
}

// połącz dwie posortowane listy w jedną też posortowaną listę
pnode merge(pnode h, pnode h2) {
	node res_pocz;
	pnode res = &res_pocz;
	res->next = NULL;
	while (1) {
		if (h == NULL) {
			res->next = h2;
			break;
		}
		else if (h2 == NULL) {
			res->next = h;
			break;
		}
		if (h->wart <= h2->wart) przeszczep(&h, &(res->next));
		else przeszczep(&h2, &(res->next));
		res = res->next;
	}
	return (res_pocz.next);
}

int main () {
	pnode head = NULL;
	pnode h2 = NULL;
	
	push(&head, 5);
	push(&head, 4);
	push(&head, 3);
	push(&head, 2);
	push(&head, 1);

	push(&h2, 5);
	push(&h2, 5);
	push(&h2, 4);
	push(&h2, 4);
	push(&h2, 3);
	
	
	print(head);
	print(h2);
	
	pnode merged = merge(head, h2);
	print(merged);

	reverse(&merged);
	print(merged);

	return 0;
}

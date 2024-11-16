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

void print(pnode h) {
	while (h != NULL) {
		printf("%d ", h->wart);
		h = h->next;
	}
	printf("\n");
}

int main () {
	pnode head = NULL;
	
	push(&head, 1);
	push(&head, 2);
	push(&head, 3);
	push(&head, 4);
	
	print(head);
	
	push(&head, 5);
	
	print(head);
	
	pop(&head);
	pop(&head);
	
	print(head);
	
	
	return 0;
}

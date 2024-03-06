#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int wart;
	struct Node *next;
} Node, *list;

void push(list *h, int a) {
	list u;
	u = malloc(sizeof(Node));
	u->wart = a;
	u->next = *h;
	*h = u;
}

void pop(list *h) {
	list u;
	if (*h != NULL) {
		u = *h;
		*h = (*h)->next;
		free(u);
	}
}

list find(list h, int a) {
	while ((h!=NULL) && (h->wart!=a))
		h = h->next;
	return h;
}

void print(list h) {
	while (h != NULL) {
		printf("%d ", h->wart);
		h = h->next;
	}
	printf("\n");
}

int main () {
	list head = NULL;
	
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

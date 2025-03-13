#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *left, *right;
} Node, *Tree;

void insert(Tree* v, int x) {
  if (*v == NULL) {
    (*v) = malloc(sizeof(Node));
    (*v)->value = x;
    (*v)->left = NULL;
    (*v)->right = NULL;
  } else {
    int val = (*v)->value;
    if (val == x) return;
    if (x > val)
      insert(&(*v)->right, x);
    else
      insert(&(*v)->left, x);
  }
}

void printAll(Tree v) {
  if (v == NULL) return;
  printAll(v->left);
  printf("%d\n", v->value);
  printAll(v->right);
}

void removeAll(Tree v) {
  if (v->left != NULL) {
    removeAll(v->left);
    free(v->left);
  }
  if (v->right != NULL) {
    removeAll(v->right);
    free(v->right);
  }
}

int main() {
  Tree root = NULL;

  int x;
  while (scanf("%d", &x) != EOF) {
    insert(&root, x);
  }

  printAll(root);
  removeAll(root);
  free(root);

  return 0;
}
/*
    Franciszek Pietrusiak
    Zadanie 4
    Podany kod podstawowych operacji na drzewach BST uzupełnij o funkcję,
    która zwraca różnicę sumy wartości w wierzchołkach leżących w parzystej
    odległości od korzenia i sumy wartości w wierzchołkach leżących w nieparzystej 		odległości od korzenia.
*/
#include<stdio.h>
#include<stdlib.h>


// wierzcholek
typedef struct node {
  int key;
  struct node * left, * right, * up;  
} node, *tree;

tree root;

// inicjalizacja drzewa
void init(tree *r) {
  *r = NULL;
}

// szukanie klucza
tree find(tree r, int a) {
  if (r == NULL || r->key == a) return r;
  else 
    if (a < r->key) return find(r->left, a);
    else return find(r->right, a);
}

// wypisywanie wartosci w wierzcholkach jako posortowanego ciagu
void printBST(tree r) {
  if (r!=NULL) {
    printBST(r->left);
    printf("%d ", r->key);
    printBST(r->right);
  }
}

// nowy element drzewa
tree nowy(int a) {
  tree w = malloc(sizeof(node));
  w->key = a;
  w->left = NULL;
  w->right = NULL;
  w->up = NULL;
  return w;
}


// wstawianie do drzewa
void dodaj(tree *r, tree w) {
  if ((*r)==NULL) {*r = w;}
  else {
    if ((*r)->key < w->key) {
      if ((*r)->right !=NULL) dodaj(&((*r)->right), w);
      else {
        w->up = *r;
        (*r)->right = w;
      }
    } else {
      if ((*r)->left !=NULL) dodaj(&((*r)->left), w);
      else {
        w->up = *r;
        (*r)->left = w;
      }
    }
  }
}


// wczytywanie drzewa z pliku o podanej nazwie
void wczytajplik(tree *r, char *nazwa) {
  FILE *f;
  f = fopen(nazwa, "r");
  int w;
  while (fscanf(f, "%d", &w) != EOF) {
    dodaj(&root, nowy(w));
  }
  fclose(f);
  return;
}

long long funkcja(tree v, int dist) {
    if (v == NULL)
        return 0LL;
    long long dodaj = v->key;
    if (dist % 2 == 1)
        dodaj *= -1;
    return (funkcja(v->left, dist+1) + dodaj + funkcja(v->right, dist+1));
}

int main() {
  init(&root);
  wczytajplik(&root, "drzewo");
  printBST(root);

    long long res = funkcja(root, 0);
    printf("\n[%lld] <- Odpowiedz\n", res);

  return 0;
}

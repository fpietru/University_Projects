#include <bits/stdc++.h>
using namespace std;

/*
 0  1  2  3
[1, 2, 3] 4
4 - 1 = 3
3 / 2 = 1
*/

// trick na swapa bez zmiennej pomocniczej
void xorswap(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void lustro1(int tab[], int p, int k) {
    k--;
    for (int i=0; i<(k-p+1)/2; i++) {
        xorswap(&tab[p+i], &tab[k-i]);
    }
}

void lustro2(int *tab, int p, int k) {
    k--;
    for (int i=0; i<(k-p+1)/2; i++) {
        xorswap(&tab[p+i], &tab[k-i]);
    }
}

void lustro3(int *p, int *k) {
    k--;
    for (int i=0; i<(k-p+1)/2; i++) {
        xorswap((p+i), (k-i));
    }
}

void lustro4(int tab[], int p, int k) {
    k--;
    for (int i=0; i<(k-p+1)/2; i++) {
        swap(tab[p+i], tab[k-i]);
    }
}


int main () {
    int n = 6;
    //           0  1  2  3  4  5
    int tab[] = {1, 2, 3, 4, 5, 6};
    lustro4(tab, 1, 4);

    for (int i=0; i<n; i++)
        cout << tab[i] << " ";
    cout << "\n";

    return 0;
}
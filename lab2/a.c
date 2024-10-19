#include <stdio.h>

int swap(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int nwd(int a, int b) {
    return (b == 0 ? a : nwd(b, a%b));
}



int main() {

    return 0;
}
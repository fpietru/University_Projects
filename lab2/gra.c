// Autor: Franciszek Pietrusiak

int nwd(int a, int b) {
    return (b == 0 ? a : nwd(b, a%b));
}

// Zwraca 1 jesli pozycja (a, b) jest wygrywajaca, w przeciwnym przypadku zwraca 0
int pozycja(int a, int b) {
    int d = nwd(a, b);
    a /= d; b /= d;
    return ((a+b) % 2 == 1);
}

int graj(int a, int b) {
    if (a == 1 && b == 1)
        return 0;
    if (pozycja(a-1, b) == 0) // jesli (a-1, b) jest przegrywajaca to nalezy wyslac tam drugiego gracza
        return 1;
    else return 2;
}
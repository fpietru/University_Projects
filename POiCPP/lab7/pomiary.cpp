#include <bits/stdc++.h>

/*
Zaimplementować klasę Pomiary, która przechowuje wykonane pomiary (liczby typu double) i umożliwia
dokonanie na nich pewnych operacji statystycznych. Zakładamy, że Pomiary opisują wyniki uzyskane
w pojedynczym badaniu – w ramach badania wykonuje się określoną liczbę pomiarów.
Metody publiczne:
• void dodaj(double wartosc) – dodaje nowy pomiar o zadanej wartości
• int ilePomiarow() const – zwraca liczbę zarejestrowanych pomiarów
• double srednia() const – zwraca średnia wartość zarejestrowanych pomiarów
• double kwartyl(int numer) const – zwraca wartość podanego kwartyla
• double std dev() const – zwraca odchylenie standarowe pomiarów
• double max() const – zwraca wartość największą z zarejestrowanych pomiarów
• Pomiary& polacz proby(const Pomiary& p) – łączy dotychczasowy zestaw pomiarów z zestawem
innych pomiarów (zwiększa możliwą liczbę pomiarów w oryginalnej bazie)
*/

class Pomiary {
private:
    int ile_pomiarow;
    double *tablica_pomiarow;
    

};


int main () {

    return 0;
}
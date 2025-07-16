#include <bits/stdc++.h>
using namespace std;

vector<int> ciag_arytmetyczny(int a, int q, int b) {
    vector<int> res;
    for (int i=a; i<=b; i+=q)
        res.push_back(i);
    return res;
}

vector<int> suma(const vector<int> &A, const vector<int> &B) {
    set<int> st;
    st.insert(A.begin(), A.end());
    st.insert(B.begin(), B.end());
    vector<int> res(st.begin(), st.end());
    return res;
}

vector<int> roznica(const vector<int> &A, const vector<int> &B) {
    set<int> st(A.begin(), A.end());
    for (auto b : B)
        st.erase(b);
    vector<int> res(st.begin(), st.end());
    return res;
}

vector<int> iloczyn(const vector<int> &A, const vector<int> &B) {
    set<int> st;
    vector<int> res;
    st.insert(A.begin(), A.end());
    for (auto b : B)
        if (st.find(b) != st.end())
            res.push_back(b);
    return res;
}

void wypisz(const vector<int> &vec) {
    for (auto u : vec)
        cout << u << " ";
    cout << "\n";
}

int main () {
    vector<int> A, B, C, D, E;
    int a, q, b;
    cin >> a >> q >> b;
    A = ciag_arytmetyczny(a, q, b);
    cin >> a >> q >> b;
    B = ciag_arytmetyczny(a, q, b);

    C = suma(A, B);
    D = roznica(A, B);
    E = iloczyn(A, B);

    wypisz(A);
    wypisz(B);
    wypisz(C);
    wypisz(D);
    wypisz(E);

    return 0;
}
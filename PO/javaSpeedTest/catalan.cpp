#include <iostream>
#include <chrono>
using namespace std;
using ll = long long;

constexpr ll MOD = 998244353;

ll catalan(int n) {
    if (n == 0) return 1;
    ll cn = 0;
    for (int i=1; i<=n; i++)
        cn = (cn + (catalan(i-1) % MOD) * (catalan(n-i) % MOD)) % MOD;
    return cn;
}

int main (int argc, char* argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n = atoi(argv[1]);
    auto start = chrono::high_resolution_clock::now();

    ll cn = catalan(n);

    auto finish = chrono::high_resolution_clock::now();
    auto time = finish - start;
    cout << "res = " << cn << "; took " << time / chrono::milliseconds(1) << " ms \n";

    return 0;
}
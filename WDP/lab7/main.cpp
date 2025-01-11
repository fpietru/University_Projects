#include <bits/stdc++.h>
#include "prev.h"
using namespace std;

int check(vector<int> &seq, int i, int lo, int hi) {
    int ans = -1;
    for (int j=0; j<=i; j++)
        if (lo <= seq[j] && seq[j] <= hi)
            ans = j;
    return ans;
}



int main() {
    std::vector<int> seq = {6, 2, 9, 1, 4, 6};
    init(seq);

    for (


    assert(prevInRange(5, 7, 10) == 2);
    assert(prevInRange(5, 12, 14) == -1);
    assert(prevInRange(5, 6, 6) == 5);
    assert(prevInRange(0, 3, 7) == 0);
    pushBack(3);
    assert(prevInRange(5, 1, 3) == 3);
    assert(prevInRange(6, 1, 3) == 6);
    pushBack(6);
    done();
}

/*

0
0 10

0 2147483647
1 0 2147483643 2147483647
1 0 2147483646 2147483647
0 2147483644
0 2147483644
0 2147483646
0 2147483645
1 0 2147483645 2147483645
1 0 2147483643 2147483647
1 1 2147483643 2147483647


*/

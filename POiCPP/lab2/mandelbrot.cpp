#include <bits/stdc++.h>
#include <complex>
using namespace std;

const int MAX_ITERATIONS = 100;
const double BOUND = 100.0;

bool in_mandelbrot(complex<double> c) {
    complex<double> z = 0;
    for (int i=1; i<=MAX_ITERATIONS; i++) {
        if (abs(z) > BOUND)
            return false;
        z = z*z + c;
    }
    return true;
}

void draw_mandelbrot(int H, int W) {
    for (int y=0; y < H; y++) {
        for (int x=0; x < W; x++) {
            complex<double> point = ((x-W/2)/10.0, (y-H/2)/100.0);
            cout << point << "\n";
            bool flag = in_mandelbrot(point);
            cout << (flag ? "#" : ".");
        }
        cout << "\n";
    }

}

int main () {
    
    draw_mandelbrot(20, 30);

    return 0;
} 
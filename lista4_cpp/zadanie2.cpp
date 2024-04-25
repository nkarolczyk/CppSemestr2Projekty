#include <cmath>
#include<iostream>

double root(double (*f)(double), double a, double b, double tolerance = 1e-10) {
    if ((*f)(a) * (*f)(b) > 0) {
        return NAN; 
    }

    double x_mid = 0.0;
    while (b - a > tolerance) {
        x_mid = (a + b) / 2.0;
        if ((*f)(x_mid) == 0.0) {
            return x_mid;
        } else if ((*f)(a) * (*f)(x_mid) < 0) {
            b = x_mid;
        } else {
            a = x_mid;
        }
    }
    return x_mid;
}

double equation1(double x) {
    return cos(x) - x;
}

double equation2(double x) {
    return cos(x) - 0.5;
}

#include <iostream>
using namespace std;

int main() {
    double tolerance = 1e-6;

    // cos(x) = x -----> przedział [0, 2]
    double result1 = root(equation1, 0, 2, tolerance);
    cout << "Pierwiastek równania cos(x) = x w przedziale [0, 2]: " << result1 << endl;

    //cos(x) = 1/2 -----> przedział [0, 1.5]
    double result2 = root(equation2, 0, 1.5, tolerance);
    cout << "Pierwiastek równania cos(x) = 1/2 w przedziale [0, 1.5]: " << result2 << endl;

    return 0;
}

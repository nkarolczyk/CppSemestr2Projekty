#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

//funkcja do obliczenia pkt a)
long double calculate_a(int n) {
    long double sum = 0.0;
    int sign = 1;
    for (int j = 1; j <= n; ++j) {
        sum += sign / (2.0 * j - 1.0);
        sign *= -1;
    }
    return 4 * sum;
}

//funkcja do obliczenia pkt b)
long double calculate_b(int n) {
    long double product = 1.0;
    for (int j = 1; j <= n; ++j) {
        product *= (4.0 * j * j) / (4.0 * j * j - 1.0);
    }
    return 2 * product;
}

//funkcja do obliczenia pkt c)
long double calculate_c(int n) {
    long double sum = 0.0;
    for (int j = 1; j <= n; ++j) {
        sum += 1.0 / ((2.0 * j - 1.0) * (2.0 * j - 1.0));
    }
    return sqrtl(8 * sum);
}

int main() {
    const int n = 1000000;
    std::cout << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10);

    long double a = calculate_a(n);
    long double b = calculate_b(n);
    long double c = calculate_c(n);

    const long double pi = std::acos(-1.0L);

    std::cout << "Wynik a): " << a << std::endl;
    std::cout << "Wynik b): " << b << std::endl;
    std::cout << "Wynik c): " << c << std::endl;

    std::cout << "Porownanie z wartoscia liczby pi:" << std::endl;
    std::cout << "Pi:        " << pi << std::endl;
    std::cout << "roznica w a): " << std::fabs(a - pi) << std::endl;
    std::cout << "roznica w b): " << std::fabs(b - pi) << std::endl;
    std::cout << "roznica w c): " << std::fabs(c - pi) << std::endl;

    return 0;
}
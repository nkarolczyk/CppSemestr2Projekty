#include <iostream>
#include <cmath>
#include <iomanip>

//a)
double obliczPiMetodaA(int iteracje) {
    double t = 1.0 / std::sqrt(3);
    for (int i = 0; i < iteracje; ++i) {
        t = std::sqrt(std::pow(t, 2) / 2 + 1) - 1;
        t /= (1 + std::sqrt(std::pow(t, 2) + 1));
    }
    return 6 * std::pow(2, iteracje) * t;
}

//b)
double obliczPiMetodaB(int iteracje) {
    double t = 1.0 / std::sqrt(3);
    for (int i = 0; i < iteracje; ++i) {
        t = t / (std::sqrt(std::pow(t, 2) + 1) + 1);
    }
    return 6 * std::pow(2, iteracje) * t;
}

int main() {
    const double aktualnePi = M_PI;
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "i\tMetoda A Pi\tBlad A\t\tMetoda B Pi\tBlad B\n";

    for (int i = 0; i <= 30; ++i) {
        double piA = obliczPiMetodaA(i);
        double bladA = std::abs(piA - aktualnePi);

        double piB = obliczPiMetodaB(i);
        double bladB = std::abs(piB - aktualnePi);

        std::cout << i << "\t" << piA << "\t" << bladA << "\t" << piB << "\t" << bladB << "\n";
    }

    return 0;
}
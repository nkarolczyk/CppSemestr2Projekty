#include <iostream>
#include <iomanip>

//malejace
double down(int N) {
    double suma = 0.0;
    for (int i = 1; i <= N; ++i) {
        suma += 1.0 / i;
    }
    return suma;
}

//rosnace
double up(int N) {
    double suma = 0.0;
    for (int i = N; i > 0; --i) {
        suma += 1.0 / i;
    }
    return suma;
}

int main() {
    int wartosciN[] = {100, 100000, 100000000};

    for (int N : wartosciN) {
        double sumaDown = down(N);
        double sumaUp = up(N);

        std::cout << std::fixed << std::setprecision(15);
        std::cout << "N = " << N << std::endl;
        std::cout << "down(N) = " << sumaDown << std::endl;
        std::cout << "up(N) = " << sumaUp << std::endl;
        std::cout << "roznica = " << (sumaUp - sumaDown) << std::endl << std::endl;
    }

    //b) powtórzenie procesu z użyciem float
    std::cout << "Używając float:" << std::endl;

    for (int N : wartosciN) {
        float sumaDownFloat = 0.0f;
        float sumaUpFloat = 0.0f;

        //malejace
        for (int i = 1; i <= N; ++i) {
            sumaDownFloat += 1.0f / i;
        }

        //rosnace
        for (int i = N; i > 0; --i) {
            sumaUpFloat += 1.0f / i;
        }

        std::cout << std::fixed << std::setprecision(7);
        std::cout << "N = " << N << std::endl;
        std::cout << "down(N) = " << sumaDownFloat << std::endl;
        std::cout << "up(N) = " << sumaUpFloat << std::endl;
        std::cout << "roznica = " << (sumaUpFloat - sumaDownFloat) << std::endl << std::endl;
    }

    return 0;
}

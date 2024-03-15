#include <iostream>

// zwraca sumę size pierwszych elementów tablicy tab
int suma(const int tab[], unsigned size) {
    int sum = 0;
    for(unsigned i = 0; i < size; ++i) {
        sum += tab[i];
    }
    return sum;
}

// to samo co powyżej, ale wynik przekazywany jest poprzez result
void suma(const int tab[], unsigned size, int* result) {
    *result = 0;
    for(unsigned i = 0; i < size; ++i) {
        *result += tab[i];
    }
}

// wypisuje size pierwszych elementów tablicy w strumieniu out
void pisz(const int* tab, size_t size, std::ostream *out) {
    for(size_t i = 0; i < size; ++i) {
        *out << tab[i] << ' ';
    }
    *out << std::endl;
}

// zapisuje w tablicy kolejne liczby całkowite, od 0 do size - 1
void iota(int tab[], unsigned size) {
    for(unsigned i = 0; i < size; ++i) {
        tab[i] = i;
    }
}

// odwraca kolejność size pierwszych elementów w tablicy tab
void reverse(int* tab, size_t size) {
    for(size_t i = 0; i < size / 2; ++i) {
        std::swap(tab[i], tab[size - i - 1]);
    }
}

// oblicza iloczyn skalarny elementów 2 tablic o rozmiarze size
int dot_product(const int* tab1, const int* tab2, size_t size) {
    int product = 0;
    for(size_t i = 0; i < size; ++i) {
        product += tab1[i] * tab2[i];
    }
    return product;
}

int main() {
    const int tab[] = {1, 2, 3, 4, 5};

    int result_sum = suma(tab, 5);
    std::cout << "Suma (funkcja zwracajaca wartosc): " << result_sum << std::endl;

    int result_sum_pointer;
    suma(tab, 5, &result_sum_pointer);
    std::cout << "Suma (funkcja z wynikiem przez wskaznik): " << result_sum_pointer << std::endl;

    std::cout << "Elementy tablicy: ";
    pisz(tab, 5, &std::cout);

    int tab_iota[5];
    iota(tab_iota, 5);
    std::cout << "Tablica po iota: ";
    pisz(tab_iota, 5, &std::cout);

    int tab_reverse[] = {1, 2, 3, 4, 5};
    reverse(tab_reverse, 5);
    std::cout << "Tablica po odwroceniu: ";
    pisz(tab_reverse, 5, &std::cout);

    const int tab2[] = {5, 4, 3, 2, 1};
    int result_dot_product = dot_product(tab, tab2, 5);
    std::cout << "Iloczyn skalarny: " << result_dot_product << std::endl;

    return 0;
}
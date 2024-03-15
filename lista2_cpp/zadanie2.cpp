#include <cstdlib>
#include <iostream>

int compare(const void* a, const void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);

    if (int_a % 2 != 0 && int_b % 2 != 0) {
        return (int_b - int_a);
    }

    if (int_a % 2 == 0 && int_b % 2 == 0) {
        return (int_a - int_b);
    }

    if (int_a % 2 == 0) {
        return -1;
    }
    if (int_b % 2 == 0) {
        return 1;
    }

    return 0;
}

int main() {
    int array[] = {1, 4, 7, 2, 5, 9, 2, 8}; //przykladowe elementy tablicy
    int array_size = sizeof(array) / sizeof(array[0]);

    qsort(array, array_size, sizeof(int), compare);

    for (int i = 0; i < array_size; ++i) {
        std::cout << array[i] << ' ';
    }

    std::cout << std::endl;

    return 0;
}

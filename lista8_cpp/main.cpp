#include <iostream>
#include "timer.h"

int silnia(int n)
{
    if (n == 0)
        return 1;
    return n * silnia(n - 1);
}

int fibonacci(int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    Timer timer;

    for (int i = 30; i >= 0; i--)
        std::cout << i << "! = " << silnia(i) << std::endl;

    for (int i = 0; i <= 45; i++)
        std::cout << "fibonacci(" << i << ") = " << fibonacci(i) << "\n";

    std::cout << "Koniec programu" << std::endl;

    double elapsed_time = timer.get_elapsed_seconds();
    std::cout << "Execution time: " << elapsed_time << " seconds\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <stdexcept>

double operator*(const std::vector<double>& v, const std::vector<double>& w)
{
    if (v.size() != w.size())
    {
        throw std::logic_error("Błąd: Wektory muszą mieć tę samą długość!");
    }

    double result = 0.0;
    for (size_t i = 0; i < v.size(); ++i)
    {
        result += v[i] * w[i];
    }
    return result;
}

int main()
{
    std::vector<double> v1 {1, 2, 3};
    std::vector<double> v2 {5, 6, 7};

    double dot_product = v1 * v2;
    std::cout << "Iloczyn skalarny v1 i v2: " << dot_product << "\n";

    return EXIT_SUCCESS;
}

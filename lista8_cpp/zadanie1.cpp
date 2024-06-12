#include <iostream>
#include <vector>
#include <complex>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int main() {
    std::vector<int> vecInt = {1, 2, 3, 4, 5};
    std::cout << "Wektor int: " << vecInt << std::endl;

    std::vector<double> vecDouble = {1.1, 2.2, 3.3, 4.4, 5.5};
    std::cout << "Wektor double: " << vecDouble << std::endl;

    std::vector<std::complex<double>> vecComplex = {
        {1.1, 2.2}, 
        {3.3, 4.4}, 
        {5.5, 6.6}
    };
    std::cout << "Wektor complex<double>: " << vecComplex << std::endl;

    return 0;
}

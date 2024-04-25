#include <iostream>
#include <vector>

double operator*(const std::vector<double>& v, const std::vector<double>& w) {
    if (v.size() != w.size()) {
        std::cerr << "Błąd: Wektory muszą mieć tę samą długość!" << std::endl;
        return 0; 
    }
    
    double result = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        result += v[i] * w[i];
    }
    return result;
}

int main() {
    std::vector<double> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    std::vector<double> v2;
    v2.push_back(5);
    v2.push_back(6);
    v2.push_back(7);

    double dot_product = v1 * v2;
    std::cout << "Iloczyn skalarny v1 i v2: " << dot_product << std::endl;

    return 0;
}

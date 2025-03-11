#include <iostream>
#include "fraction.hpp"

int main()
{
    Fraction f1 { 3, 4 };
    Fraction f2 { 1, 2 };

    std::cout << "f1 = " << f1 << " f2 = " << f2 << std::endl;

    Fraction f3 { add(f1, f2) };

    std::cout << "add(f1, f2) = " << f3;

    std::cout << std::endl << "sub(f1, f2) = " << sub(f1, f2);

    std::cout << std::endl << "mul(f1, f2) = " << mul(f1, f2);

    // Conversio en float
    std::cout << std::endl << "mul(f1, f2) float = " << (f1 * f2).to_float();
    std::cout << std::endl << "mul(f1, f2) float = " << static_cast<float>(f1 * f2);

    std::cout << std::endl << "div(f1, f2) = " << div(f1, f2);

    std::cout << std::endl << "add(1/6, 2/6) = " << add({1, 6}, {2, 6});

    std::cout << std::endl << "f1 == f2 : " << (f1 == f2);

    std::cout << std::endl << "f1 == f1 : " << (f1 == f1);

    std::cout << std::endl << "f1 != f2 : " << (f1 != f2);

    std::cout << std::endl << "f1 != f1 : " << (f1 != f1);

    std::cout << std::endl << "f1 < f2 : " << (f1 < f2);

    std::cout << std::endl << "f1 > f2 : " << (f1 > f2);

    std::cout << std::endl << "f1 <= f2 : " << (f1 >= f2);

    std::cout << std::endl << "f1 >= f1 : " << (f1 >= f1);

    std::cout << std::endl << "f1 += f2 : " << (f1 += f2);

    std::cout << std::endl << "f1 -= f2 : " << (f1 -= f2);

    std::cout << std::endl << "f1 *= f2 : " << static_cast<float>(f1 *= f2);

    std::cout << std::endl << "f1 /= f2 : " << static_cast<float>(f1 /= f2);

    return 0;
}
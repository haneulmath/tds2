#include "fraction.hpp"
#include "utils.hpp"
#include <iostream>

// void Fraction::display() {
//     std::cout << numerator << "/" << denominator;
// }

// Fraction add(Fraction const& f1, Fraction const& f2) {
//     Fraction result {
//         f1.numerator * f2.denominator + f2.numerator * f1.denominator
//         f1.denominator * f2.denominator
//     };

//     return simplify(result);
// }


// Surcharge de l'opérateur 
std::ostream& operator<<(std::ostream& os, Fraction const& f) {
    os << f.numerator << "/" << f.denominator;
    return os;
}

// Fraction add(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.denominator + f2.numerator * f1.denominator,
//         f1.denominator * f2.denominator
//     });
// }

// Fraction sub(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.denominator - f2.numerator * f1.denominator,
//         f1.denominator * f2.denominator
//     });
// }

// Fraction mul(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.numerator,
//         f1.denominator * f2.denominator
//     });
// }

// Fraction div(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.denominator,
//         f1.denominator * f2.numerator
//     });
// }

// Opérateurs 
Fraction Fraction::operator+(Fraction const& other) const {
    Fraction result = *this;
    result += other;
    return result;
}

Fraction Fraction::operator-(Fraction const& other) const {
    Fraction result = *this;
    result -= other;
    return result;
}

Fraction Fraction::operator*(Fraction const& other) const {
    Fraction result = *this;
    result *= other;
    return result;
}

Fraction Fraction::operator/(Fraction const& other) const {
    Fraction result = *this;
    result /= other;
    return result;
}


// Opérateurs d'affectation
Fraction& Fraction::operator+=(Fraction const& other) {
    *this = add(*this, other);
    return *this;
}

Fraction& Fraction::operator-=(Fraction const& other) {
    *this = sub(*this, other);
    return *this;
}

Fraction& Fraction::operator*=(Fraction const& other) {
    *this = mul(*this, other);
    return *this;
}

Fraction& Fraction::operator/=(Fraction const& other) {
    *this = div(*this, other);
    return *this;
}


/// Opérateurs de comparaison
bool Fraction::operator==(Fraction const& other) const {
    return numerator == other.numerator && denominator == other.denominator;
}

bool Fraction::operator!=(Fraction const& other) const {
    return !(*this == other);
}

bool Fraction::operator<(Fraction const& other) const {
    return numerator * other.denominator < other.numerator * denominator;
}

bool Fraction::operator>(Fraction const& other) const {
    return numerator * other.denominator > other.numerator * denominator;
}

bool Fraction::operator<=(Fraction const& other) const {
    return *this < other || *this == other;
}

bool Fraction::operator>=(Fraction const& other) const {
    return *this > other || *this == other;
}


// Conversion de la fraction en float
float Fraction::to_float() const {
    return static_cast<float>(numerator) / static_cast<float>(denominator);
}

Fraction::operator float() const {
    return to_float();
}
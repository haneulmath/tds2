#pragma once
#include <iostream>

struct Fraction {
    unsigned int numerator;
    unsigned int denominator;

    // void display();

    Fraction operator+(Fraction const& other) const;
    Fraction operator-(Fraction const& other) const;
    Fraction operator*(Fraction const& other) const;
    Fraction operator/(Fraction const& other) const;

    // Ajout de l'opérateur de comparaison d'égalité
    bool operator==(Fraction const& other) const;

    // Ajout de l'opérateur de comparaison d'inégalité
    bool operator!=(Fraction const& other) const;

    // Ajout de l'opérateur de comparaison d'infériorité
    bool operator<(Fraction const& other) const;

    // Ajout de l'opérateur de comparaison de supériorité
    bool operator>(Fraction const& other) const;

    // Ajout de l'opérateur de comparaison d'infériorité ou d'égalité
    bool operator<=(Fraction const& other) const;

    // Ajout de l'opérateur de comparaison de supériorité ou d'égalité
    bool operator>=(Fraction const& other) const;

    // Ajout des opérateurs d'affectation
    Fraction& operator+=(Fraction const& other);
    Fraction& operator-=(Fraction const& other);
    Fraction& operator*=(Fraction const& other);
    Fraction& operator/=(Fraction const& other);

    float to_float() const;
    operator float() const;

};

std::ostream& operator<<(std::ostream& os, Fraction const& f);

Fraction add(Fraction const& f1, Fraction const& f2);
Fraction sub(Fraction const& f1, Fraction const& f2);
Fraction mul(Fraction const& f1, Fraction const& f2);
Fraction div(Fraction const& f1, Fraction const& f2);
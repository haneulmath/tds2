#include <string>
#include <algorithm>
#include <iostream>

bool Palindrome(const std::string& str) {
    return std::equal(std::begin(str), std::end(str), std::rbegin(str));
}

int main() {
    std::string input;
    std::cout << "Entrez une chaîne de caractères : ";
    std::cin >> input;

    if (Palindrome(input)) {
        std::cout << "La chaîne \"" << input << "\" est un palindrome." << std::endl;
    } else {
        std::cout << "La chaîne \"" << input << "\" n'est pas un palindrome." << std::endl;
    }

    return 0;
}
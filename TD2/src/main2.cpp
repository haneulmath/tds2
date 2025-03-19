#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.hpp"

// Fonction pour séparer une chaîne de caractères en mots
std::vector<std::string> split(const std::string& expression) {
    std::istringstream iss(expression);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

int main() {
    std::string expression;
    std::cout << "Entrez une expression en notation polonaise inversée (main2): ";
    std::getline(std::cin, expression);

    try {
        std::vector<std::string> words = split(expression);
        std::vector<Token> tokens = tokenize(words);
        float result = npi_evaluate(tokens);
        std::cout << "Le résultat est: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
    }

    return 0;
}
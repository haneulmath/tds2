#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.hpp"

// Fonction pour séparer une chaîne de caractères en mots
std::vector<std::string> tokenize(const std::string& expression) {
    std::istringstream iss(expression);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    std::string expression;
    std::cout << "Entrez une expression en notation polonaise inversée: ";
    std::getline(std::cin, expression);

    try {
        std::vector<std::string> tokens = tokenize(expression);
        float result = npi_evaluate(tokens);
        std::cout << "Le résultat est: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
    }

    return 0;
}
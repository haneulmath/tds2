#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.hpp"

// Fonction pour vérifier si une chaîne de caractères représente un nombre flottant
bool is_floating(const std::string& s);

// Fonction pour évaluer une expression en notation polonaise inversée
float npi_evaluate(const std::vector<std::string>& tokens);

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

// Fonction pour évaluer une expression en notation polonaise inversée
float npi_evaluate(const std::vector<std::string>& tokens) {
    std::stack<float> stack;

    for (const auto& token : tokens) {
        if (is_floating(token)) {
            stack.push(std::stof(token));
        } else {
            if (stack.size() < 2) {
                throw std::invalid_argument("Expression invalide");
            }
            float b = stack.top(); stack.pop();
            float a = stack.top(); stack.pop();

            if (token == "+") {
                stack.push(a + b);
            } else if (token == "-") {
                stack.push(a - b);
            } else if (token == "*") {
                stack.push(a * b);
            } else if (token == "/") {
                if (b == 0) {
                    throw std::invalid_argument("Division par zéro");
                }
                stack.push(a / b);
            } else {
                throw std::invalid_argument("Opérateur inconnu: " + token);
            }
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Expression invalide");
    }

    return stack.top();
}

int main() {
    std::string expression;
    std::cout << "Entrez une expression en notation polonaise inversée (main1): ";
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
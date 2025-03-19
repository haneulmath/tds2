#include "utils.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <regex>

// Fonction pour vérifier si une chaîne de caractères représente un nombre flottant
bool is_floating(const std::string& s) {
    std::regex float_regex("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
    return std::regex_match(s, float_regex);
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

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


// Fonction pour créer un token à partir d'un opérande
Token make_token(float value) {
    Token token;
    token.type = Token::OPERAND;
    token.value.operand = value;
    return token;
}

// Fonction pour créer un token à partir d'un opérateur
Token make_token(Operator op) {
    Token token;
    token.type = Token::OPERATOR;
    token.value.op = op;
    return token;
}

// Fonction pour transformer une liste de mots en une liste de tokens
std::vector<Token> tokenize(const std::vector<std::string>& words) {
    std::vector<Token> tokens;
    for (const auto& word : words) {
        if (is_floating(word)) {
            tokens.push_back(make_token(std::stof(word)));
        } else {
            Operator op;
            if (word == "+") op = Operator::ADD;
            else if (word == "-") op = Operator::SUBTRACT;
            else if (word == "*") op = Operator::MULTIPLY;
            else if (word == "/") op = Operator::DIVIDE;
            else throw std::invalid_argument("Opérateur inconnu: " + word);
            tokens.push_back(make_token(op));
        }
    }
    return tokens;
}

// Fonction pour évaluer une expression en notation polonaise inversée
float npi_evaluate2(const std::vector<Token>& tokens) {
    std::stack<float> stack;

    for (const auto& token : tokens) {
        if (token.type == Token::OPERAND) {
            stack.push(token.value.operand);
        } else {
            if (stack.size() < 2) {
                throw std::invalid_argument("Expression invalide");
            }
            float b = stack.top(); stack.pop();
            float a = stack.top(); stack.pop();

            switch (token.value.op) {
                case Operator::ADD:
                    stack.push(a + b);
                    break;
                case Operator::SUBTRACT:
                    stack.push(a - b);
                    break;
                case Operator::MULTIPLY:
                    stack.push(a * b);
                    break;
                case Operator::DIVIDE:
                    if (b == 0) {
                        throw std::invalid_argument("Division par zéro");
                    }
                    stack.push(a / b);
                    break;
                default:
                    throw std::invalid_argument("Opérateur inconnu");
            }
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Expression invalide");
    }

    return stack.top();
}

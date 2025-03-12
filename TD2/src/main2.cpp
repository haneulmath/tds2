#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.hpp"

// Énumération pour les opérateurs
enum class Operator { ADD, SUBTRACT, MULTIPLY, DIVIDE };

// Vérifier si une chaîne de caractères représente un nombre flottant
struct Token {
    enum Type { OPERAND, OPERATOR } type;
    union {
        float operand;
        Operator op;
    } value;
};

// Fonctions pour construire la structure Token à partir d'un nombre flottant ou de la valeur de l’énumération Operator
Token make_token(float value);
Token make_token(Operator op);

// Fonvertir une liste de mots en une liste de tokens
std::vector<Token> tokenize(const std::vector<std::string>& words);

// Évaluer une expression en notation polonaise inversée
float npi_evaluate(const std::vector<Token>& tokens);

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
float npi_evaluate(const std::vector<Token>& tokens) {
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
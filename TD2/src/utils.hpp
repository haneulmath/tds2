#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

// Fonction pour vérifier si une chaîne de caractères représente un nombre flottant
bool is_floating(const std::string& s);

// Fonction pour évaluer une expression en notation polonaise inversée
float npi_evaluate(const std::vector<std::string>& tokens);

// Fonction pour évaluer une expression en notation polonaise inversée avec des tokens
float npi_evaluate2(const std::vector<Token>& tokens);

#endif 

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


#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

// Fonction pour vérifier si une chaîne de caractères représente un nombre flottant
bool is_floating(const std::string& s);

// Fonction pour évaluer une expression en notation polonaise inversée
float npi_evaluate(const std::vector<std::string>& tokens);

#endif 

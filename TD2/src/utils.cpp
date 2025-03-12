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


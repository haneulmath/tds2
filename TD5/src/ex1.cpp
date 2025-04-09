#include <iostream>
#include <string>
#include <cstddef> // pour size_t

// Fonction de hachage qui prend une chaîne et retourne un entier entre 0 et max
size_t hash_string(const std::string& str, size_t max) {
    size_t hash = 0;
    
    // Somme des valeurs ASCII de chaque caractère
    for (char c : str) {
        hash += static_cast<size_t>(c);
    }
    
    // Retourne la valeur entre 0 et max
    return hash % (max + 1);
}

// Fonction de hachage prenant en compte l'ordre des caractères
size_t hash_string_ordered(const std::string& str, size_t max) {
    size_t hash = 0;
    
    // Utilisation d'une pondération basée sur la position pour que l'ordre compte
    for (size_t i = 0; i < str.length(); ++i) {
        // Multiplication par une puissance de 31 (nombre premier communément utilisé en hachage)
        // pour que chaque position contribue différemment au résultat final
        hash = hash * 31 + static_cast<size_t>(str[i]);
    }
    
    // Retourne la valeur entre 0 et max
    return hash % (max + 1);
}

// Fonction de hachage utilisant la technique du polynomial rolling hash
size_t polynomial_rolling_hash(std::string const& s, size_t p, size_t m) {
    size_t hash_value = 0;
    size_t p_pow = 1; // p^0 = 1
    
    // Calcul du hash polynomial: s[0]*p^(n-1) + s[1]*p^(n-2) + ... + s[n-1]*p^0
    for (char c : s) {
        hash_value = (hash_value + static_cast<size_t>(c) * p_pow) % m;
        p_pow = (p_pow * p) % m; // Calcul de la prochaine puissance de p, avec modulo pour éviter l'overflow
    }
    
    return hash_value;
}

int main() {
    std::string input;
    size_t max_value;
    
    std::cout << "Entrez une chaîne de caractères : ";
    std::getline(std::cin, input);
    
    std::cout << "Entrez la valeur maximum pour le hash : ";
    std::cin >> max_value;
    
    size_t hash_result = hash_string(input, max_value);
    
    // Test de la nouvelle fonction de hachage
    size_t ordered_hash_result = hash_string_ordered(input, max_value);
    
    std::cout << "Hash classique de \"" << input << "\" : " << hash_result << std::endl;
    std::cout << "Hash ordonné de \"" << input << "\" : " << ordered_hash_result << std::endl;
    
    // Démonstration avec anagramme
    std::string str1 = "abc";
    std::string str2 = "cba";
    
    std::cout << "\nDémonstration avec anagrammes:\n";
    std::cout << "Hash classique de \"" << str1 << "\" : " << hash_string(str1, max_value) << std::endl;
    std::cout << "Hash classique de \"" << str2 << "\" : " << hash_string(str2, max_value) << std::endl;
    std::cout << "Hash ordonné de \"" << str1 << "\" : " << hash_string_ordered(str1, max_value) << std::endl;
    std::cout << "Hash ordonné de \"" << str2 << "\" : " << hash_string_ordered(str2, max_value) << std::endl;
    
    // Test de la fonction polynomial rolling hash
    size_t p = 31; // Base 
    size_t m = max_value + 1; // Module
    
    std::cout << "\nTest du polynomial rolling hash:\n";
    std::cout << "Polynomial rolling hash de \"" << str1 << "\" : " 
              << polynomial_rolling_hash(str1, p, m) << std::endl;
    std::cout << "Polynomial rolling hash de \"" << str2 << "\" : " 
              << polynomial_rolling_hash(str2, p, m) << std::endl;
    
    return 0;
}

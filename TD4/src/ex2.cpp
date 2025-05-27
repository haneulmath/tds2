#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

// Fonction pour compter les lettres du premier mot
int compteLettresPremierMot(const std::string& phrase) {
    auto it = std::find(phrase.begin(), phrase.end(), ' ');
    return std::distance(phrase.begin(), it);
}

// Fonction pour découper une phrase en mots
std::vector<std::string> split_string(std::string const& str) {
    std::vector<std::string> mots;
    std::string mot;
    
    for (char c : str) {
        if (c == ' ') {
            if (!mot.empty()) {
                mots.push_back(mot);
                mot.clear();
            }
        } else {
            mot += c;
        }
    }
    
    // Ajouter le dernier mot s'il existe
    if (!mot.empty()) {
        mots.push_back(mot);
    }
    
    return mots;
}

// Exemple d'utilisation
int main() {
    std::string phrase;
    
    std::cout << "Entrez une phrase : ";
    std::getline(std::cin, phrase);
    
    std::cout << "Nombre de lettres du premier mot : " << compteLettresPremierMot(phrase) << std::endl;
    
    auto mots = split_string(phrase);
    std::cout << "Mots de la phrase :" << std::endl;
    for (const auto& mot : mots) {
        std::cout << mot << std::endl;
    }
    
    return 0;
}

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include <numeric>

int main() {
    // Générateur nb aléatoires
    std::srand(std::time(0));

    // Création d'un vecteur de 10 éléments
    std::vector<int> vector01(10);
    for (auto& val : vector01) {
        val = std::rand() % 101; 
    }

    // Affichage avant tri
    std::cout << "Vecteur avant tri : ";
    for (auto it = vector01.begin(); it != vector01.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Tri du vecteur
    std::sort(vector01.begin(), vector01.end());

    // Affichage après tri
    std::cout << "Vecteur après tri : ";
    for (auto it = vector01.begin(); it != vector01.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Calcul de la somme des éléments
    int sum = std::accumulate(vector01.begin(), vector01.end(), 0);
    std::cout << "La somme des éléments du vecteur est : " << sum << std::endl;

    // Saisie 
    int userInput;
    std::cout << "Entrez un nombre à rechercher : ";
    std::cin >> userInput;

    // Recherche d'un élément
    auto it = std::find(vector01.begin(), vector01.end(), userInput);
    if (it != vector01.end()) {
        std::cout << "Element trouvé à la position " << std::distance(vector01.begin(), it)+1 << std::endl;
    } else {
        std::cout << "Element non trouvé" << std::endl;
    }

    // Nb d'occurrences
    int count = std::count(vector01.begin(), vector01.end(), userInput);
    std::cout << "Le nombre " << userInput << " apparaît " << count << " fois " <<std::endl;


    return 0;
}



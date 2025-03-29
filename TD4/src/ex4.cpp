#include <vector>
#include <numeric>
#include <iostream>

// Somme des carrés
int sommeDesCarres(const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0, [](int acc, int val) {
        return acc + val * val;
    });
}

// Produit des éléments pairs
int produitDesPairs(const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 1, [](int acc, int val) {
        return acc * (val % 2 == 0 ? val : 1);
    });
}

int main() {
    std::vector<int> vec;
    int n, value;

    std::cout << "Entrez le nombre d'éléments : ";
    std::cin >> n;

    std::cout << "Entrez les éléments : ";
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        vec.push_back(value);
    }

    std::cout << "Somme des carrés : " << sommeDesCarres(vec) << std::endl;
    std::cout << "Produit des pairs : " << produitDesPairs(vec) << std::endl;

    return 0;
}

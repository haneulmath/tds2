#include <functional>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

enum class Insect {
    ClassicBee,
    Ladybug,
    Butterfly,
    Dragonfly,
    Ant,
    Grasshopper,
    Beetle,
    Wasp,
    Caterpillar,
    Spider,
    GuimielBee
};

std::vector<Insect> const insect_values {
    Insect::ClassicBee,
    Insect::Ladybug,
    Insect::Butterfly,
    Insect::Dragonfly,
    Insect::Ant,
    Insect::Grasshopper,
    Insect::Beetle,
    Insect::Wasp,
    Insect::Caterpillar,
    Insect::Spider,
    Insect::GuimielBee
};

std::unordered_map<Insect, std::string> const insect_to_string = {
    {Insect::ClassicBee, "ClassicBee"},
    {Insect::Ladybug, "Ladybug"},
    {Insect::Butterfly, "Butterfly"},
    {Insect::Dragonfly, "Dragonfly"},
    {Insect::Ant, "Ant"},
    {Insect::Grasshopper, "Grasshopper"},
    {Insect::Beetle, "Beetle"},
    {Insect::Wasp, "Wasp"},
    {Insect::Caterpillar, "Caterpillar"},
    {Insect::Spider, "Spider"},
    {Insect::GuimielBee, "GuimielBee"}
};

std::vector<int> const expected_insect_counts {
    75, // ClassicBee
    50, // Ladybug
    100, // Butterfly
    20, // Dragonfly
    400, // Ant
    150, // Grasshopper
    60, // Beetle
    10, // Wasp
    40, // Caterpillar
    90, // Spider 
    5, // GuimielBee
};

// Fonction pour convertir un vecteur de comptages en vecteur de probabilités
std::vector<float> probabilities_from_count(std::vector<int> const& counts) {
    std::vector<float> probabilities;
    probabilities.reserve(counts.size());
    
    // Calcul de la somme totale des comptages
    int sum = 0;
    for (int count : counts) {
        sum += count;
    }
    
    // Conversion des comptages en probabilités
    if (sum > 0) { 
        for (int count : counts) {
            probabilities.push_back(static_cast<float>(count) / static_cast<float>(sum));
        }
    } else {
        float equal_probability = 1.0f / static_cast<float>(counts.size());
        for (size_t i = 0; i < counts.size(); ++i) {
            probabilities.push_back(equal_probability);
        }
    }
    
    return probabilities;
}

std::vector<std::pair<Insect, int>> get_insect_observations(
    size_t const number_of_observations,
    std::vector<float> const& insect_probabilities,
    unsigned int const seed = std::random_device{}()
) {
    // Vérification que la somme des probabilités est égale à 1
    std::default_random_engine random_engine{seed};

    auto rand_insect_index { std::bind(std::discrete_distribution<size_t>{insect_probabilities.begin(), insect_probabilities.end()}, random_engine) };
    
    std::vector<std::pair<Insect, int>> observations {};
    observations.reserve(number_of_observations);

    for(size_t i {0}; i < number_of_observations; ++i) {
        size_t const random_insect_index { rand_insect_index() };
        Insect const random_insect { insect_values[random_insect_index] };
        
        // Vérification si l'insecte a déjà été observé
        if(!observations.empty() && observations.back().first == random_insect) {
            observations.back().second++;
            i -= 1;
        } else {
            observations.push_back({random_insect, 1});
        }
    }

    return observations;
}

#include <iostream>
#include <iomanip>

int main() {
    // Génération des probabilités à partir des comptages attendus
    std::vector<float> probabilities = probabilities_from_count(expected_insect_counts);
    
    // Génération de 10000 observations d'insectes
    const size_t nb_observations = 10000;
    auto observations = get_insect_observations(nb_observations, probabilities);
    
    // Création d'une table de hachage pour compter les apparitions de chaque insecte
    std::unordered_map<Insect, int> insect_counts;
    
    // Parcours des observations et comptage
    for (const auto& observation : observations) {
        insect_counts[observation.first] += observation.second;
    }
    
    // Affichage des résultats
    std::cout << "Résultats des observations de " << nb_observations << " insectes:" << std::endl;
    std::cout << std::left << std::setw(15) << "Insecte" << std::right << std::setw(10) << "Nombre" << std::endl;
    std::cout << std::string(25, '-') << std::endl;
    
    for (const auto& insect : insect_values) {
        std::cout << std::left << std::setw(15) << insect_to_string.at(insect)
                  << std::right << std::setw(10) << insect_counts[insect] << std::endl;
    }
    
    // Conversion des comptages observés en vecteur pour calculer les probabilités réelles
    std::vector<int> observed_counts;
    observed_counts.reserve(insect_values.size());
    
    for (const auto& insect : insect_values) {
        observed_counts.push_back(insect_counts[insect]);
    }
    
    // Calcul des probabilités basées sur les observations réelles
    std::vector<float> observed_probabilities = probabilities_from_count(observed_counts);
    
    // Seuil de conformité des probabilités (1%)
    const float threshold = 0.01f;
    bool is_conforming = true;
    
    // Affichage des probabilités observées et comparaison avec les probabilités initiales
    std::cout << "\nComparaison des probabilités:" << std::endl;
    std::cout << std::left << std::setw(15) << "Insecte" 
              << std::right << std::setw(15) << "Prob. Initiale"
              << std::right << std::setw(15) << "Prob. Observée"
              << std::right << std::setw(15) << "Différence" 
              << std::right << std::setw(15) << "Conforme?" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    
    for (size_t i = 0; i < insect_values.size(); ++i) {
        float diff = std::abs(probabilities[i] - observed_probabilities[i]);
        bool is_insect_conforming = diff <= threshold;
        
        // Si au moins un insecte n'est pas conforme, les observations ne sont pas conformes
        if (!is_insect_conforming) {
            is_conforming = false;
        }
        
        std::cout << std::left << std::setw(15) << insect_to_string.at(insect_values[i])
                  << std::right << std::setw(15) << std::fixed << std::setprecision(6) << probabilities[i]
                  << std::right << std::setw(15) << std::fixed << std::setprecision(6) << observed_probabilities[i]
                  << std::right << std::setw(15) << std::fixed << std::setprecision(6) << diff
                  << std::right << std::setw(15) << (is_insect_conforming ? "Oui" : "Non") << std::endl;
    }
    
    // Affichage du résultat final 
    std::cout << "\nRésultat global: ";
    if (is_conforming) {
        std::cout << "Les observations sont conformes aux probabilités initiales (seuil de " << threshold << ")." << std::endl;
    } else {
        std::cout << "Les observations ne sont pas conformes aux probabilités initiales (seuil de " << threshold << ")." << std::endl;
    }
    
    return 0;
}


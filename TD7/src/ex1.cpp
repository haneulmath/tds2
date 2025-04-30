#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <queue>
#include <stack>
#include <set>

namespace Graph {
    struct WeightedGraphEdge {
        int to {};
        float weight {1.0f};

        // default ici permet de définit les opérateurs de comparaison membres à membres automatiquement
        // Cela ne fonction qu'en C++20, si vous n'avez pas accès à cette version je vous donne les implémentations des opérateurs plus bas
        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct WeightedGraph {
        // L'utilisation d'un tableau associatif permet d'avoir une complexité en O(1) pour l'ajout et la recherche d'un sommet.
        // Cela permet de stocker les sommets dans un ordre quelconque (et pas avoir la contrainte d'avoir des identifiants (entiers) de sommets consécutifs lors de l'ajout de sommets).
        // Cela permet également de pouvoir utiliser des identifiants de sommets de n'importe quel type (string, char, int, ...) et pas seulement des entiers.
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list {};

        void add_vertex(int const id);

        void add_directed_edge(int const from, int const to, float const weight = 1.0f);
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f);
        
        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        void print_DFS(int const start) const;
        void print_BFS(int const start) const;
    };

    // Implémentation de add_vertex
    void WeightedGraph::add_vertex(int const id) {
        // Vérifie si le sommet existe déjà
        if (adjacency_list.find(id) == adjacency_list.end()) {
            // Si le sommet n'existe pas, on l'ajoute avec une liste d'arêtes vide
            adjacency_list[id] = std::vector<WeightedGraphEdge>{};
        }
    }

    // Implémentation de add_directed_edge
    void WeightedGraph::add_directed_edge(int const from, int const to, float const weight) {
        // Ajoute les sommets s'ils n'existent pas
        add_vertex(from);
        add_vertex(to);
        
        // Ajoute l'arête dirigée
        adjacency_list[from].push_back({to, weight});
    }

    // Implémentation de add_undirected_edge
    void WeightedGraph::add_undirected_edge(int const from, int const to, float const weight) {
        // Ajoute deux arêtes dirigées dans les deux sens
        add_directed_edge(from, to, weight);
        add_directed_edge(to, from, weight);
    }

    // Implémentation de build_from_adjacency_matrix
    WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix) {
        WeightedGraph graph;
        
        // Parcours de la matrice d'adjacence
        for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
            // Ajoute le sommet i
            graph.add_vertex(static_cast<int>(i));
            
            // Parcours des colonnes pour trouver les arêtes
            for (size_t j = 0; j < adjacency_matrix[i].size(); ++j) {
                // Si le poids est différent de 0, il y a une arête
                if (adjacency_matrix[i][j] != 0.0f) {
                    graph.add_directed_edge(static_cast<int>(i), static_cast<int>(j), adjacency_matrix[i][j]);
                }
            }
        }
        
        return graph;
    }

} // namespace

// Fonction principale pour tester l'implémentation
int main() {
    // Création d'une matrice d'adjacence
    // Exemple de graphe avec 4 sommets
    std::vector<std::vector<float>> adjacency_matrix = {
        {0.0f, 2.0f, 1.0f, 0.0f},
        {2.0f, 0.0f, 3.0f, 0.0f},
        {1.0f, 3.0f, 0.0f, 1.5f},
        {0.0f, 0.0f, 1.5f, 0.0f}
    };
    
    // Création du premier graphe à partir de la matrice d'adjacence
    Graph::WeightedGraph graph1 = Graph::build_from_adjacency_matrix(adjacency_matrix);
    
    // Création du deuxième graphe en utilisant les méthodes add_vertex et add_undirected_edge
    Graph::WeightedGraph graph2;
    
    // Ajout des sommets
    for (int i = 0; i < 4; ++i) {
        graph2.add_vertex(i);
    }
    
    // Ajout des arêtes non dirigées
    graph2.add_undirected_edge(0, 1, 2.0f);
    graph2.add_undirected_edge(0, 2, 1.0f);
    graph2.add_undirected_edge(1, 2, 3.0f);
    graph2.add_undirected_edge(2, 3, 1.5f);
    
    // Comparaison des deux graphes
    if (graph1 == graph2) {
        std::cout << "Les deux graphes sont identiques!" << std::endl;
    } else {
        std::cout << "Les deux graphes sont différents!" << std::endl;
    }
    
    return 0;
}
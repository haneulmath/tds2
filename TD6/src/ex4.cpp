#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

namespace BinaryTreeImpl {

// Structure de noeud pour l'implémentation interne de l'arbre binaire
struct Node {
    int value;
    std::unique_ptr<Node> left{nullptr};
    std::unique_ptr<Node> right{nullptr};
    
    // Vérifie si le noeud est une feuille
    bool is_leaf() const {
        return !left && !right;
    }
    
    // Insère une valeur dans l'arbre
    void insert(int value) {
        if (value < this->value) {
            if (!left) {
                left = std::make_unique<Node>(Node{value});
            } else {
                left->insert(value);
            }
        } else {
            if (!right) {
                right = std::make_unique<Node>(Node{value});
            } else {
                right->insert(value);
            }
        }
    }
    
    // Affichage des valeurs dans l'ordre infixe
    void display_infix() const {
        if (left) {
            left->display_infix();
        }
        
        std::cout << value << " ";
        
        if (right) {
            right->display_infix();
        }
    }
    
    // Calcule la hauteur de l'arbre
    size_t height() const {
        if (is_leaf()) {
            return 1;
        }
        
        size_t left_height = 0;
        size_t right_height = 0;
        
        if (left) {
            left_height = left->height();
        }
        
        if (right) {
            right_height = right->height();
        }
        
        return 1 + std::max(left_height, right_height);
    }
    
    // Valeur minimale
    int min() const {
        if (!left) {
            return value;
        }
        return left->min();
    }
    
    // Valeur maximale
    int max() const {
        if (!right) {
            return value;
        }
        return right->max();
    }
    
    // Parcours préfixe
    std::vector<int> prefix() const {
        std::vector<int> result;
        
        // Ajouter d'abord le noeud courant (racine)
        result.push_back(value);
        
        // Ajouter les noeuds du sous-arbre gauche en préfixe
        if (left) {
            std::vector<int> left_values = left->prefix();
            result.insert(result.end(), left_values.begin(), left_values.end());
        }
        
        // Ajouter les noeuds du sous-arbre droit en préfixe
        if (right) {
            std::vector<int> right_values = right->prefix();
            result.insert(result.end(), right_values.begin(), right_values.end());
        }
        
        return result;
    }
    
    // Parcours postfixe 
    std::vector<int> postfix() const {
        std::vector<int> result;
        
        // Ajouter les noeuds du sous-arbre gauche en postfixe
        if (left) {
            std::vector<int> left_values = left->postfix();
            result.insert(result.end(), left_values.begin(), left_values.end());
        }
        
        // Ajouter les noeuds du sous-arbre droit en postfixe
        if (right) {
            std::vector<int> right_values = right->postfix();
            result.insert(result.end(), right_values.begin(), right_values.end());
        }
        
        // Ajouter le noeud courant en dernier (racine)
        result.push_back(value);
        
        return result;
    }
};

// Retourne une référence vers le pointeur du noeud le plus à gauche
std::unique_ptr<Node>& most_left(std::unique_ptr<Node>& node) {
    if (!node) {
        return node;
    }
    
    if (!node->left) {
        return node;
    }
    
    return most_left(node->left);
}

// Supprime un noeud avec une valeur spécifique
bool remove(std::unique_ptr<Node>& node, int value) {
    if (!node) {
        return false;
    }
    
    if (value < node->value) {
        return remove(node->left, value);
    }
    
    if (value > node->value) {
        return remove(node->right, value);
    }
    
    // Cas 1: Noeud feuille (sans enfants)
    if (node->is_leaf()) {
        node.reset();
        return true;
    }
    
    // Cas 2: Noeud avec un seul enfant
    if (!node->left) {
        node = std::move(node->right);
        return true;
    }
    
    if (!node->right) {
        node = std::move(node->left);
        return true;
    }
    
    // Cas 3: Noeud avec deux enfants
    std::unique_ptr<Node>& successor = most_left(node->right);
    
    node->value = successor->value;
    
    if (!successor->right) {
        successor.reset();
    } else {
        successor = std::move(successor->right);
    }
    
    return true;
}

// Vérifie si un arbre contient une valeur
bool contains(const std::unique_ptr<Node>& node, int value) {
    if (!node) {
        return false;
    }
    
    if (node->value == value) {
        return true;
    }
    
    if (value < node->value) {
        return contains(node->left, value);
    } else {
        return contains(node->right, value);
    }
}

// Somme des valeurs des noeuds
int sum_values(const std::unique_ptr<Node>& node) {
    if (!node) {
        return 0;
    }
    
    return node->value + sum_values(node->left) + sum_values(node->right);
}

} // fin du namespace BinaryTreeImpl

// La classe BinaryTree qui expose l'interface publique
class BinaryTree {
private:
    // Implémentation interne cachée
    std::unique_ptr<BinaryTreeImpl::Node> root{nullptr};
    
public:
    // Constructeur par défaut
    BinaryTree() = default;
    
    // Constructeur avec valeur initiale
    explicit BinaryTree(int value) {
        root = std::make_unique<BinaryTreeImpl::Node>(BinaryTreeImpl::Node{value});
    }
    
    // Insérer une valeur dans l'arbre
    void insert(int value) {
        if (!root) {
            root = std::make_unique<BinaryTreeImpl::Node>(BinaryTreeImpl::Node{value});
        } else {
            root->insert(value);
        }
    }
    
    // Supprimer une valeur de l'arbre
    bool remove(int value) {
        return BinaryTreeImpl::remove(root, value);
    }
    
    // Vider l'arbre
    void clear() {
        root.reset();
    }
    
    // Vérifier si l'arbre contient une valeur
    bool contains(int value) const {
        return BinaryTreeImpl::contains(root, value);
    }
    
    // Calculer la hauteur de l'arbre
    size_t height() const {
        if (!root) {
            return 0;
        }
        return root->height();
    }
    
    // Afficher l'arbre en ordre infixe
    void display_infix() const {
        if (root) {
            root->display_infix();
        }
        std::cout << std::endl;
    }
    
    // Obtenir la valeur minimale de l'arbre
    int min() const {
        if (!root) {
            throw std::runtime_error("Arbre vide");
        }
        return root->min();
    }
    
    // Obtenir la valeur maximale de l'arbre
    int max() const {
        if (!root) {
            throw std::runtime_error("Arbre vide");
        }
        return root->max();
    }
    
    // Obtenir les valeurs en parcours préfixe
    std::vector<int> prefix() const {
        if (!root) {
            return {};
        }
        return root->prefix();
    }
    
    // Obtenir les valeurs en parcours postfixe (BONUS)
    std::vector<int> postfix() const {
        if (!root) {
            return {};
        }
        return root->postfix();
    }
    
    // Calculer la somme des valeurs de l'arbre
    int sum() const {
        return BinaryTreeImpl::sum_values(root);
    }
};

int main() {
    BinaryTree tree;
    
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(1);
    tree.insert(9);
    tree.insert(0);
    
    std::cout << "Affichage infixe: ";
    tree.display_infix();
    
    std::cout << "Valeur minimale: " << tree.min() << std::endl;
    std::cout << "Valeur maximale: " << tree.max() << std::endl;

    std::cout << "Somme des valeurs: " << tree.sum() << std::endl;

    std::cout << "Hauteur de l'arbre: " << tree.height() << std::endl;
    
    std::vector<int> prefix_values = tree.prefix();
    std::cout << "Parcours préfixe: ";
    for (int val : prefix_values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::vector<int> postfix_values = tree.postfix();
    std::cout << "Parcours postfixe: ";
    for (int val : postfix_values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "L'arbre contient 6: " << (tree.contains(6) ? "oui" : "non") << std::endl;
    std::cout << "L'arbre contient 42: " << (tree.contains(42) ? "oui" : "non") << std::endl;
    

    std::cout << "Suppression de la valeur 3: " << (tree.remove(3) ? "réussi" : "échec") << std::endl;
    
    // Afficher l'arbre après suppression
    std::cout << "Affichage après suppression: ";
    tree.display_infix();
    
    return 0;
}
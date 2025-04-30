#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

// Structure de noeud intelligente pour l'arbre binaire
struct SmartNode;

// Déclaration anticipée
std::unique_ptr<SmartNode> create_smart_node(int value);
std::unique_ptr<SmartNode>& most_left(std::unique_ptr<SmartNode>& node);
bool remove(std::unique_ptr<SmartNode>& node, int value);
bool contains(const std::unique_ptr<SmartNode>& node, int value);

// Structure de noeud intelligente pour l'arbre binaire
struct SmartNode {
    int value;
    std::unique_ptr<SmartNode> left{nullptr};
    std::unique_ptr<SmartNode> right{nullptr};
    
    // Vérifie si le noeud est une feuille (aucun fils)
    bool is_leaf() const {
        // Utilisation de la conversion implicite de unique_ptr en booléen
        return !left && !right;
    }
    
    // Insère un nouveau noeud avec la valeur spécifiée dans l'arbre binaire
    void insert(int value) {
        if (value < this->value) {
            // Si la valeur est inférieure, on l'insère à gauche
            if (!left) {
                left = create_smart_node(value);
            } else {
                left->insert(value);
            }
        } else {
            // Si la valeur est supérieure ou égale, on l'insère à droite
            if (!right) {
                right = create_smart_node(value);
            } else {
                right->insert(value);
            }
        }
    }
    
    // Affiche les valeurs des noeuds dans l'ordre infixe
    void display_infix() const {
        if (left) {
            left->display_infix();
        }
        
        std::cout << value << " ";
        
        if (right) {
            right->display_infix();
        }
    }
    
    // Calcule la hauteur de l'arbre binaire
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
    
    // Retourne la valeur minimale dans l'arbre binaire
    int min() const {
        if (!left) {
            return value;
        }
        return left->min();
    }
    
    // Retourne la valeur maximale dans l'arbre binaire
    int max() const {
        if (!right) {
            return value;
        }
        return right->max();
    }
    
    // Retourne un vecteur avec les noeuds dans l'ordre préfixe
    std::vector<const SmartNode*> prefix() const noexcept {
        std::vector<const SmartNode*> result;
        
        // Ajouter d'abord le noeud courant (racine)
        result.push_back(this);
        
        // Ajouter les noeuds du sous-arbre gauche en préfixe
        if (left) {
            std::vector<const SmartNode*> left_nodes = left->prefix();
            result.insert(result.end(), left_nodes.begin(), left_nodes.end());
        }
        
        // Ajouter les noeuds du sous-arbre droit en préfixe
        if (right) {
            std::vector<const SmartNode*> right_nodes = right->prefix();
            result.insert(result.end(), right_nodes.begin(), right_nodes.end());
        }
        
        return result; 
    }
};

// Crée un nouveau noeud intelligent avec une valeur spécifiée
std::unique_ptr<SmartNode> create_smart_node(int value) {
    return std::make_unique<SmartNode>(SmartNode{value});
}

// Retourne une référence vers le pointeur du noeud le plus à gauche de l'arbre
std::unique_ptr<SmartNode>& most_left(std::unique_ptr<SmartNode>& node) {
    if (!node) {
        return node;
    }
    
    if (!node->left) {
        return node;
    }
    
    return most_left(node->left);
}

// Supprime un noeud avec une valeur spécifique de l'arbre binaire
bool remove(std::unique_ptr<SmartNode>& node, int value) {
    if (!node) {
        return false;
    }
    
    if (value < node->value) {
        return remove(node->left, value);
    }
    
    if (value > node->value) {
        return remove(node->right, value);
    }
    
    // Si on arrive ici, c'est que la valeur du noeud courant est celle à supprimer
    
    // Cas 1: noeud feuille (sans enfants)
    if (node->is_leaf()) {
        node.reset();  // Équivalent à delete node; node = nullptr
        return true;
    }
    
    // Cas 2: Noeud avec un seul enfant
    if (!node->left) {
        // Le noeud n'a qu'un enfant droit
        node = std::move(node->right);  // Transfert de propriété
        return true;
    }
    
    if (!node->right) {
        // Le noeud n'a qu'un enfant gauche
        node = std::move(node->left);  // Transfert de propriété
        return true;
    }
    
    // Cas 3: Noeud avec deux enfants
    // Trouver le successeur inorder (le plus petit noeud dans le sous-arbre droit)
    std::unique_ptr<SmartNode>& successor = most_left(node->right);
    
    // Copier la valeur du successeur dans le noeud courant
    node->value = successor->value;
    
    // Supprimer le successeur (qui a au plus un enfant droit)
    if (!successor->right) {
        successor.reset();
    } else {
        successor = std::move(successor->right);
    }
    
    return true;
}

// Classe BinaryTree qui encapsule la gestion de l'arbre binaire
class BinaryTree {
private:
    std::unique_ptr<SmartNode> root{nullptr};
    
public:
    // Constructeur par défaut
    BinaryTree() = default;
    
    // Constructeur avec valeur initiale
    explicit BinaryTree(int root_value) {
        root = create_smart_node(root_value);
    }
    
    // Insérer une valeur dans l'arbre
    void insert(int value) {
        if (!root) {
            root = create_smart_node(value);
        } else {
            root->insert(value);
        }
    }
    
    // Supprimer une valeur de l'arbre
    bool remove(int value) {
        return ::remove(root, value);
    }
    
    // Vider l'arbre
    void clear() {
        root.reset();
    }
    
    // Vérifier si l'arbre contient une valeur
    bool contains(int value) const {
        return ::contains(root, value);
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
    
    // Valeur minimale
    int min() const {
        if (!root) {
            throw std::runtime_error("Arbre vide");
        }
        return root->min();
    }
    
    // Valeur maximale
    int max() const {
        if (!root) {
            throw std::runtime_error("Arbre vide");
        }
        return root->max();
    }
    
    // Somme des valeurs en utilisant prefix
    int sum() const {
        if (!root) {
            return 0;
        }
        
        std::vector<const SmartNode*> nodes = root->prefix();
        int total = 0;
        for (const auto* node : nodes) {
            total += node->value;
        }
        return total;
    }
};

// Vérifier si un arbre contient une valeur
bool contains(const std::unique_ptr<SmartNode>& node, int value) {
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
    
    std::cout << "Suppression de la valeur 3: " << (tree.remove(3) ? "réussi" : "échec") << std::endl;
    
    std::cout << "Affichage après suppression: ";
    tree.display_infix();
    
    return 0;
}
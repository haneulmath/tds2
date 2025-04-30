#include <iostream>
#include <vector>
#include <algorithm>

// Arbre binaire de recherche
struct Noeud {
    int valeur;
    Noeud* gauche;
    Noeud* droite;
    
    Noeud(int val) : valeur(val), gauche(nullptr), droite(nullptr) {}
    
    // Vérifie si le noeud est une feuille
    bool est_feuille() const {
        return (gauche == nullptr && droite == nullptr);
    }
};

// Crée un nouveau noeud
Noeud* creer_noeud(int valeur) {
    return new Noeud(valeur);
}

// Insère un nouveau noeud
void inserer(Noeud* racine, int valeur) {
    if (valeur < racine->valeur) {
        if (racine->gauche == nullptr) {
            racine->gauche = creer_noeud(valeur);
        } else {
            inserer(racine->gauche, valeur);
        }
    } else {
        if (racine->droite == nullptr) {
            racine->droite = creer_noeud(valeur);
        } else {
            inserer(racine->droite, valeur);
        }
    }
}

// Affiche les valeurs des nœuds dans l'ordre infixe
void afficher_infixe(Noeud* noeud) {
    if (noeud == nullptr) return;
    
    afficher_infixe(noeud->gauche);
    std::cout << noeud->valeur << " ";
    afficher_infixe(noeud->droite);
}

// Calcule la hauteur 
int hauteur(Noeud* noeud) {
    if (noeud == nullptr) return 0;
    if (noeud->est_feuille()) return 1;
    
    return 1 + std::max(
        noeud->gauche ? hauteur(noeud->gauche) : 0,
        noeud->droite ? hauteur(noeud->droite) : 0
    );
}

// Valeur minimale 
int valeur_min(Noeud* noeud) {
    if (noeud->gauche == nullptr) {
        return noeud->valeur;
    }
    return valeur_min(noeud->gauche);
}

// Valeur maximale 
int valeur_max(Noeud* noeud) {
    if (noeud->droite == nullptr) {
        return noeud->valeur;
    }
    return valeur_max(noeud->droite);
}

// Retourne le noeud le plus à gauche
Noeud** le_plus_a_gauche(Noeud** ptr_noeud) {
    if (*ptr_noeud == nullptr) {
        return ptr_noeud;
    }
    
    if ((*ptr_noeud)->gauche == nullptr) {
        return ptr_noeud;
    }
    
    return le_plus_a_gauche(&((*ptr_noeud)->gauche));
}

// Supprime un noeud avec une valeur spécifique
bool supprimer(Noeud** ptr_noeud, int valeur) {
    Noeud* noeud = *ptr_noeud;
    
    if (noeud == nullptr) {
        return false;
    }
    
    if (valeur < noeud->valeur) {
        return supprimer(&(noeud->gauche), valeur);
    }
    
    if (valeur > noeud->valeur) {
        return supprimer(&(noeud->droite), valeur);
    }
    
    // Cas 1: Noeud feuille
    if (noeud->est_feuille()) {
        delete noeud;
        *ptr_noeud = nullptr;
        return true;
    }
    
    // Cas 2: Un seul enfant
    if (noeud->gauche == nullptr) {
        Noeud* temp = noeud;
        *ptr_noeud = noeud->droite;
        delete temp;
        return true;
    }
    
    if (noeud->droite == nullptr) {
        Noeud* temp = noeud;
        *ptr_noeud = noeud->gauche;
        delete temp;
        return true;
    }
    
    // Cas 3: Deux enfants
    Noeud** successeur = le_plus_a_gauche(&(noeud->droite));
    
    noeud->valeur = (*successeur)->valeur;
    
    if ((*successeur)->droite == nullptr) {
        delete *successeur;
        *successeur = nullptr;
    } else {
        Noeud* temp = *successeur;
        *successeur = (*successeur)->droite;
        delete temp;
    }
    
    return true;
}

// Supprime l'arbre entier
void supprimer_arbre(Noeud* noeud) {
    if (noeud == nullptr) return;
    
    supprimer_arbre(noeud->gauche);
    supprimer_arbre(noeud->droite);
    
    delete noeud;
}

int main() {
    Noeud* racine = creer_noeud(5);

    inserer(racine, 3);
    inserer(racine, 7);
    inserer(racine, 2);
    inserer(racine, 4);
    inserer(racine, 6);
    inserer(racine, 8);
    inserer(racine, 1);
    inserer(racine, 9);
    inserer(racine, 0);
    
    std::cout << "Affichage infixe: ";
    afficher_infixe(racine);
    std::cout << std::endl;
    
    // Afficher les valeurs minimale et maximale
    std::cout << "Valeur minimale: " << valeur_min(racine) << std::endl;
    std::cout << "Valeur maximale: " << valeur_max(racine) << std::endl;
    
    // Calculer la somme des valeurs en utilisant prefix
    std::vector<int> noeuds_prefixe;

    std::function<void(Noeud*, std::vector<int>&)> prefix_valeurs = [&](Noeud* noeud, std::vector<int>& resultat) {
        if (noeud == nullptr) return;
        
        resultat.push_back(noeud->valeur);
        prefix_valeurs(noeud->gauche, resultat);
        prefix_valeurs(noeud->droite, resultat);
    };
    
    prefix_valeurs(racine, noeuds_prefixe);
    
    int somme = 0;
    for (int valeur : noeuds_prefixe) {
        somme += valeur;
    }
    
    std::cout << "Somme des valeurs (en utilisant prefix): " << somme << std::endl;
    
    std::cout << "Hauteur de l'arbre: " << hauteur(racine) << std::endl;
    
    supprimer_arbre(racine);
    
    return 0;
}


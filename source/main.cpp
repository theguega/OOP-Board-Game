#include "splendor.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "joueur.hpp"

int main(int argc, const char * argv[]) {
    std::cout << "Bonjour !\nVeuillez creer les joueurs : \n";
    std::string nom, prenom;
    std::string typedejoueur;
    type typeDeJoueur;

    std::cout << "Nom du joueur 1 : ";
    std::cin >> nom;
    std::cout << "Prenom du joueur 1 : ";
    std::cin >> prenom;
    std::cout << "Type de joueur (IA ou HUMAIN) : ";
    std::cin >> typedejoueur;
    typeDeJoueur = toType(typedejoueur);
    Joueur joueur1(nom, prenom, typeDeJoueur);
    std::cout << "\n\n";

    joueur1.afficherJoueur();


    return 0;
}

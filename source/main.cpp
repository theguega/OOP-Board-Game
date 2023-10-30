//
//  main.cpp
//  Projet_LO21
//
//  Created by Theo GUEGAN on 11/09/2023.
//

#include <iostream>
#include "carte.h"
#include <string>
#include <vector>
#include "joueur.hpp"
#include "jetons.hpp"

int main(int argc, const char * argv[]) {
    try
    {
        //Création du lot
        LotDeJetons lot;
        //Création du sac
        Sac sac = Sac(lot);
        //Tirage de 2 jetons
        std::cout << sac.piocherJeton() << "\n";
        std::cout << sac.piocherJeton() << "\n";
        std::cout << sac.piocherJeton() << "\n";
        std::cout << sac.piocherJeton() << "\n";
    }
    catch (JetonException& e)
    {
        std::cout << e.getInfo() << "\n";
    }

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

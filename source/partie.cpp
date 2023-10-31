#include "partie.hpp"
#include "splendor.hpp"
#include "joueur.hpp"
#include "jetons.hpp"
#include "carte.h"
#include "espacejeux.hpp"


Partie::Partie(std::string nomJoueur1, std::string prenomJoueur1) {
    // création et affectation de nouveaux joueurs 
    joueurs[0] = new Joueur(nomJoueur1, prenomJoueur1, type::HUMAIN);
    joueurs[1] = new Joueur("AL", "Gorythme", type::IA);
    tour = 0;
    joueurCourant = 0;
}

Partie::Partie(std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2) {
    // création et affectation de nouveaux joueurs 
    joueurs[0] = new Joueur(nomJoueur1, prenomJoueur1, type::HUMAIN);
    joueurs[1] = new Joueur(nomJoueur2, prenomJoueur2, type::HUMAIN);
    tour = 0;
    joueurCourant = 0;
}

Partie::~Partie() {
    // Libérez la mémoire allouée 
    delete joueurs[0];
    delete joueurs[1];
    delete espaceJeux;
}

void Partie::changerJoueurCourant() {
    switch (joueurCourant) {
        case 0:
            joueurCourant = 1;
            break;
        case 1:
            joueurCourant = 0;
            break;
        default:
            break;
    }
}

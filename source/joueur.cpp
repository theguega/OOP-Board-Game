//
// Created by samma on 28/10/2023.
//

#include "joueur.hpp"
#include <iostream>
#include <string>

// Constructeur
Joueur::Joueur(std::string nom, std::string prenom, bool typeDeJoueur):
               nom(nom), prenom(prenom), typeDeJoueur(typeDeJoueur), score(0), nbCartes(0),
                nbJetons(0), nbPrivileges(0) {

}

// Affichages

void Joueur::afficherJoueur() {
    std::cout << "Nom : " << nom << std::endl;
    std::cout << "Prenom : " << prenom << std::endl;
    std::cout << "Type de joueur : " << typeDeJoueur << std::endl;
    std::cout << "Score : " << score << std::endl;
    std::cout << "Nombre de cartes : " << nbCartes << std::endl;
    std::cout << "Nombre de jetons : " << nbJetons << std::endl;
    std::cout << "Nombre de privilèges : " << nbPrivileges << std::endl;
}

void Joueur::afficherCartes() {
    for (int i = 0; i < nbCartes; i++) {
        std::cout << "Carte " << i << " : " << std::endl;
        //cartes[i]->afficherCarte();
    }
}

void Joueur::afficherJetons() {
    for (int i = 0; i < nbJetons; i++) {
        std::cout << "Jeton " << i << " : " << std::endl;
        //jetons[i]->afficherJeton();
    }
}

// Ajout des éléments

void Joueur::addCarte(Carte *carte) {
    cartes.push_back(carte);
    nbCartes++;
}

void Joueur::addJeton(Jetons *jeton) {
    jetons.push_back(jeton);
    nbJetons++;
}

void Joueur::addPrivilege(Privilege *privilege) {
    privileges.push_back(privilege);
    nbPrivileges++;
}


// Suppression des éléments

void::Joueur::supCarte(Carte *carte) {
    for (int i = 0; i < nbCartes; i++) {
        if (cartes[i] == carte) {
            cartes.erase(cartes.begin() + i);
            nbCartes--;
        }
    }
}

void::Joueur::supJeton(Jetons *jeton) {
    for (int i = 0; i < nbJetons; i++) {
        if (jetons[i] == jeton) {
            jetons.erase(jetons.begin() + i);
            nbJetons--;
        }
    }
}

void::Joueur::supPrivilege() {
    privileges.erase(privileges.begin());
    nbPrivileges--;
}
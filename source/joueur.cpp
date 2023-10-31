#include "joueur.hpp"

std::string toStringType(type t) {
    switch (t) {
        case type::IA: return "IA";
        case type::HUMAIN: return "HUMAIN";
    }
    throw JoueurException("Type inconnu");
}

type toType(std::string s) {
    if (s == "IA") return type::IA;
    return type::HUMAIN;
}

// Constructeur
Joueur::Joueur(std::string nom, std::string prenom, type typeDeJoueur):
               nom(nom), prenom(prenom), typeDeJoueur(typeDeJoueur), score(0), nbCartes(0),
                nbJetons(0), nbPrivileges(0) {

}

// Destructeur
Joueur::~Joueur() {
    for (int i = 0; i < nbCartes; i++) {
        delete cartes[i];
    }
    for (int i = 0; i < nbJetons; i++) {
        delete jetons[i];
    }
    for (int i = 0; i < nbPrivileges; i++) {
        delete privileges[i];
    }
}

// Affichages

void Joueur::afficherJoueur() const {
    std::cout << "Nom : " << nom << std::endl;
    std::cout << "Prenom : " << prenom << std::endl;
    std::cout << "Type de joueur : " << toStringType(typeDeJoueur) << std::endl;
    std::cout << "Score : " << score << std::endl;
    std::cout << "Nombre de cartes : " << nbCartes << std::endl;
    std::cout << "Nombre de jetons : " << nbJetons << std::endl;
    std::cout << "Nombre de privilèges : " << nbPrivileges << std::endl;
}

void Joueur::afficherCartes() const {
    for (int i = 0; i < nbCartes; i++) {
        std::cout << "Carte " << i << " : " << std::endl;
        //cartes[i]->afficherCarte();
    }
}

void Joueur::afficherJetons() const {
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

void Joueur::addJeton(Jeton *jeton) {
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

void::Joueur::supJeton(Jeton *jeton) {
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
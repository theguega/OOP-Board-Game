#include "splendor.hpp"
#include "jetons.hpp"
#include "strategy.hpp"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>

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
               nom(nom), prenom(prenom), typeDeJoueur(typeDeJoueur),  nbCartes(0),
                nbJetons(0), nbPrivileges(0), ptsPrestige(0), nbCouronnes(0) {

}

// Destructeur
Joueur::~Joueur() {
    // Voir l'interet d'un destructeur
    /*
    for (int i = 0; i < nbCartes; i++) {
        delete cartes[i];
    }
    for (int i = 0; i < nbJetons; i++) {
        delete jetons[i];
    }
    for (int i = 0; i < nbPrivileges; i++) {
        delete privileges[i];
    }*/
}

// Affichages

void Joueur::afficherJoueur() const {
    std::cout << "Nom : " << nom << std::endl;
    std::cout << "Prenom : " << prenom << std::endl;
    std::cout << "Type de joueur : " << toStringType(typeDeJoueur) << std::endl;
    std::cout << "Points de prestiges : " << ptsPrestige << std::endl;
    std::cout << "Nombre de couronnes : " << nbCouronnes << std::endl;
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
    //cartes[carte->getCouleur()].push_back(carte);
    nbCartes++;
    //ptsPrestige += carte->getPtsPrestige();
    //nbCouronnes += carte->getNbCouronnes();
}

void Joueur::addJeton(Jeton *jeton) {
    jetons[jeton->getCouleur()].push_back(jeton);
    nbJetons++;
}

void Joueur::addPrivilege(Privilege *privilege) {
    privileges.push_back(privilege);
    nbPrivileges++;
}


// Suppression des éléments

void::Joueur::supCarte(Carte *carte) {
    /*
    for (int i = 0; i < cartes[carte->getBonus()->getCouleur]; i++) {
        if (cartes[carte->getBonus()->getCouleur][i] == carte) {
            //nbCouronnes -= carte->getNbCouronnes();
            //ptsPrestige -= carte->getPtsPrestige();
            cartes[carte->getBonus()->getCouleur].erase(cartes[carte->getBonus()->getCouleur].begin() + i);
            nbCartes--;
        }
    }*/
}

void::Joueur::supJeton(Jeton *jeton) {
    for (int i = 0; i < jetons[jeton->getCouleur()].size(); i++) {
        if (jetons[jeton->getCouleur()][i] == jeton) {
            jetons[jeton->getCouleur()].erase(jetons[jeton->getCouleur()].begin() + i);
            nbJetons--;
        }
    }
}

void::Joueur::supPrivilege() {
    privileges.erase(privileges.begin());
    nbPrivileges--;
}

bool::Joueur::nbPtsPrestigeParCouleurSupDix() const {
    for (auto it = cartes.begin(); it != cartes.end(); it++) {
        std::vector<Carte*> tab = it->second;
        int somme = 0;
        for (int i = 0; i < tab.size(); ++i) {
            //somme += tab[i]->getNbPtsPrivilege();
        }
        if (somme >= 10) {
            return true;
        }
    }
    return false;
}
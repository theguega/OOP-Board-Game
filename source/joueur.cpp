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
Joueur::Joueur(string pseudo, type typeDeJoueur):
               pseudo(pseudo), typeDeJoueur(typeDeJoueur), nbCartes(0),
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
    std::cout << "Pseudo : " << pseudo << std::endl;
    std::cout << "Type de joueur : " << toStringType(typeDeJoueur) << std::endl;
    std::cout << "Points de prestiges : " << ptsPrestige << std::endl;
    std::cout << "Nombre de couronnes : " << nbCouronnes << std::endl;
    std::cout << "Nombre de cartes : " << nbCartes << std::endl;
    std::cout << "Nombre de jetons : " << nbJetons << std::endl;
    std::cout << "Nombre de privileges : " << nbPrivileges << std::endl;
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

void Joueur::addCarte(const Carte &carte) {
    cartes[carte.getBonus().getCouleur()].push_back(&carte);
    nbCartes++;
    ptsPrestige += carte.getNbPtsPrivilege();
    nbCouronnes += carte.getNbCouronnes();
}

void Joueur::addCarteReservee(const Carte &carte) {
    cartesReservees.push_back(&carte);
    nbCartes++;

}

void Joueur::addJeton(const Jeton& jeton) {
    jetons[jeton.getCouleur()].push_back(&jeton);
    nbJetons++;
}

void Joueur::addPrivilege(const Privilege &privilege) {
    privileges.push_back(&privilege);
    nbPrivileges++;
}


// Suppression des éléments

void::Joueur::supCarte(Carte &carte) {
    for (int i = 0; i < cartes[carte.getBonus().getCouleur()].size(); i++) {
        if (cartes[carte.getBonus().getCouleur()][i] == &carte) {
            nbCouronnes -= carte.getNbCouronnes();
            ptsPrestige -= carte.getNbPtsPrivilege();
            cartes[carte.getBonus().getCouleur()].erase(cartes[carte.getBonus().getCouleur()].begin() + i);
            nbCartes--;
        }
    }
}

void::Joueur::supCarteReservee(const Carte &carte) {
    for (int i = 0; i < cartesReservees.size(); i++) {
        if (cartesReservees[i] == &carte) {
            cartesReservees.erase(cartesReservees.begin() + i);
            nbCartesReservees--;
        }
    }
}

void::Joueur::supJeton(Jeton *jeton) {
    for (int i = 0; i < jetons[jeton->getCouleur()].size(); i++) {
        if (jetons[jeton->getCouleur()][i] == jeton) {
            jetons[jeton->getCouleur()].erase(jetons[jeton->getCouleur()].begin() + i);
            nbJetons--;
        }
    }
}

const Privilege&::Joueur::supPrivilege() {
    const Privilege& sup = *privileges[0];
    privileges.erase(privileges.begin());
    nbPrivileges--;
    return  sup;
}



bool Joueur::nbPtsPrestigeParCouleurSupDix() const{
    // Itère sur toutes les couleurs
    for (const auto& pair : cartes) {
        const std::vector<const Carte*>& tab = pair.second;
        unsigned int somme = 0;

        // Calcule la somme pour chaque couleur
        for (const auto* carte : tab) somme += carte->getNbPtsPrivilege();
        if (somme >= 10) return true;
    }
    return false;
}


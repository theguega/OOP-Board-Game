#include "jetons.hpp"
#include "joueur.hpp"
#include "strategy.hpp"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <utility>

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



///////////////////////// Actions d'un joueur /////////////////////////

void Joueur::utiliserPrivilege(Plateau& plateau){
    if (nbPrivileges == 0) {
        throw JoueurException("Le joueur n'a pas de privilège");
    }
    /*if (plateau.getNbJtons()==0){
        throw JoueurException("Le plateau n'a pas de jetons");
    }*/
    const Privilege& privilege = supPrivilege();
    plateau.poserPrivilege(privilege);
    const Jeton& jetonSelec = strategy->choisirJeton(plateau);
    addJeton(jetonSelec);

}

void Joueur::remplirPlateau(Plateau& plateau, Sac& sac, Joueur& joueurAdverse){
    strategy->remplirPlateauStrat(plateau, sac);
    if (nbPrivileges == 3){
        std::cout<< "Vous avez deja 3 privileges. Vous n'en recupererez donc pas plus !" << std::endl;
        return;
    }
    // Verifier s'il reste des privileges sur le plateau
    if (!plateau.pivilegeDisponible()){
        std::cout<< "Il n'y a plus de privileges sur le plateau !\nLe joueur adverse perd donc un privilege..." << std::endl;
        const Privilege& privilege = joueurAdverse.supPrivilege(); // recuperation du privilege du joueur adverse
        addPrivilege(privilege); // ajout du privilege au joueur
        return;
    }
    // Cas standard
    const Privilege& privilege = plateau.recupererPrivilege();
    addPrivilege(privilege);
}

void Joueur::recupererJetons(Plateau& plateau){
    std::cout << "Combien de jetons souhaitez-vous recuperer ? (1 a 3)" << std::endl;
    unsigned int nbJetonsRecup;
    std::cin >> nbJetonsRecup;
    if (nbJetonsRecup > 3 || nbJetonsRecup < 1){
        throw JoueurException("Le nombre de jetons est impossible");
    }

    std::cout << "Merci de selectionner des jetons adjacents en ligne, en colonne ou en diagonale." << std::endl;

    std::vector<std::pair<unsigned int, unsigned int>> vecteurCoordonnees;
    std::vector<const Jeton*> jetonsRecup;


    for (int k = 0; k < nbJetonsRecup; k++){
        unsigned int i, j;
        std::cout << "Entrez la valeur de i : ";
        std::cin >> i;
        std::cout << "Entrez la valeur de j : ";
        std::cin >> j;
        const Jeton& jeton = plateau.recupererJeton(i, j);
        // Ajout des coordonnees
        vecteurCoordonnees.push_back(std::make_pair(i, j));
        // Ajout du jeton
        jetonsRecup.push_back(&jeton);
    }

    // Verifier que les jetons sont adjacents
    if (nbJetons > 1) {
        bool result1 = true;
        bool result2 = true;
        bool result3 = true;

        for (int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            if (vecteurCoordonnees[i].first != vecteurCoordonnees[i + 1].first) {
                result1 = false;
            }
        }
        for (int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            if (vecteurCoordonnees[i].second != vecteurCoordonnees[i + 1].second) {
                result2 = false;
            }
        }
        for (int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            // A modifier pour les diagonales
            if (vecteurCoordonnees[i].second != vecteurCoordonnees[i + 1].second-1 ) {
                result3 = false;
            }
        }

        if (!result1 && !result2 && !result3) {
            throw JoueurException("Les jetons ne sont pas adjacents");
        }

    }

    // ajout des jetons dans la main du joueur
    for (int i = 0; i < jetonsRecup.size(); i++){
        addJeton(*jetonsRecup[i]);
    }

}

void Joueur::orReserverCarte (Pyramide& pyramide, Plateau& plateau){
    std::cout<<"Volez-vous réserver une carte de la pyramide ou de la pioche de niveau i ? (0, 1, 2, 3)" << std::endl;
    unsigned int choix;
    std::cin >> choix;

    if (choix == 0){
        // Reservation de la carte
        std::cout << "Voici les cartes de la pyramide : " << std::endl;
        pyramide.afficherPyramide();
        std::cout << "Tapez le niveau de la carte que vous voulez réserver : " << std::endl;
        unsigned int niveau;
        std::cin >> niveau;
        std::cout << "Tapez le numero de la carte que vous voulez réserver : " << std::endl;
        unsigned int numCarte;
        std::cin >> numCarte;
        // Vérifications
        if (numCarte > pyramide.getNbCartesNiv(niveau)){
            throw JoueurException("Le numéro de la carte est incorrect");
        }
        const Carte& carte = pyramide.reserverCarte(niveau, numCarte);
        addCarteReservee(carte);
        
        //pyramide.supprimerCarte(niveau, numCarte);

        // Recuperation d'un jeton or
        const Jeton& jeton = strategy->choisirJeton(plateau);
        if(jeton.getCouleur() != CouleurJeton::OR){
            throw JoueurException("Le jeton choisi n'est pas un jeton or");
        }
        addJeton(jeton);


    }
    else if (choix == 1 || choix == 2 || choix == 3){
        // Reservation de la carte
        const Carte& carte = pyramide.ReserverCartePioche(choix);
        addCarteReservee(carte);

        // Recuperation d'un jeton or
        const Jeton& jeton = strategy->choisirJeton(plateau);
        if(jeton.getCouleur() != CouleurJeton::OR){
            throw JoueurException("Le jeton choisi n'est pas un jeton or");
        }
        addJeton(jeton);
    }


}

void Joueur::acheterCarteJoaillerie (Pyramide& pyramide){
    // Voir comment gérer les bonus
    std::cout << "Tapez 1 pour acheter une carte Réservée.\nTapez 2 pour acheter une carte du plateau." << std::endl;
    unsigned int choix;
    std::cin >> choix;
    // Achat carte reservee
    if (choix == 1){
        std::cout << "Voici les cartes réservées : " << std::endl;
        unsigned int i = 0;
        // Affichage de la réserve
        for (auto & cartesReservee : cartesReservees) {
            std::cout <<"Numéro "<<i << " : ";
            std::cout<<cartesReservee;
            i++;
        }
        std::cout << "Tapez le numéro de la carte que vous voulez acheter : " << std::endl;
        unsigned int numCarte;
        std::cin >> numCarte;
        // Vérifications -> voir plus au niveau des jetons dans la main
        if (numCarte > cartesReservees.size()){
            throw JoueurException("Le numéro de la carte est invalide.");
        }
        const Carte& carte = *cartesReservees[numCarte];
        if (carte.getNbPtsPrivilege() > ptsPrestige){
            throw JoueurException("Vous n'avez pas assez de points de prestige pour acheter cette carte...");
        }
        addCarte(carte);
        supCarteReservee(carte);
    }
    // Achat carte du plateau
    else if (choix == 2){
        // Affichage des cartes
        std::cout << "Voici les cartes du plateau : " << std::endl;
        pyramide.afficherPyramide(); //Gerer l'affichage de la pyramide

        std::cout << "Tapez le niveau de la carte que vous voulez acheter : " << std::endl;
        unsigned int niveau;
        std::cin >> niveau;
        std::cout << "Tapez le numero de la carte que vous voulez acheter : " << std::endl;
        unsigned int numCarte;
        std::cin >> numCarte;

        // Vérifications
        if (numCarte > pyramide.getNbCartesNiv(niveau)){
            throw JoueurException("Le numéro de la carte est incorrect");
        }
        
        const Carte& carte = pyramide.acheterCarte(niveau, numCarte);
        if (carte.getNbPtsPrivilege() > ptsPrestige){
            throw JoueurException("Vous n'avez pas assez de points de prestige pour acheter cette carte");
        }
        addCarte(carte);
        //pyramide.supprimerCarte(niveau, numCarte);*/
    }
    else {
        throw JoueurException("Le choix est incorrect");
    }


}


#include "joueur.hpp"
#include <algorithm>


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
               pseudo(pseudo), typeDeJoueur(typeDeJoueur), ptsPrestige(0), nbCouronnes(0), gagnant(0) {


                //on initialise les map avec les bonnes couleurs
                for (const auto& couleur : Couleurs) {
                    if (couleur != Couleur::INDT) {
                        jetons[couleur];
                        if (couleur != Couleur::OR) {
                            cartes[couleur];
                            cartesReservees[couleur];
                            bonus[couleur] = 0;
                        }
                    }
                }

    // Créer la stratégie en fonction du type de joueur
    if (typeDeJoueur == type::IA) {
        strategy = new StrategyIA();  // Vous devez définir le constructeur de StrategyIA
    } else {
        strategy = new StrategyHumain();  // Vous devez définir le constructeur de StrategyHumain
    }
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

// Getter
size_t Joueur::getNbCartes() const {
    size_t nbCartes = 0;
    for (const auto& couleur : Couleurs) {
        if (couleur != Couleur::INDT && couleur != Couleur::OR) {
            nbCartes += cartes.at(couleur).size();
        }
    }

    return nbCartes;
}

size_t Joueur::getNbCartesReservees() const {
    size_t nbCartes = 0;
    for (const auto& couleur : Couleurs) {
        if (couleur != Couleur::INDT && couleur != Couleur::OR) {
            nbCartes += cartesReservees.at(couleur).size();
        }
    }

    return nbCartes;
}

size_t Joueur::getNbJetons() const {
    size_t nbJetons = 0;
    for (const auto& couleur : Couleurs) {
        if (couleur != Couleur::INDT && couleur != Couleur::OR) {
            nbJetons += jetons.at(couleur).size();
        }
    }

    return nbJetons;
}

// Affichages

void Joueur::afficherJoueur() const {
    std::cout << "Pseudo : " << pseudo << std::endl;
    std::cout << "Type de joueur : " << toStringType(typeDeJoueur) << std::endl;
    std::cout << "Points de prestiges : " << ptsPrestige << std::endl;
    std::cout << "Nombre de couronnes : " << nbCouronnes << std::endl;
    std::cout << "Nombre de cartes : " << getNbCartes() << std::endl;
    std::cout << "Nombre de cartes reservees : " << getNbCartesReservees() << std::endl;
    std::cout << "Nombre de jetons : " << getNbJetons() << std::endl;
    std::cout << "Nombre de privileges : " << getNbPrivileges() << std::endl;
}

void Joueur::afficherCartes() const {
    for (size_t i = 0; i < getNbCartes(); i++) {
        std::cout << "Carte " << i << " : " << std::endl;
        //cartes[i]->afficherCarte();
    }
}

void Joueur::afficherJetons() const {
    for (size_t i = 0; i < getNbJetons(); i++) {
        std::cout << "Jeton " << i << " : " << std::endl;
        //jetons[i]->afficherJeton();
    }
}

// Ajout des éléments

void Joueur::addCarte(const Carte &carte) {
    cartes[carte.getBonus().getCouleur()].push_back(&carte);
    ptsPrestige += carte.getNbPtsPrivilege();
    nbCouronnes += carte.getNbCouronnes();
}

void Joueur::addCarteReservee(const Carte &carte) {
    cartesReservees[carte.getBonus().getCouleur()].push_back(&carte);
}

void Joueur::addCarteNoble(const Carte& carte){
    cartesNobles.push_back(&carte);
}

void Joueur::addJeton(const Jeton& jeton) {
    jetons[jeton.getCouleur()].push_back(&jeton);
}

void Joueur::addPrivilege(const Privilege &privilege) {
    privileges.push_back(&privilege);
}


// Suppression des éléments

void::Joueur::supCarte(Carte &carte) {
    for (size_t i = 0; i < cartes[carte.getBonus().getCouleur()].size(); i++) {
        if (cartes[carte.getBonus().getCouleur()][i] == &carte) {
            nbCouronnes -= carte.getNbCouronnes();
            ptsPrestige -= carte.getNbPtsPrivilege();
            cartes[carte.getBonus().getCouleur()].erase(cartes[carte.getBonus().getCouleur()].begin() + i);
        }
    }
}

void::Joueur::supCarteReservee(const Carte &carte) {
    for (size_t i = 0; i < cartes[carte.getBonus().getCouleur()].size(); i++) {
        if (cartesReservees[carte.getBonus().getCouleur()][i] == &carte) {
            cartesReservees[carte.getBonus().getCouleur()].erase(cartes[carte.getBonus().getCouleur()].begin() + i);
        }
    }
}

void Joueur::supCarteNoble(const Carte& carte){
    for (size_t i = 0; i < cartesNobles.size(); i++) {
        if (cartesNobles[i] == &carte) {
            cartesNobles.erase(cartesNobles.begin()+i);
        }
    }
}

void::Joueur::supJeton(Jeton *jeton, EspaceJeux& espaceJeux) {
    for (size_t i = 0; i < jetons[jeton->getCouleur()].size(); i++) {
        if (jetons[jeton->getCouleur()][i] == jeton) {
            // On rajoute le jeton dans le sac
            espaceJeux.getSac().ajouterJeton(*jetons[jeton->getCouleur()][i]);
            jetons[jeton->getCouleur()].erase(jetons[jeton->getCouleur()].begin() + i);
        }
    }
}

void Joueur::supJetonNb(unsigned int nb, Couleur c, EspaceJeux& espaceJeux){
    for (size_t i = 0; i < nb; i++) {
        // On rajoute le jeton dans le sac
        espaceJeux.getSac().ajouterJeton(*jetons[c].back());
        // On supprime le jeton du joueur
        jetons[c].pop_back();
    }

}

const Privilege&::Joueur::supPrivilege(Plateau& plateau) {
    const Privilege& sup = *privileges[0];
    privileges.erase(privileges.begin());
    // rajout du privilège sur le plateau
    plateau.poserPrivilege(sup);

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




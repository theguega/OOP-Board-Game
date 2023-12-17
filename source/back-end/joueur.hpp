#ifndef PROJET_LO21_JOUEUR_HPP
#define PROJET_LO21_JOUEUR_HPP

/*
-------------------------------------
       _
      | |
      | | ___  _   _  ___ _   _ _ __
  _   | |/ _ \| | | |/ _ \ | | | '__|
 | |__| | (_) | |_| |  __/ |_| | |
  \____/ \___/ \__,_|\___|\__,_|_|

-------------------------------------
*/

#include <unordered_map>

#include "jetons.hpp"
#include "carte.hpp"
#include "strategy.hpp"




enum class type { IA, HUMAIN };
std::string toStringType(type t);
type toType(std::string s);




class Joueur {
private:
    const string pseudo;
    const type typeDeJoueur;
    unsigned int ptsPrestige;
    unsigned int nbCouronnes;
    bool gagnant;
    std::unordered_map<Couleur, std::vector<const Carte*>> cartes;
    std::unordered_map<Couleur, std::vector<const Carte*>> cartesReservees;
    std::unordered_map<Couleur, std::vector<const Jeton*>> jetons;
    std::vector<const Carte*> cartesNobles;
    std::vector<const Privilege*> privileges;
    std::unordered_map<Couleur, unsigned int> bonus;

    Strategy* strategy;
public:
    Joueur(string pseudo, type typeDeJoueur);
    ~Joueur();

    // Getters
    std::string getPseudo() const { return pseudo; }
    type getTypeDeJoueur() const { return typeDeJoueur; }
    unsigned int getptsPrestige() const { return ptsPrestige; }
    unsigned int getnbCouronnes() const { return nbCouronnes; }
    size_t getNbCartes() const;
    size_t getNbCartes(Couleur c) const { return cartes.at(c).size(); }
    size_t getNbCartesReservees() const;
    size_t getNbCartesNobles() const { return cartesNobles.size(); }
    size_t getNbCartesReservees(Couleur c) const { return cartesReservees.at(c).size(); }
    size_t getNbJetons() const;
    size_t getNbJetons(Couleur c) const { return jetons.at(c).size(); }
    size_t getNbPrivileges() const { return privileges.size(); }
    const Carte& getCarte(Couleur c, size_t i) const { return *cartes.at(c).at(i); }
    const Carte& getCarteReservee(Couleur c, size_t i) const { return *cartesReservees.at(c).at(i); }
    const Carte& getCarteNoble(size_t i) const { return *cartesNobles[i]; }
    unsigned int getNbCouronnes ()const { return nbCouronnes; }


    // Setters et updater
    void updatePtsPrestige(int pts) { ptsPrestige += pts; }
    void updateNbCouronnes(int couronnes) { nbCouronnes += couronnes; }

    void addCarte(const Carte &carte);
    void addCarteReservee(const Carte &carte) ;
    void addCarteNoble(const Carte& carte);
    void addJeton(const Jeton &jeton);
    void addPrivilege(const Privilege &privilege);
    void addBonus(Couleur c, int nb);


    void supCarte(Carte &carte);
    void supCarteReservee(const Carte &carte);
    void supCarteNoble(const Carte& carte);
    void supJeton(Jeton *jeton, EspaceJeux& espaceJeux);
    void supJetonNb(unsigned int nb, Couleur c, EspaceJeux& espaceJeux);
    void supJetonPrix(Carte& c, EspaceJeux& espaceJeux);
    const Privilege& supPrivilege();
    void setGagnant() {gagnant=true;}

    const Jeton& RecupJetonCoul(Couleur c);

    // Affichage
    void afficherJoueur() const;
    void afficherCartes() const;
    void afficherJetons() const;
    void afficherPrivileges() const{
        std::cout << "Nombre de privilèges : " << &privileges << std::endl;
    }

    // Verifs
    bool nbPtsPrestigeParCouleurSupDix() const;
    bool estGagnant() const { return gagnant;}

    friend class Controller;
};

#endif

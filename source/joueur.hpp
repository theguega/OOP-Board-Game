//
// Created by samma on 28/10/2023.
//

#ifndef PROJET_LO21_JOUEUR_HPP
#define PROJET_LO21_JOUEUR_HPP

#include "splendor.hpp"
#include "jetons.hpp"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include "strategy.hpp"




// Rajouter classe exception
class JoueurException
{
public:
    JoueurException(const std::string& i) :info(i) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};



enum class type { IA, HUMAIN };

std::string toStringType(type t);

type toType(std::string s);

class Joueur {
private:
    // Rajouter un tab static avec les deux joueurs
    const std::string nom;
    const std::string prenom;
    const type typeDeJoueur;
    int ptsPrestige;
    int nbCouronnes;

    std::unordered_map</*CouleurCarte*/ CouleurJeton, std::vector<Carte*>> cartes;
    size_t nbCartes;
    std::unordered_map<CouleurJeton, std::vector<const Jeton*>> jetons;
    size_t nbJetons;
    std::vector<const Privilege*> privileges;
    size_t nbPrivileges;
    Strategy* strategy;
public:
    // Constructeur done
    Joueur(std::string nom, std::string prenom, type typeDeJoueur);

    // Destructeur
    ~Joueur();



    // Getters Done
    std::string getNom() const { return nom; };
    std::string getPrenom() const { return prenom; };
    type getTypeDeJoueur() const { return typeDeJoueur; };
    int getptsPrestige() const { return ptsPrestige; };
    int getnbCouronnes() const { return nbCouronnes; };
    //Carte **getCartes();
    size_t getNbCartes() const { return nbCartes; }
    //Jetons **getJetons();
    size_t getNbJetons() const { return nbJetons; }
    //Privilege **getPrivileges();
    size_t getNbPrivileges() const { return nbPrivileges; }

    bool nbPtsPrestigeParCouleurSupDix() const;

    // Setters
    void updatePtsPrestige(int pts) { ptsPrestige += pts; };
    void updateNbCouronnes(int couronnes) { nbCouronnes += couronnes; };

    void addCarte(Carte *carte);
    void addJeton(const Jeton &jeton);
    void addPrivilege(const Privilege &privilege);

    // Supprimer un element du vecteur --> attention il faudra voir le lien avec les autres classes DONE
    // Si on supprime un privilège il doit revenir sur le plateau
    void supCarte(Carte *carte);
    void supJeton(Jeton *jeton);
    const Privilege& supPrivilege(); // a voir si on retire pas juste le premier privilege

    // Affichage Done
    void afficherJoueur() const;
    void afficherCartes() const;
    void afficherJetons() const;
    void afficherPrivileges() const{
        std::cout << "Nombre de privilèges : " << &privileges << std::endl;
    }


    void utiliserPrivilège(Plateau& plateau);


};


#endif //PROJET_LO21_JOUEUR_HPP

#ifndef PROJET_LO21_JOUEUR_HPP
#define PROJET_LO21_JOUEUR_HPP

#include "splendor.hpp"
#include "jetons.hpp"

#include <iostream>
#include <string>
#include <array>
#include <vector>

enum class type { IA, HUMAIN };

std::string toStringType(type t);

type toType(std::string s);

class Joueur {
private:
    // Rajouter un tab static avec les deux joueurs
    const std::string nom;
    const std::string prenom;
    const type typeDeJoueur;
    int score;
    std::vector<Carte*> cartes;
    int nbCartes;
    std::vector<Jeton*> jetons;
    int nbJetons;
    std::vector<Privilege*> privileges;
    int nbPrivileges;
public:
    // Constructeur done
    Joueur(std::string nom, std::string prenom, type typeDeJoueur);

    // Destructeur
    ~Joueur();

    // Getters Done
    std::string getNom() const { return nom; };
    std::string getPrenom() const { return prenom; };
    type getTypeDeJoueur() const { return typeDeJoueur; };
    int getScore() const { return score; };
    //Carte **getCartes();
    int getNbCartes() const { return nbCartes; }
    //Jetons **getJetons();
    int getNbJetons() const { return nbJetons; }
    //Privilege **getPrivileges();
    int getNbPrivileges() const { return nbPrivileges; }

    // Setters
    void updateScore(int s) { score += s; };

    void addCarte(Carte *carte);
    void addJeton(Jeton *jeton);
    void addPrivilege(Privilege *privilege);

    // Supprimer un element du vecteur --> attention il faudra voir le lien avec les autres classes DONE
    // Si on supprime un privilège il doit revenir sur le plateau
    void supCarte(Carte *carte);
    void supJeton(Jeton *jeton);
    void supPrivilege(); // a voir si on retire pas juste le premier privilege

    // Affichage Done
    void afficherJoueur() const;
    void afficherCartes() const;
    void afficherJetons() const;


    // surchages
};


#endif //PROJET_LO21_JOUEUR_HPP

//
// Created by samma on 28/10/2023.
//

#ifndef PROJET_LO21_JOUEUR_HPP
#define PROJET_LO21_JOUEUR_HPP

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "splendor.hpp"

enum class type { IA, HUMAIN };

class Joueur {
private:
    std::string nom;
    std::string prenom;
    type typeDeJoueur;
    int score;
    std::vector<Carte*> cartes;
    int nbCartes;
    std::vector<Jetons*> jetons;
    int nbJetons;
    std::vector<Privilege*> privileges;
    int nbPrivileges;
public:
    // Constructeur done
    Joueur(std::string nom, std::string prenom, bool typeDeJoueur);

    // Destructeur
    ~Joueur();

    // Getters Done
    std::string getNom() { return nom; };
    std::string getPrenom() { return prenom; };
    type getTypeDeJoueur() { return typeDeJoueur; };
    int getScore() { return score; };
    //Carte **getCartes();
    int getNbCartes() { return nbCartes; }
    //Jetons **getJetons();
    int getNbJetons() { return nbJetons; }
    //Privilege **getPrivileges();
    int getNbPrivileges() { return nbPrivileges; }

    // Setters
    void updateScore(int s) { score += s; };

    void addCarte(Carte *carte);
    void addJeton(Jetons *jeton);
    void addPrivilege(Privilege *privilege);

    // Supprimer un element du vecteur --> attention il faudra voir le lien avec les autres classes DONE
    // Si on supprime un privilège il doit revenir sur le plateau
    void supCarte(Carte *carte);
    void supJeton(Jetons *jeton);
    void supPrivilege(); // a voir si on retire pas juste le premier privilege

    // Affichage Done
    void afficherJoueur();
    void afficherCartes();
    void afficherJetons();


    // surchages
};


#endif //PROJET_LO21_JOUEUR_HPP

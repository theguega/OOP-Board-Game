#ifndef SPLENDOR_H
#define SPLENDOR_H

#include <string>
#include <vector>

// Définition de l'énumération pour la couleur des jetons
enum class CouleurJeton { RUBIS, SAPHIR, ÉMERAUDE, ONYX, DIAMANT, OR, PERLE };

// Déclaration de la classe Jetons
class Jetons {
    //Theo
public:
    CouleurJeton couleur;

    // Constructeur de Jetons
    Jetons(CouleurJeton couleur) : couleur(couleur) {}
};

// Déclaration de la classe Privilege
class Privilege {
    //Theo
public:
    void utiliserPrivilege();
};

// Déclaration de la classe Carte
class Carte {
    //Samuel B
private:
    // Définition de la structure Jetons pour le coût et le bonus
    struct Jetons {
        CouleurJeton couleur;
        int quantite;
    };

    Jetons cout;
    Jetons bonus;
    int nbCouronnes;
    int nbPtsPrivilege;

public:
    // Constructeur de Carte
    Carte(Jetons cout, Jetons bonus, int nbCouronnes, int nbPtsPrivilege)
        : cout(cout), bonus(bonus), nbCouronnes(nbCouronnes), nbPtsPrivilege(nbPtsPrivilege) {}
};

// Déclaration de la classe Sac
class Sac {
public:
    Plateau remplirPlateau();
};

// Déclaration de la classe Pyramide
class Pyramide {
public:
    void reserverCarte();
    void acheterCarte();
};

// Déclaration de la classe Plateau
class Plateau {
    //Theo
private:
    std::vector<std::vector<Jetons>> matriceJetons;

public:
    Privilege privilege;

    Plateau();
    void remplirPlateau();
    Jetons recupererJeton();
};

// Déclaration de la classe Joueur
class Joueur {
    //Samuel M
private:
    std::string nom;
    int score;
    Jetons jetons;
    Carte cartes;
    Privilege privilege;

public:
    int getNbCouronnes();
    int getNbPrestige();
    int getPtsBonus();
};

// Déclaration de la classe EspaceJeux
class EspaceJeux {
public:
    Sac sac;
    Pyramide pyramide;
    Plateau plateau;
};

// Déclaration de la classe Partie
class Partie {
    //Robert
private:
    Joueur joueur1;
    Joueur joueur2;
    EspaceJeux espaceJeux;
    int tour;

public:
    bool finPartie();
};

// Déclaration de la classe Jeu
class Jeu {
public:
    Partie lancer();
    bool conditionsVictoire();
};

class I_A {

};

class Physique {

};

class JeuDeCarte {
};

class LotJetons {

};

#endif // SPLENDOR_H
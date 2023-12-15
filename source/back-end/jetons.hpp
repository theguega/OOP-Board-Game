#ifndef JETONS_H
#define JETONS_H 

#include <iostream>
#include <random>
#include <array>
#include <unordered_map>
#include <map>
#include <string>
#include "back-end/exception.hpp"
#include <QDebug>
using namespace std;

//Enum pour les couleurs : initialiser, to string, affichage, string to couleur.
enum class Couleur { BLANC, BLEU, VERT, ROUGE, NOIR, PERLE, OR, INDT};
std::string toStringCouleur(Couleur c);
std::string toEmojiCouleur(Couleur c);
std::ostream& operator<<(std::ostream& f, Couleur c);
QDebug operator<<(QDebug f, const Couleur &c);
extern std::initializer_list<Couleur> Couleurs;
extern std::map<string, Couleur> stringToCouleurMap;
Couleur StringToCouleur(const string& couleurStr);

//Classe Jetons
class Jeton {
    private :
        const Couleur couleur;
    public :
        Jeton(Couleur c) : couleur(c) {}
        Couleur getCouleur() const { return couleur; }
};
std::ostream& operator<< (std::ostream& f, const Jeton& jeton);
QDebug operator<<(QDebug f, const Jeton &jeton);
std::ostream& operator<< (std::ostream& f, const Jeton* jeton);
QDebug operator<<(QDebug f, const Jeton* jeton);

class LotDeJetons {
    private :
        std::vector<const Jeton*> jetons;
        //max de chaque jetons
        const size_t max_or = 3;
        const size_t max_perle = 2;

        const size_t max_rouge = 4;
        const size_t max_noir = 4;
        const size_t max_bleu = 4;
        const size_t max_blanc = 4;
        const size_t max_vert = 4;

        //Constructeur non accessible par l'utilisateur : singleton
        LotDeJetons();
        ~LotDeJetons();

        //pas de duplication du lot de jetons
        LotDeJetons(const LotDeJetons&) = delete;
        LotDeJetons& operator=(const LotDeJetons&) = delete;
    public:
        size_t getNbJetons() const { return jetons.size(); }

        //Récupération d'un jeton à partir de son indice
        const Jeton& getJetons(size_t i) const;

        //Singleton
        static const LotDeJetons& getLotDeJetons();
};

class Privilege {
    //pas d'attribut ni méthode : les 3 privilèges sont identiques
};

std::ostream& operator<< (std::ostream& f, const Privilege& privilege);
QDebug operator<<(QDebug f, const Privilege &privilege);

class LotPrivileges {
    private :
        std::vector<const Privilege*> privileges;
        const size_t max_privileges = 3;

        //Constructeur non accessible par l'utilisateur : singleton
        LotPrivileges();
        ~LotPrivileges();

        //Constructeur non accessible par l'utilisateur : singleton
        LotPrivileges(const LotPrivileges&) = delete;
        LotPrivileges& operator=(const LotPrivileges&) = delete;
    public :
        size_t getNbPrivileges() const { return privileges.size(); }
        const Privilege& getPrivilege(size_t i) const;  

        //Singleton
        static const LotPrivileges& getLotPrivileges();      
};

class Sac {
    //Le sac de jetons contient tous les jetons qui ne sont ni dans la main des joueurs ni sur le plateau
    //Au debut de la partie, le plateau est pleins, le sac est donc vide au même titre que la main des joueurs
    private :
        std::vector<const Jeton*> jetons;

        //Constructeur non accessible par l'utilisateur : singleton
        //Constructeur à partir d'un lot de jetons (dans le cas d'une nouvelle partie -> sac plein)
        explicit Sac(const LotDeJetons& lot); //explicit pour éviter les conversions implicites
        //Constructeur sans argument pour initialiser un sac vide (dans le cas d'une partie en cours)
        //par défaut : initialisation du vecteur vide
        Sac() = default;

        //pas de duplication de sac
        Sac(const Sac&) = delete;
        Sac& operator=(const Sac&) = delete;
    public :
        bool estVide() const { return jetons.empty(); }

        size_t getNbJetons() const { return jetons.size(); }
        void ajouterJeton(const Jeton& j);
        const Jeton& piocherJeton();
        const Jeton& piocherJeton(Couleur c);

        //Singleton
        //Avec tous les jetons (debut de partie)
        static Sac& getSac(const LotDeJetons& lot);
        //Sans jetons (restitution de partie)
        static Sac& getSac();
        void afficherSac() const;
};

class Plateau {
    //Le plateau est une matrice de jetons
    private : 
        std::array<std::array<const Jeton*, 5>, 5> jetons;
        std::vector<const Privilege*> privileges;



        //Constructeur non accessible par l'utilisateur : singleton
        //Constructeur à partir d'un lot de privilèges
        explicit Plateau(const LotPrivileges& lotp); //on evite la conversion du lot de privilèges en plateau

        //pas de duplication du plateau
        Plateau(const Plateau&) = delete;
        Plateau& operator=(const Plateau&) = delete;
    public :
        bool estVide() const;
        bool caseVide(unsigned int i, unsigned int j) const;
        bool caseOr(unsigned int i, unsigned int j) const;
        bool contientOr()const;
        bool contientOnlyOr() const;
        size_t getLargeurMatrice() const { return jetons.size(); }
        size_t getNbJetons() const;

        const Jeton& recupererJeton(const size_t i, const size_t j);
        const Privilege& recupererPrivilege();
        bool pivilegeDisponible() const { return !privileges.empty(); }
        const Jeton* getJeton(const size_t i, const size_t j) const { return jetons[i][j]; }
        unsigned int getNbPrivileges() const {return privileges.size(); }

        //Postionnement du jeton en suivant l'ordre du plateau
        void positionerJeton(const Jeton& jeton);
        void poserPrivilege(const Privilege& privilege);
        //Postionnement du jeton en imposant une positite (restitution de partie) (non accessible par l'utilisateur)
        //Sera accessible par la classe qui fera la restitution de partie
        void positionerJeton(const Jeton& jeton, const size_t i, const size_t j); //TODO
        //Remplissage du plateau à partir du sac (on vide le sac)
        void remplirPlateau(Sac& sac);



        //Singleton
        //Lot de privilèges (debut de partie)
        static Plateau& getPlateau(const LotPrivileges& lotp);
};

std::ostream& operator<< (std::ostream& f, const Plateau& plateau);
QDebug operator<<(QDebug f, const Plateau &plateau);

#endif


/*
Pour récupération d'une partie :

Fin de partie :

LotDeJetons + LotPrivileges (ne pas sauvegarder car seront les mêmes)
Savergarder le nombre de privilege sur le plateau + chaque joueur
Sauvegarder le vecteur de jeton du sac
Sauvegarder la matrice du plateau : indice -> couleur/nullptr

Pour restitution d'une partie :
Creation normale des Lots
Creation du sac et du plateau sans arguments 
Remplissage du sac en prenant les jetons dans lot de jetons avec getter par couleur
Remplissage du plateau en prenant les jetons dans lot de jetons avec getter par couleur
Remplissage du plateau en prenant les privilèges dans lot de privilèges avec getter par indice
*/

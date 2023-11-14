#ifndef JETONS_H
#define JETONS_H 

#include <iostream>
#include <random>

//Gestion des jetons et des privileges pour splendor duel

//Gestion des exceptions liées aux jetons
class JetonException
{
public:
    JetonException(const std::string& i) :info(i) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};

//Gestion des exceptions liées aux privilèges
class PrivilegeException
{
public:
    PrivilegeException(const std::string& i) :info(i) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};

//Enum pour les couleurs : initialiser, to string, affichage.
enum class CouleurJeton { RUBIS, SAPHIR, EMERAUDE, ONYX, DIAMANT, OR, PERLE };
std::string toStringCouleur(CouleurJeton c);
std::ostream& operator<<(std::ostream& f, CouleurJeton c);
extern std::initializer_list<CouleurJeton> CouleursJeton;

//Classe Jetons
class Jeton {
    private :
        const CouleurJeton couleur;
    public :
        Jeton(CouleurJeton c) : couleur(c) {}
        CouleurJeton getCouleur() const { return couleur; }
};
std::ostream& operator<< (std::ostream& f, const Jeton& jeton);

class LotDeJetons {
    private :
        std::vector<const Jeton*> jetons;
        //max de chaque jetons
        const size_t max_or = 3;
        const size_t max_perle = 2;

        const size_t max_rubis = 4;
        const size_t max_onyx = 4;
        const size_t max_saphir = 4;
        const size_t max_dimant = 4;
        const size_t max_emeraude = 4;

        //Constructeur non accessible par l'utilisateur : singleton
        LotDeJetons();
        ~LotDeJetons();

        //Récupération d'un jeton à partir de sa couleur (restitution de partie) (non accessible par l'utilisateur)
        //Sera accessible par la classe qui fera la restitution de partie
        const Jeton& getJeton(CouleurJeton c) const;

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

        //Singleton
        //Avec tous les jetons (debut de partie)
        static Sac& getSac(const LotDeJetons& lot);
        //Sans jetons (restitution de partie)
        static Sac& getSac();
};

class Plateau {
    //Le plateau est une matrice de jetons
    private : 
        std::array<std::array<const Jeton*, 5>, 5> jetons;
        std::vector<const Privilege*> privileges;

        //Postionnement du jeton en imposant une positite (restitution de partie) (non accessible par l'utilisateur)
        //Sera accessible par la classe qui fera la restitution de partie
        void positionerJeton(const Jeton& jeton, const size_t i, const size_t j); //TODO

        //Constructeur non accessible par l'utilisateur : singleton
        //Constructeur à partir d'un sac et d'un lot de privilèges (dans le cas d'une nouvelle partie)
        Plateau(Sac& sac, const LotPrivileges& lotp);
        //Constructeur sans argument pour initialiser un plateau vide (restitution partie en cours)
        Plateau();

        //pas de duplication du plateau
        Plateau(const Plateau&) = delete;
        Plateau& operator=(const Plateau&) = delete;
    public :
        bool estVide() const;
        size_t getTaille() const { return jetons.size(); }

        const Jeton& recupererJeton(const size_t i, const size_t j);
        const Privilege& recupererPrivilege();
        bool pivilegeDisponible() const { return !privileges.empty(); }
        const Jeton* getJeton(const size_t i, const size_t j) { return jetons[i][j]; }

        //Postionnement du jeton en suivant l'ordre du plateau
        void positionerJeton(const Jeton& jeton);
        void poserPrivilege(const Privilege& privilege);

        //Remplissage du plateau à partir du sac (on vide le sac)
        void remplirPlateau(Sac& sac);

        //Singleton
        //Avec sac et lot de privilèges (debut de partie)
        static Plateau& getPlateau(Sac& sac, const LotPrivileges& lotp);
        //Sans sac et lot de privilèges (restitution de partie)
        static Plateau& getPlateau();
};

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
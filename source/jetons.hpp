#ifndef JETONS_H
#define JETONS_H

#include <iostream>
#include <vector>
#include <string>

//Gestion des jetons splendor duel

/* Il faudra implémenter la classe jetons, ansi que Lot de Jetons qui contiendra tous les jetons.
Il faudra également définir le plateau de Jeu qui est une matrice de jetons.
Les privilèges apparaitront également sur le plateau. Il faudra aussi définir la classe Lot de Privilege.
Les jetons peuvent se situer à trois endroits : dans le sac, sur le plateau ou dans la main d'un joueur.
Les privilèges, à deux endroits : sur le plateau ou dans la main d'un joueur.
La classe joueur implémenter dans le fichier joueur agira comme controleur pour les jetons et les privilèges.
*/

//Gestion des exceptions liées aux jetons
class JetonException
{
public:
    JetonException(const std::string& i) :info(i) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};

//Enum pour les couleurs : initialiser, to string, affichage.
enum class CouleurJeton { RUBIS, SAPHIR, ÉMERAUDE, ONYX, DIAMANT, OR, PERLE };
std::string toString(CouleurJeton c);
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
        //max jetons
        const size_t max_jetons = 25;
        //max de chaque jetons
        const size_t max_or = 3;
        const size_t max_perle = 2;

        const size_t max_rubis = 4;
        const size_t max_onyx = 4;
        const size_t max_saphir = 4;
        const size_t max_dimant = 4;
        const size_t max_emeraude = 4;
    public:
        size_t getNbJetons() const { return jetons.size(); }
        const Jeton& getJetons(size_t i) const;
        LotDeJetons();
        ~LotDeJetons();

        //pas de duplication du lot de jetons
        LotDeJetons(const LotDeJetons&) = delete;
        LotDeJetons& operator=(const LotDeJetons&) = delete;
};

class Privilege {
    //pas d'attribut ni méthode : les 3 privilèges sont identiques
};
std::ostream& operator<< (std::ostream& f, const Privilege& privilege);

class LotPrivileges {
    private :
        std::vector<const Privilege*> privileges;
        const size_t max_privileges = 3;
    public :
        size_t getNbPrivileges() const { return privileges.size(); }
        const Privilege& getPrivilege(size_t i) const;
        LotPrivileges();
        ~LotPrivileges();

        //pas de duplication du lot
        LotPrivileges(const LotPrivileges&) = delete;
        LotPrivileges& operator=(const LotPrivileges&) = delete;
};

class Sac {
    //Le sac de jetons contient tous les jetons qui ne sont ni dans la main des joueurs ni sur le plateau
    //Au debut de la partie, le plateau est pleins, le sac est donc vide au même titre que la main des joueurs
    private :
        std::vector<const Jeton*> jetons;
    public :
        explicit Sac(const LotDeJetons& lot);
        bool estVide() const { return jetons.empty(); }
        size_t getNbJetons() const { return jetons.size(); }
        void ajouterJeton(const Jeton& j);
        const Jeton& piocherJeton();

        //pas de duplication de sac
        Sac(const Sac&) = delete;
        Sac& operator=(const Sac&) = delete;
};

class Plateau {
    //Le plateau est une matrice de jetons
    private :
        //la taille de la matrice est fixe pour le moment
        //une augmentation de sa taille nécéssiterai la modification de l'ordre de positionnement des jetons 
        std::array<std::array<const Jeton*, 5>, 5> jetons;
        std::vector<const Privilege*> privileges;
        //ordre de positionnement des jetons sur le plateau
        std::array<std::tuple<size_t, size_t>, 25> liste_pos = {
            std::make_tuple(2,2), std::make_tuple(1,2), std::make_tuple(1,3), std::make_tuple(2,3), std::make_tuple(3,3), std::make_tuple(3,2), std::make_tuple(3,1), std::make_tuple(2,1), std::make_tuple(1,1), std::make_tuple(0,1), std::make_tuple(0,2), std::make_tuple(0,3), std::make_tuple(0,4), std::make_tuple(1,4), std::make_tuple(2,4), std::make_tuple(3,4), std::make_tuple(4,4), std::make_tuple(4,3), std::make_tuple(4,2), std::make_tuple(4,1), std::make_tuple(4,0), std::make_tuple(3,0), std::make_tuple(2,0), std::make_tuple(1,0), std::make_tuple(0,0)
            };
    public :
        const Jeton& recupererJeton(const size_t i, const size_t j);
        const Privilege& recupererPrivilege();
        void positionerJeton(const Jeton& jeton);
        void poserPrivilege(const Privilege& privilege);
        void remplirPlateau(Sac& sac);
        bool estVide() const;
        Plateau(Sac& sac, const LotPrivileges& lotp);

        //pas de duplication du plateau
        Plateau(const Plateau&) = delete;
        Plateau& operator=(const Plateau&) = delete;
};

#endif

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
class Jetons {
    private :
        CouleurJeton couleur;
    public :
        Jetons(CouleurJeton c) : couleur(c) {}
        CouleurJeton getCouleur() const { return couleur; }
};

std::ostream& operator<< (std::ostream& f, const Jetons& jeton);

#endif

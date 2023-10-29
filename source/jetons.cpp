#include "jetons.hpp"
#include <random>

//------------------------------------------------- Gestion de la couleur des jetons
std::initializer_list<CouleurJeton> CouleursJeton = { CouleurJeton::RUBIS, CouleurJeton::SAPHIR, CouleurJeton::ÉMERAUDE, CouleurJeton::ONYX, CouleurJeton::DIAMANT, CouleurJeton::OR, CouleurJeton::PERLE };

std::string toString(CouleurJeton c)
{
    switch (c)
    {
    case CouleurJeton::RUBIS: return "Rubis";
    case CouleurJeton::SAPHIR: return "Saphir";
    case CouleurJeton::ONYX: return "Onyx";
    case CouleurJeton::ÉMERAUDE: return "Emeraude";
    case CouleurJeton::DIAMANT: return "Diamant";
    case CouleurJeton::OR: return "Or";
    case CouleurJeton::PERLE: return "Perle";
    default: throw JetonException("Couleur inconnue");
    }
}

std::ostream& operator<<(std::ostream& f, CouleurJeton c)
{
    return f << toString(c);
}

//------------------------------------------------- Classe Jetons

std::ostream& operator<< (std::ostream& f, const Jeton& jeton) {
    f << jeton.getCouleur();
    return f;
}

//------------------------------------------------- Classe LotDeJetons

const Jeton& LotDeJetons::getJetons(size_t i) const
{
    if (i >= 25)
        throw JetonException("Indice de jeton incorrect");
    return *jetons[i];
}

LotDeJetons::LotDeJetons()
{
    //Pour le moment : création de 25 jetons directement dans le constructeur
    //3 OR
    for (size_t i = 0; i < 3; i++)
    {
        jetons[i] = new Jeton(CouleurJeton::OR);
    }
    //2 Perles
    for (size_t i = 3; i < 5; i++)
    {
        jetons[i] = new Jeton(CouleurJeton::PERLE);
    }
    //4 jetons de chacune des 5 couleurs
    for (size_t i = 5; i<9; i++) {
        jetons[i] = new Jeton(CouleurJeton::RUBIS);
    }
    for (size_t i = 9; i<13; i++) {
        jetons[i] = new Jeton(CouleurJeton::SAPHIR);
    }
    for (size_t i = 13; i<17; i++) {
        jetons[i] = new Jeton(CouleurJeton::ÉMERAUDE);
    }
    for (size_t i = 17; i<21; i++) {
        jetons[i] = new Jeton(CouleurJeton::ONYX);
    }
    for (size_t i = 21; i<25; i++) {
        jetons[i] = new Jeton(CouleurJeton::DIAMANT);
    }
}

LotDeJetons::~LotDeJetons()
{
    for (size_t i = 0; i < getNbJetons(); i++)
    {
        delete jetons[i];
    }
}

//------------------------------------------------- Classe LotPrivilege

const Privilege& LotPrivilege::getPrivilege(size_t i) const
{
    if (i >= 3)
        throw JetonException("Indice de privilège incorrect");
    return *privileges[i];
}

LotPrivilege::LotPrivilege()
{
    for (size_t i = 0; i < 3; i++)
    {
        privileges[i] = new Privilege();
    }
}

LotPrivilege::~LotPrivilege()
{
    for (size_t i = 0; i < getNbPrivileges(); i++)
    {
        delete privileges[i];
    }
}

//------------------------------------------------- Classe Sac

Sac::Sac(const LotDeJetons& lot) {
    for (size_t i = 0; i < lot.getNbJetons(); i++)
    {
        jetons.push_back(&lot.getJetons(i));
    }
}

void Sac::ajouterJeton(const Jeton* j) {
    jetons.push_back(j);
}

const Jeton& Sac::piocherJeton() {
    if (estVide())
        throw JetonException("Pas de jeton à piocher dans le sac");

    //génération d'un indice aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, jetons.size()-1);
    size_t i = distrib(gen);

    //recuperation du jeton
    const Jeton* j = jetons[i];
    jetons.erase(jetons.begin() + i);

    return *j;
}



//------------------------------------------------- Classe Plateau

Plateau::Plateau(const LotPrivilege& lot) {
    //initialisation du plateau vide
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            jetons[i][j] = nullptr;
        }
    }

    //initialisation des privilèges
    for (size_t i = 0; i < lot.getNbPrivileges(); i++)
    {
        privileges.push_back(&lot.getPrivilege(i));
    }
}

const Jeton& Plateau::recupererJeton(size_t i, size_t j)
{
    if (i >= 5 || j >= 5)
        throw JetonException("Indice de jeton incorrect");
    if (jetons[i][j] == nullptr)
        throw JetonException("Pas de jeton à cet emplacement");
    
    const Jeton* jeton = jetons[i][j];
    jetons[i][j] = nullptr;
    return *jeton;
}

const Privilege& Plateau::recupererPrivilege() {
    if (privileges.empty())
        throw JetonException("Pas de privilège à récupérer");
    
    //on recup le dernier privilège
    const Privilege* privilege = privileges.back();
    privileges.pop_back();
    return *privilege;
}

void Plateau::poserPrivilege(const Privilege* privilege) {
    privileges.push_back(privilege);
}

void Plateau::positionerJeton(const Jeton* jeton) {
    //on cherche la première case vide
    int pos=0;
    int i = std::get<0>(liste_pos[pos]);
    int j = std::get<1>(liste_pos[pos]);
    while (jetons[i][j] != nullptr && pos<liste_pos.size()-1) {
        pos++;
        i = std::get<0>(liste_pos[pos]);
        j = std::get<1>(liste_pos[pos]);
    };

    //si on est arrivés au bout de la liste et que aucune case n'est vide
    if (jetons[i][j] != nullptr) {
        throw JetonException("Le plateau est déjà plein");
    } else {
        jetons[i][j] = jeton;
    }
}
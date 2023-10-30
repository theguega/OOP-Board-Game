#include "jetons.hpp"
#include <random>

//------------------------------------------------- Gestion de la couleur des jetons
std::initializer_list<CouleurJeton> CouleursJeton = { 
    CouleurJeton::RUBIS, CouleurJeton::SAPHIR, CouleurJeton::ÉMERAUDE, CouleurJeton::ONYX, CouleurJeton::DIAMANT, CouleurJeton::OR, CouleurJeton::PERLE 
};

std::string toString(CouleurJeton c) {
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

std::ostream& operator<<(std::ostream& f, CouleurJeton c) {
    return f << toString(c);
}

//------------------------------------------------- Classe Jetons

std::ostream& operator<< (std::ostream& f, const Jeton& jeton) {
    f << jeton.getCouleur();
    return f;
}

//------------------------------------------------- Classe LotDeJetons

const Jeton& LotDeJetons::getJetons(size_t i) const {   
    if (i >= jetons.size())
        throw JetonException("Indice de jeton incorrect");
    return *jetons[i];
}

LotDeJetons::LotDeJetons() { 
    if (max_jetons != max_or + max_perle + max_dimant + max_onyx + max_rubis + max_saphir + max_emeraude) {
        throw JetonException("Attention le nombre de jetons ne correponds pas au nombre de jetons de chaque type");
    }

    //création de tous les jetons
    for (int i = 0; i < max_or; i++)
        jetons.push_back(new Jeton(CouleurJeton::OR));
    for (int i = 0; i < max_perle; i++)
        jetons.push_back(new Jeton(CouleurJeton::PERLE));
    for (int i = 0; i < max_dimant; i++)
        jetons.push_back(new Jeton(CouleurJeton::DIAMANT));
    for (int i = 0; i < max_onyx; i++)
        jetons.push_back(new Jeton(CouleurJeton::ONYX));
    for (int i = 0; i < max_rubis; i++)
        jetons.push_back(new Jeton(CouleurJeton::RUBIS));
    for (int i = 0; i < max_saphir; i++)
        jetons.push_back(new Jeton(CouleurJeton::SAPHIR));
    for (int i = 0; i < max_emeraude; i++)
        jetons.push_back(new Jeton(CouleurJeton::ÉMERAUDE));

    if (jetons.size() != max_jetons)
        throw JetonException("Attention le nombre de jetons ne correponds pas au nombre de jetons de chaque type");
}

LotDeJetons::~LotDeJetons() {
    for (size_t i = 0; i < getNbJetons(); i++)
        delete jetons[i];
}

//------------------------------------------------- Classe LotPrivilege

std::ostream& operator<< (std::ostream& f, const Privilege& privilege) {
    f << "Privilège" << std::endl;
    return f;
}

const Privilege& LotPrivileges::getPrivilege(size_t i) const {
    if (i >= privileges.size())
        throw JetonException("Indice de privilège incorrect");
    return *privileges[i];
}

LotPrivileges::LotPrivileges() {
    for (size_t i = 0; i < max_privileges; i++)
        privileges.push_back(new Privilege());
}

LotPrivileges::~LotPrivileges() {
    for (size_t i = 0; i < getNbPrivileges(); i++)
        delete privileges[i];
}

//------------------------------------------------- Classe Sac

Sac::Sac(const LotDeJetons& lot) {
    for (size_t i = 0; i < lot.getNbJetons(); i++)
        jetons.push_back(&lot.getJetons(i));
}

void Sac::ajouterJeton(const Jeton& j) {
    jetons.push_back(&j);
}

const Jeton& Sac::piocherJeton() {
    if (estVide())
        throw JetonException("Le sac est vide");

    //génération d'un indice aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, static_cast<int>(jetons.size()) - 1);
    size_t i = distrib(gen);

    //recuperation du jeton
    const Jeton& j = *jetons[i];
    jetons.erase(jetons.begin() + i);

    return j;
}



//------------------------------------------------- Classe Plateau

Plateau::Plateau(Sac& sac, const LotPrivileges& lotp) {
    //initialisation des privilèges
    for (size_t i = 0; i < lotp.getNbPrivileges(); i++)
        poserPrivilege(lotp.getPrivilege(i));

    //initialisation du plateau vide
    for (size_t i = 0; i < 5; i++)
        for (size_t j = 0; j < 5; j++)
            jetons[i][j] = nullptr;

    //remplissage du plateau
    remplirPlateau(sac);
}

const Jeton& Plateau::recupererJeton(size_t i, size_t j) {
    if (i >= 5 || j >= 5)
        throw JetonException("Indice de jeton incorrect");
    if (jetons[i][j] == nullptr)
        throw JetonException("Pas de jeton à cet emplacement");
    
    //recuperation du jeton
    const Jeton& jeton = *jetons[i][j];
    jetons[i][j] = nullptr;
    return jeton;
}

const Privilege& Plateau::recupererPrivilege() {
    if (privileges.empty())
        throw JetonException("Pas de privilège à récupérer");
    
    //on recup le dernier privilège
    const Privilege& privilege = *privileges.back();
    privileges.pop_back();
    return privilege;
}

void Plateau::poserPrivilege(const Privilege& privilege) {
    privileges.push_back(&privilege);
}

void Plateau::positionerJeton(const Jeton& jeton) {
    //on cherche la première case vide
    int pos=0;
    size_t i = std::get<0>(liste_pos[pos]);
    size_t j = std::get<1>(liste_pos[pos]);
    while (jetons[i][j] != nullptr && pos<liste_pos.size()-1) {
        pos++;
        i = std::get<0>(liste_pos[pos]);
        j = std::get<1>(liste_pos[pos]);
    };

    //si on est arrivés au bout de la liste et que aucune case n'est vide
    if (jetons[i][j] != nullptr) {
        throw JetonException("Le plateau est déjà plein");
    } else {
        jetons[i][j] = &jeton;
    }
}

void Plateau::remplirPlateau(Sac& sac) {
    if(sac.estVide())
        throw JetonException("Le sac est vide");
    while(!sac.estVide()) {
        positionerJeton(sac.piocherJeton());
    }
}
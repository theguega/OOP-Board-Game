#include "jetons.hpp"

/*
   __         _ 
   \ \   ___ | |_   ___   _ __   ___ 
    \ \ / _ \| __| / _ \ | '_ \ / __|
 /\_/ /|  __/| |_ | (_) || | | |\__ \
 \___/  \___| \__| \___/ |_| |_||___/
*/

//------------------------------------------------- Gestion de la couleur des jetons
std::initializer_list<Couleur> Couleurs = { 
    Couleur::BLANC, Couleur::BLEU, Couleur::VERT, Couleur::ROUGE, Couleur::NOIR, Couleur::PERLE, Couleur::OR, Couleur::INDT
};

std::string toStringCouleur(Couleur c) {
    switch (c)
    {
    case Couleur::BLANC: return "Blanc";
    case Couleur::BLEU: return "Bleu ";
    case Couleur::VERT: return "Vert ";
    case Couleur::ROUGE: return "Rouge";
    case Couleur::NOIR: return "Noir ";
    case Couleur::PERLE: return "Perle";
    case Couleur::OR: return "Or   ";
    case Couleur::INDT: return "Indt ";
    default: throw JetonException("Couleur inconnue");
    }
}

std::ostream& operator<<(std::ostream& f, Couleur c) {
    return f << toStringCouleur(c);
}

std::map<std::string, Couleur> stringToCouleurMap = {
        {"blanc", Couleur::BLANC},
        {"bleu", Couleur::BLEU},
        {"vert", Couleur::VERT},
        {"noir", Couleur::NOIR},
        {"rouge", Couleur::ROUGE},
        {"perle", Couleur::PERLE},
        {"or", Couleur::OR},
        {"indt", Couleur::INDT}
};

Couleur StringToCouleur(const std::string& couleurStr) {
    auto tmp = stringToCouleurMap.find(couleurStr);
    if (tmp != stringToCouleurMap.end()) {
        return tmp->second;
    }
    else {
        return Couleur::INDT;
    }
}

//------------------------------------------------- Classe Jetons

std::ostream& operator<< (std::ostream& f, const Jeton& jeton) {
    f << jeton.getCouleur();
    return f;
}
std::ostream& operator<< (std::ostream& f, const Jeton* jeton) {
    f << *jeton;
    return f;
}

//------------------------------------------------- Classe LotDeJetons

//recuperation d'un jeton à partir de son indice
const Jeton& LotDeJetons::getJetons(size_t i) const {   
    if (i >= jetons.size())
        throw JetonException("Indice de jeton incorrect");
    return *jetons[i];
}

//recuperation d'un jeton à partir de sa couleur (non accessible par l'utilisateur)
const Jeton& LotDeJetons::getJeton(Couleur c) const {
    for (size_t i = 0; i < jetons.size(); i++)
        if (jetons[i]->getCouleur() == c)
            return *jetons[i];
    throw JetonException("Couleur de jeton incorrecte");
}

LotDeJetons::LotDeJetons() { 
    //création de tous les jetons
    for (int i = 0; i < max_or; i++)
        jetons.push_back(new Jeton(Couleur::OR));
    for (int i = 0; i < max_perle; i++)
        jetons.push_back(new Jeton(Couleur::PERLE));
    for (int i = 0; i < max_blanc; i++)
        jetons.push_back(new Jeton(Couleur::BLANC));
    for (int i = 0; i < max_noir; i++)
        jetons.push_back(new Jeton(Couleur::NOIR));
    for (int i = 0; i < max_rouge; i++)
        jetons.push_back(new Jeton(Couleur::ROUGE));
    for (int i = 0; i < max_bleu; i++)
        jetons.push_back(new Jeton(Couleur::BLEU));
    for (int i = 0; i < max_vert; i++)
        jetons.push_back(new Jeton(Couleur::VERT));
}

LotDeJetons::~LotDeJetons() {
    for (size_t i = 0; i < getNbJetons(); i++)
        delete jetons[i];
}

//Singleton
const LotDeJetons& LotDeJetons::getLotDeJetons() {
    static const LotDeJetons instance;
    return instance;
}

//------------------------------------------------- Classe LotPrivilege

std::ostream& operator<< (std::ostream& f, const Privilege& privilege) {
    f << "Privilege" << std::endl;
    return f;
}

const Privilege& LotPrivileges::getPrivilege(size_t i) const {
    if (i >= privileges.size())
        throw JetonException("Indice de privilege incorrect");
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

//Singleton
const LotPrivileges& LotPrivileges::getLotPrivileges() {
    static const LotPrivileges instance;
    return instance;
}

//------------------------------------------------- Classe Sac


const Jeton& Sac::piocherJeton(Couleur c) {
    for (size_t i = 0; i < jetons.size(); i++)
        if (jetons[i]->getCouleur() == c) {
            const Jeton* jt = jetons[i];
            jetons.erase(jetons.begin()+i);
            return *jt;
        }
    throw JetonException("Couleur de jeton incorrecte");
}

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

//Singleton
//Avec jetons
Sac& Sac::getSac(const LotDeJetons& lot) {
    static Sac instance(lot);
    return instance;
}
//Sans jetons (pour restitution de partie)
Sac& Sac::getSac() {
    static Sac instance;
    return instance;
}


//------------------------------------------------- Classe Plateau

void Plateau::positionerJeton(const Jeton& jeton, const size_t i, const size_t j){
    jetons[i][j] = &jeton;
}

Plateau::Plateau(const LotPrivileges& lotp) {
    //initialisation des privilèges
    for (size_t i = 0; i < lotp.getNbPrivileges(); i++)
        poserPrivilege(lotp.getPrivilege(i));

    //initialisation du plateau vide
    for (size_t i = 0; i < jetons.size(); i++)
        for (size_t j = 0; j < jetons.size(); j++)
            jetons[i][j] = nullptr;
}

const Jeton& Plateau::recupererJeton(const size_t i, const size_t j) {
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
    size_t centre = jetons.size() / 2;
    size_t i = centre, j = centre;
    size_t h = 1, d = 1, b = 2, g = 2;
    size_t direction = 0, avancement = 0;
    while (jetons[i][j] != nullptr && i <= jetons.size()-1 && j <= jetons.size()-1) {
        switch (direction) {
            case 0:  // Vers le haut
                i--;
                avancement++;
                if (avancement == h){
                    avancement = 0;
                    direction = 1;
                    h += 2;
                }
                break;
            case 1:  // Vers la droite
                j++;
                avancement++;
                if (avancement == d){
                    avancement = 0;
                    direction = 2;
                    d += 2;
                }
                break;
            case 2:  // Vers le bas
                i++;
                avancement++;
                if (avancement == b){
                    avancement = 0;
                    direction = 3;
                    b += 2;
                }
                break;
            case 3:  // Vers la gauche
                j--;
                avancement++;
                if (avancement == g){
                    avancement = 0;
                    direction = 0;
                    g += 2;
                }
                break;
        }
    }

    //si on est arrivés au bout de la liste et que aucune case n'etait vide
    if (i <= jetons.size()-1 && j <= jetons.size()-1) {
        jetons[i][j] = &jeton;
    } else {
        throw JetonException("Le plateau est déjà plein");
    }
}

void Plateau::remplirPlateau(Sac& sac) {
    if(sac.estVide())
        throw JetonException("Le sac est vide");
    while(!sac.estVide()) {
        positionerJeton(sac.piocherJeton());
    }
}

bool Plateau::estVide() const {
    for (size_t i = 0; i < 5; i++)
        for (size_t j = 0; j < 5; j++)
            if (jetons[i][j] != nullptr)
                return false;
    return true;
}

//Singleton
//Avec sac et lot de privilèges (debut de partie)
Plateau& Plateau::getPlateau(const LotPrivileges& lotp) {
    static Plateau instance(lotp);
    return instance;
}

std::ostream& operator<< (std::ostream& f, const Plateau& plateau) {
    //On affiche une matrice avec dans chaque case la lettre correpondant au jetons
    f<<"-------------------------------"<<std::endl;
    for (size_t i = 0; i < plateau.getTaille(); i++) {
        f << "|";
        for (size_t j = 0; j < plateau.getTaille(); j++) {
            if (plateau.getJeton(i,j) == nullptr)
                f << " ";
            else
                f << plateau.getJeton(i, j);
            f << "|";
        };
        f << "\n" << "-------------------------------" << std::endl;
    }
    return f;
}
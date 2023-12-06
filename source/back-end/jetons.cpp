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

/*
std::string toStringCouleur(Couleur c) {
    switch (c)
    {
    case Couleur::BLANC: return "Blanc";
    case Couleur::BLEU: return "Bleu";
    case Couleur::VERT: return "Vert";
    case Couleur::ROUGE: return "Rouge";
    case Couleur::NOIR: return "Noir";
    case Couleur::PERLE: return "Perle";
    case Couleur::OR: return "Or";
    case Couleur::INDT: return "Indt";
    default: throw SplendorException("Couleur inconnue");
    }
}*/

//🔵🟢🔴🟡🟣🖤🤍

std::string toEmojiCouleur(Couleur c) {
    switch (c)
    {
    case Couleur::BLANC: return "\033[1;37m O \033[0m"; // Blanc
    case Couleur::BLEU: return "\033[1;34m O \033[0m";  // Bleu
    case Couleur::VERT: return "\033[1;32m O \033[0m";  // Vert
    case Couleur::ROUGE: return "\033[1;31m O \033[0m"; // Rouge
    case Couleur::NOIR: return "\033[1;90m O \033[0m";  // Noir
    case Couleur::PERLE: return "\033[1;35m O \033[0m"; // Perle (rose)
    case Couleur::OR: return "\033[1;33m O \033[0m";    // Or (jaune)
    case Couleur::INDT: return "Indt";
    default: throw SplendorException("Couleur inconnue");
    }
}

std::string toStringCouleur(Couleur c) {
    switch (c)
    {
    case Couleur::BLANC: return "Blanc"; // Blanc
    case Couleur::BLEU: return "Bleu ";  // Bleu
    case Couleur::VERT: return "Vert ";  // Vert
    case Couleur::ROUGE: return "Rouge"; // Rouge
    case Couleur::NOIR: return "Noir ";  // Noir
    case Couleur::PERLE: return "Perle"; // Perle (rose)
    case Couleur::OR: return "Or   ";    // Or (jaune)
    case Couleur::INDT: return "Indt ";
    default: throw SplendorException("Couleur inconnue");
    }
}

std::ostream& operator<<(std::ostream& f, Couleur c) {
    return f << toEmojiCouleur(c);
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
        throw SplendorException("Couleur de carte inconnu, attention à la casse\n");
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

//recuperation d'un jeton a partir de son indice
const Jeton& LotDeJetons::getJetons(size_t i) const {   
    if (i >= jetons.size())
        throw SplendorException("Indice de jeton incorrect");
    return *jetons[i];
}

LotDeJetons::LotDeJetons() { 
    //creation de tous les jetons
    for (size_t i = 0; i < max_or; i++)
        jetons.push_back(new Jeton(Couleur::OR));
    for (size_t i = 0; i < max_perle; i++)
        jetons.push_back(new Jeton(Couleur::PERLE));
    for (size_t i = 0; i < max_blanc; i++)
        jetons.push_back(new Jeton(Couleur::BLANC));
    for (size_t i = 0; i < max_noir; i++)
        jetons.push_back(new Jeton(Couleur::NOIR));
    for (size_t i = 0; i < max_rouge; i++)
        jetons.push_back(new Jeton(Couleur::ROUGE));
    for (size_t i = 0; i < max_bleu; i++)
        jetons.push_back(new Jeton(Couleur::BLEU));
    for (size_t i = 0; i < max_vert; i++)
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

std::ostream& operator<< (std::ostream& f,[[maybe_unused]]const Privilege& privilege) {
    f << "Privilege" << std::endl;
    return f;
}

const Privilege& LotPrivileges::getPrivilege(size_t i) const {
    if (i >= privileges.size())
        throw SplendorException("Indice de privilege incorrect");
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
    throw SplendorException("Couleur de jeton incorrecte");
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
        throw SplendorException("Le sac est vide, vous ne pouvez pas recuperer de Jetons");

    //generation d'un indice aleatoire
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
    //initialisation des privileges
    for (size_t i = 0; i < lotp.getNbPrivileges(); i++)
        poserPrivilege(lotp.getPrivilege(i));

    //initialisation du plateau vide
    for (size_t i = 0; i < jetons.size(); i++)
        for (size_t j = 0; j < jetons.size(); j++)
            jetons[i][j] = nullptr;
}

const Jeton& Plateau::recupererJeton(const size_t i, const size_t j) {
    if (i >= 5 || j >= 5)
        throw SplendorException("Indice de jeton incorrect");
    if (jetons[i][j] == nullptr)
        throw SplendorException("Pas de jeton a cet emplacement");
    
    //recuperation du jeton
    const Jeton& jeton = *jetons[i][j];
    jetons[i][j] = nullptr;
    return jeton;
}

const Privilege& Plateau::recupererPrivilege() {
    if (privileges.empty())
        throw SplendorException("Pas de privilege a recuperer");
    
    //on recup le dernier privilege
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

    //si on est arrives au bout de la liste et que aucune case n'etait vide
    if (i <= jetons.size()-1 && j <= jetons.size()-1) {
        jetons[i][j] = &jeton;
    } else {
        throw SplendorException("Le plateau est deja plein");
    }
}

void Plateau::remplirPlateau(Sac& sac) {
    if(sac.estVide())
        throw SplendorException("Le sac est vide");
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

bool Plateau::caseVide(unsigned int i, unsigned int j) const{
    if (jetons[i][j] == nullptr)
        return true;
    return false;
}

bool Plateau::caseOr(unsigned int i, unsigned int j) const{
    if(jetons[i][j]->getCouleur() == Couleur::OR)
        return true;
    return false;
};

bool Plateau::contientOr() const {
    for(int i =0; i <5; i++){
        for(int j = 0; j<5; j++){
            if(!caseVide(i, j) && caseOr(i, j))
                return true;
        }
    }
    return false;
}
//Singleton
//Avec sac et lot de privileges (debut de partie)
Plateau& Plateau::getPlateau(const LotPrivileges& lotp) {
    static Plateau instance(lotp);
    return instance;
}

std::ostream& operator<< (std::ostream& f, const Plateau& plateau) {
    //On affiche une matrice avec dans chaque case la lettre correpondant au jetons
    f<<"---------------------"<<std::endl;
    for (size_t i = 0; i < plateau.getLargeurMatrice(); i++) {
        f << "|";
        for (size_t j = 0; j < plateau.getLargeurMatrice(); j++) {
            if (plateau.getJeton(i,j) == nullptr)
                f << "   ";
            else
                f << plateau.getJeton(i, j);
            f << "|";
        };
        f << "\n" << "---------------------" << std::endl;
    }


    //Sous la matrice, on affiche les privileges :
    for(unsigned int i = 0; i<plateau.getNbPrivileges();i++)
        f << "|\033[1;38;5;208mP\033[0m|";

    f << "\n" << "---------------------" << std::endl;
    return f;
}

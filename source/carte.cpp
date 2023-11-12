#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include "carte.h"
#include "sqlite/sqlite3.h"
using namespace std;

std::initializer_list<CouleurCarte> CouleursCarte = { CouleurCarte::blanc, CouleurCarte::bleu, CouleurCarte::vert, CouleurCarte::noir, CouleurCarte::rouge, CouleurCarte::perle, CouleurCarte::indt };
std::initializer_list<TypeCarte> TypesCarte = { TypeCarte::Niv1, TypeCarte::Niv2, TypeCarte::Niv3, TypeCarte::Noble };
std::initializer_list<Capacite> Capacites = { Capacite::NewTurn, Capacite::TakePrivilege, Capacite::TakeJetonFromBonus, Capacite::TakeJetonToAdv, Capacite::AssociationBonus, Capacite::None };


string toString(CouleurCarte c){
    switch (c){
        case CouleurCarte::blanc : return "blanc";
        case CouleurCarte::bleu: return "bleu";
        case CouleurCarte::vert: return "vert";
        case CouleurCarte::noir: return "noir";
        case CouleurCarte::rouge: return "rouge";
        case CouleurCarte::perle: return "perle";
        case CouleurCarte::indt: return "indt";
        default: throw CarteException("Couleur inconnue");
    }
}
ostream& operator<<(ostream& f, CouleurCarte c){ f << toString(c); return f; }

std::map<std::string, CouleurCarte> stringToCouleurCarteMap = {
        {"blanc", CouleurCarte::blanc},
        {"bleu", CouleurCarte::bleu},
        {"vert", CouleurCarte::vert},
        {"noir", CouleurCarte::noir},
        {"rouge", CouleurCarte::rouge},
        {"perle", CouleurCarte::perle},
        {"indt", CouleurCarte::indt}
};

CouleurCarte StringToCouleurCarte(const std::string& couleurStr){
    auto tmp = stringToCouleurCarteMap.find(couleurStr);
    if (tmp != stringToCouleurCarteMap.end()) {
        return tmp->second;
    }
    else {
        return CouleurCarte::indt;
    }
}


string toString(TypeCarte t){
    switch (t) {
        case TypeCarte::Niv1: return "Niv1";
        case TypeCarte::Niv2: return "Niv2";
        case TypeCarte::Niv3: return "Niv3";
        case TypeCarte::Noble: return "Noble";
        default: throw CarteException("Type inconnue");
    }
}
ostream& operator<<(ostream& f, TypeCarte t) { f << toString(t); return f; }


string toString(Capacite c){
    switch (c) {
        case Capacite::NewTurn: return "NewTurn";
        case Capacite::TakePrivilege: return "TakePrivilege";
        case Capacite::TakeJetonFromBonus: return "TakeJetonFromBonus";
        case Capacite::TakeJetonToAdv: return "TakeJetonToAdv";
        case Capacite::AssociationBonus: return "AssociationBonus";
        case Capacite::None: return "None";
        default: throw CarteException("Capacite inconnue");
    }
}
ostream& operator<<(ostream& f, Capacite c) { f << toString(c); return f; }

std::map<std::string, Capacite> stringToCapaciteMap = {
        {"NewTurn", Capacite::NewTurn},
        {"TakePrivilege", Capacite::TakePrivilege},
        {"TakeJetonFromBonus", Capacite::TakeJetonFromBonus},
        {"TakeJetonToAdv", Capacite::TakeJetonToAdv},
        {"AssociationBonus", Capacite::AssociationBonus},
        {"None", Capacite::None}
};

Capacite StringToCapacite(const std::string& capaciteStr){
    auto tmp = stringToCapaciteMap.find(capaciteStr);
    if (tmp != stringToCapaciteMap.end()) {
        return tmp->second;
    }
    else {
        return Capacite::None;
    }
}


ostream& operator<<(ostream& f, const Prix& p){
	f << "Blanc : " << p.getBlanc() << "    " << "Bleu :  " << p.getBleu() << "\n";
    f << "Vert :  " << p.getVert() << "    " << "Noir :  " << p.getNoir() << "\n";
    f << "Rouge : " << p.getRouge() << "    " << "Perle : " << p.getPerle() << "\n";
    return f;
}


ostream& operator<<(ostream& f, const Bonus& b){
    f << b.getNbBonus() << " " << b.getCouleur();
    return f;
}


Carte::Carte(TypeCarte t, Prix& p, Capacite c1, Capacite c2, Bonus& b, unsigned int nbC, unsigned int nbP) : type(t), prix(p), capacite1(c1), capacite2(c2), bonus(b), nbCouronnes(nbC), nbPtsPrivilege(nbP) {
    if (t == TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprie");
}


Carte::Carte(TypeCarte t, Capacite c, unsigned int nbP) : type(t), prix(0, 0, 0, 0, 0, 0), capacite1(c), capacite2(Capacite::None), bonus(), nbCouronnes(0), nbPtsPrivilege(nbP) {
    if (t != TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprie");
}


ostream& operator<<(ostream& f, const Carte& c){
    f << "-------------------------------------\n";
    f << c.getType() << "        " << "Bonus : " << c.getBonus() << "\n";
    f << "-------------------------------------\n";
    f << "Capacite : " << c.getCapacites() << "\n";
    f << "-------------------------------------\n";
    f << "Prix :\n" << c.getPrix() << "\n";
    f << "-------------------------------------\n";
    f << "Privileges : " << c.getNbPtsPrivilege() << "        " << "Couronnes : " << c.getNbCouronnes() << "\n";
    f << "-------------------------------------\n";
    return f;
}


JeuCarte::JeuCarte(){
    cartes_nv1.fill(nullptr);
    cartes_nv2.fill(nullptr);
    cartes_nv3.fill(nullptr);
    cartes_nobles.fill(nullptr);
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_stmt* stmt2;
    int i = 0;
    int j = 0;
    int k = 0;
    int z = 0;

    int rc = sqlite3_open("data_carte.sqlite", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'carte'", -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        unsigned int p_blanc = sqlite3_column_int(stmt, 2);
        unsigned int p_bleu = sqlite3_column_int(stmt, 3);
        unsigned int p_vert = sqlite3_column_int(stmt, 4);
        unsigned int p_noir = sqlite3_column_int(stmt, 5);
        unsigned int p_rouge = sqlite3_column_int(stmt, 6);
        unsigned int p_perle = sqlite3_column_int(stmt, 7);
        string capacite1 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        string capacite2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
        string couleur_bonus = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
        unsigned int bonus = sqlite3_column_int(stmt, 11);
        unsigned int nb_couronnes = sqlite3_column_int(stmt, 12);
        unsigned int nb_pts_privileges = sqlite3_column_int(stmt, 13);

        Prix p(p_blanc, p_bleu, p_vert, p_noir, p_rouge, p_perle);
        Bonus b(StringToCouleurCarte(couleur_bonus), bonus);
        if (type == "Niv1") {
            cartes_nv1[i] = new Carte(TypeCarte::Niv1, p, StringToCapacite(capacite1), StringToCapacite(capacite2), b, nb_couronnes, nb_pts_privileges);
            i++;
        }
        else if (type == "Niv2") {
            cartes_nv2[j] = new Carte(TypeCarte::Niv2, p, StringToCapacite(capacite1), StringToCapacite(capacite2), b, nb_couronnes, nb_pts_privileges);
            j++;
        }
        else if (type == "Niv3") {
            cartes_nv3[k] = new Carte(TypeCarte::Niv3, p, StringToCapacite(capacite1), StringToCapacite(capacite2), b, nb_couronnes, nb_pts_privileges);
            k++;
        }
        else {
            throw CarteException("Erreur de construction, le type de carte ne convient pas ici");
        }
    }
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'carte_noble'", -1, &stmt2, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt2) == SQLITE_ROW) {
        string capacite = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 1));
        unsigned int nb_pts_privileges = sqlite3_column_int(stmt2, 2);
        cartes_nobles[z] = new Carte(TypeCarte::Noble, StringToCapacite(capacite), nb_pts_privileges);
        z++;
    }
    sqlite3_finalize(stmt);
    sqlite3_finalize(stmt2);
    sqlite3_close(db);
}


JeuCarte::~JeuCarte(){
    for (size_t i = 0; i < getNbCartes_nv1(); ++i) {
		delete cartes_nv1[i];
	}
    for (size_t i = 0; i < getNbCartes_nv2(); ++i) {
        delete cartes_nv2[i];
    }
    for (size_t i = 0; i < getNbCartes_nv3(); ++i) {
        delete cartes_nv3[i];
    }
    for (size_t i = 0; i < getNbCartes_nobles(); ++i) {
        delete cartes_nobles[i];
    }
}


const Carte& JeuCarte::getCarteNiv1(size_t i) const{
    if (i >= 30)
        throw CarteException("Il n'y a que 30 cartes de niveau 1");
    return *cartes_nv1[i];
}


const Carte& JeuCarte::getCarteNiv2(size_t i) const{
    if (i >= 24)
        throw CarteException("Il n'y a que 24 cartes de niveau 2");
    return *cartes_nv2[i];
}


const Carte& JeuCarte::getCarteNiv3(size_t i) const{
    if (i >= 13)
        throw CarteException("Il n'y a que 13 cartes de niveau 3");
    return *cartes_nv3[i];
}


const Carte& JeuCarte::getCarteNoble(size_t i) const{
    if (i >= 4)
        throw CarteException("Il n'y a que 4 cartes nobles");
    return *cartes_nobles[i];
}


Pioche::Pioche(const JeuCarte& j, TypeCarte t) : type_carte(t){
    if (t == TypeCarte::Niv1) {
        nb_cartes = j.getNbCartes_nv1();
        for (size_t i = 0; i < nb_cartes; i++)
            cartes.push_back(&j.getCarteNiv1(i));
    }
    else if (t == TypeCarte::Niv2) {
        nb_cartes = j.getNbCartes_nv2();
        for (size_t i = 0; i < nb_cartes; i++)
            cartes.push_back(&j.getCarteNiv2(i));
    }
    else if (t == TypeCarte::Niv3) {
        nb_cartes = j.getNbCartes_nv3();
        for (size_t i = 0; i < nb_cartes; i++)
            cartes.push_back(&j.getCarteNiv3(i));
    }
    else if (t == TypeCarte::Noble) {
        nb_cartes = j.getNbCartes_nobles();
        for (size_t i = 0; i < nb_cartes; i++)
            cartes.push_back(&j.getCarteNoble(i));
    }
    else {
        throw CarteException("Type de cartes inconnu");
    }
}


Pioche::~Pioche(){
    for (size_t i = 0; i < nb_cartes; i++)
        delete cartes[i];
}


const Carte& Pioche::piocher(){
    if (nb_cartes == 0)
        throw CarteException("Plus de cartes dans cette pioche");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, nb_cartes-1);
    size_t x = distrib(gen);
    const Carte* c = cartes[x];
    for (size_t i = x + 1; i < nb_cartes; i++)
        cartes[i - 1] = cartes[i]; //Deplace toutes les cartes  droite vers la gauche.
    nb_cartes--;
    return *c;
}

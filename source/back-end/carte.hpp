#ifndef CARTES_H
#define CARTES_H

/*
--------------------------------
   _____           _
  / ____|         | |
 | |     __ _ _ __| |_ ___  ___
 | |    / _` | '__| __/ _ \/ __|
 | |___| (_| | |  | ||  __/\__ \
  \_____\__,_|_|   \__\___||___/

--------------------------------
*/

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <map>
#include <random>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

#include "jetons.hpp"
#include "exception.hpp"

using namespace std;




enum class TypeCarte { Niv1, Niv2, Niv3, Noble };
string TypeCartetoString(TypeCarte t);
int TypeCartetoInt(TypeCarte t);
ostream& operator<<(ostream& f, TypeCarte t);
QDebug operator<<(QDebug f, TypeCarte t);
extern std::initializer_list<TypeCarte> TypesCarte;




enum class Capacite { NewTurn, TakePrivilege, TakeJetonFromBonus, TakeJetonToAdv, AssociationBonus, None };
extern std::map<std::string, Capacite> stringToCapaciteMap;
string CapacitetoString(Capacite c);
string CapacitetoShort(Capacite c);
ostream& operator<<(ostream& f, Capacite c);
QDebug operator<<(QDebug f, Capacite c);

Capacite StringToCapacite(const string& capaciteStr);




class Prix {
private:
    unsigned int blanc, bleu, vert, rouge, noir, perle;
public:
    Prix(unsigned int bla, unsigned int ble, unsigned int v, unsigned int r, unsigned int n, unsigned int p) : blanc(bla), bleu(ble), vert(v), rouge(r), noir(n), perle(p) {}

    unsigned int getBlanc() const { return blanc; }
    unsigned int getBleu() const { return bleu; }
    unsigned int getVert() const { return vert; }
    unsigned int getRouge() const { return rouge; }
    unsigned int getNoir() const { return noir; }
    unsigned int getPerle() const { return perle; }
};
ostream& operator<<(ostream& f, const Prix& p);
QDebug operator<<(QDebug f, const Prix &p);




class Bonus {
private:
    Couleur couleur;
    unsigned int nbBonus;
public:
    Bonus(Couleur c = Couleur::INDT, int n = 0) : couleur(c), nbBonus(n) {}

    void setCouleur(Couleur c) { couleur = c; }

    Couleur getCouleur() const { return couleur; }
    unsigned int getNbBonus() const { return nbBonus; }
};

ostream& operator<<(ostream& f, const Bonus& b);

QDebug operator<<(QDebug f, const Bonus &b);




class Carte {
private:
    TypeCarte type;
    Prix prix;
    Capacite capacite1;
    Capacite capacite2;
    Bonus bonus;
    unsigned int nbCouronnes;
    unsigned int nbPtsPrivilege;
    unsigned int id;
public:
    Carte(TypeCarte t, Prix& p, Capacite c1, Capacite c2, Bonus& b, unsigned int nbC, unsigned int nbP, unsigned int id); // constructeur classique
    Carte(TypeCarte t, Capacite c, unsigned int nbP, unsigned int id); // constructeur carte noble
    ~Carte() = default;

    TypeCarte getType() const { return type; }
    const Prix& getPrix() const { return prix; }
    Capacite getCapacite1() const { return capacite1; }
    Capacite getCapacite2() const { return capacite2; }
    const Bonus& getBonus() const { return bonus; }
    unsigned int getId() const { return id; }
    unsigned int getNbCouronnes() const { return nbCouronnes; }
    unsigned int getNbPtsPrivilege() const { return nbPtsPrivilege; }
    string getInfos() const;
};
ostream& operator<<(ostream& f, const Carte& c);
QDebug operator<<(QDebug f, const Carte &c);




class JeuCarte {
private:
    vector<const Carte*> cartes_nv1; 
    vector<const Carte*> cartes_nv2;
    vector<const Carte*> cartes_nv3;
    vector<const Carte*> cartes_nobles;
public:
    JeuCarte();
    ~JeuCarte();

    size_t getNbCartes_nv1() const { return cartes_nv1.size(); }
    size_t getNbCartes_nv2() const { return cartes_nv2.size(); }
    size_t getNbCartes_nv3() const { return cartes_nv3.size(); }
    size_t getNbCartes_nobles() const { return cartes_nobles.size(); }
    const Carte& getCarteNiv1(size_t i) const;
    const Carte& getCarteNiv2(size_t i) const;
    const Carte& getCarteNiv3(size_t i) const;
    const Carte& getCarteNoble(size_t i) const;


    JeuCarte(const JeuCarte& j) = delete;
    JeuCarte& operator=(const JeuCarte& j) = delete;
};




class Pioche{
private:
    TypeCarte type_carte;
    vector<const Carte*> cartes;
public:
    explicit Pioche(const JeuCarte& j, TypeCarte t);
    ~Pioche();

    size_t getNbCartes() const { return cartes.size(); }
    TypeCarte getTypeCarte() const { return type_carte; }
    const vector<const Carte*>& getCartes() const { return cartes; }

    bool estVide() const { return getNbCartes() == 0; }
    const Carte& piocher();
    const Carte& piocher(unsigned int id);

    Pioche(const Pioche& p) = delete;
    Pioche& operator=(const Pioche& p) = delete;
};

#endif

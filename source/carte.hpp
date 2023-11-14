#ifndef CARTES_H
#define CARTES_H

#include <iostream>
#include <string>

#include <array>
#include <vector>
#include <unordered_map>
#include <map>

#include <random>

// ###### Mettez ici le chemin absolu de la librairie sqlite de votre pc, masquez les autres #####
//#include "C:\Users\Beziat\source\repos\Projet_LO21\source\sqlite\sqlite3.h"
#include "sqlite/sqlite3.h" //Pour MAC
//#include "sqlite\sqlite3.h" //Pour Windows
//Samuel M
//Maxime

using namespace std;


class CarteException{
private:
    string info;
public:
    CarteException(const string& i) : info(i) {}
    string getInfo() const { return info; }
};


enum class CouleurCarte {blanc, bleu, vert, noir, rouge, perle, indt}; // ajout de "indetermin�" car certaines carte ont une couleur de Bonus variable

string CouleurCartetoString(CouleurCarte c);
ostream& operator<<(ostream& f, CouleurCarte c);
extern std::initializer_list<CouleurCarte> CouleursCarte;
extern std::map<string, CouleurCarte> stringToCouleurCarteMap;
CouleurCarte StringToCouleurCarte(const string& couleurStr);


enum class TypeCarte { Niv1, Niv2, Niv3, Noble };
string TypeCartetoString(TypeCarte t);
ostream& operator<<(ostream& f, TypeCarte t);
extern std::initializer_list<TypeCarte> TypesCarte;


enum class Capacite { NewTurn, TakePrivilege, TakeJetonFromBonus, TakeJetonToAdv, AssociationBonus, None };
extern std::map<std::string, Capacite> stringToCapaciteMap;
string CapacitetoString(Capacite c);
ostream& operator<<(ostream& f, Capacite c);
Capacite StringToCapacite(const string& capaciteStr);



class Prix { // on l'encapsule dans la classe carte ? ou bien il y'a d'autres elements qui ont un cout ?
private:
    unsigned int blanc, bleu, vert, noir, rouge, perle;
public:
    Prix(unsigned int bla, unsigned int ble, unsigned int v, unsigned int n, unsigned int r, unsigned int p) : blanc(bla), bleu(ble), vert(v), noir(n), rouge(r), perle(p) {}
    unsigned int getBlanc() const { return blanc; }
    unsigned int getBleu() const { return bleu; }
    unsigned int getVert() const { return vert; }
    unsigned int getNoir() const { return noir; }
    unsigned int getRouge() const { return rouge; }
    unsigned int getPerle() const { return perle; }
};
ostream& operator<<(ostream& f, const Prix& p);


class Bonus {
private:
    CouleurCarte couleur;
    unsigned int nbBonus;
public:
    Bonus(CouleurCarte c = CouleurCarte::indt, int n = 0) : couleur(c), nbBonus(n) {}
    void setCouleur(CouleurCarte c) { couleur = c; };
    CouleurCarte getCouleur() const { return couleur; }
    unsigned int getNbBonus() const { return nbBonus; }
};
ostream& operator<<(ostream& f, const Bonus& b);


class Carte {
private:
    // eventuel ajout d'un champ ID, peut �tre util pour les cartes nobles par exemple, savoir qui est qui
    TypeCarte type;
    Prix prix;
    Capacite capacite1;
    Capacite capacite2;
    Bonus bonus;
    unsigned int nbCouronnes;
    unsigned int nbPtsPrivilege;
public:
    Carte(TypeCarte t, Prix& p, Capacite c1, Capacite c2, Bonus& b, unsigned int nbC, unsigned int nbP); // constructeur classique
    Carte(TypeCarte t, Capacite c, unsigned int nbP); // constructeur carte noble
    ~Carte() = default;
    TypeCarte getType() const { return type; }
    Prix getPrix() const { return prix; }
    Capacite getCapacite1() const { return capacite1; }
    Capacite getCapacite2() const { return capacite2; }
    Bonus getBonus() const { return bonus; }
    unsigned int getNbCouronnes() const { return nbCouronnes; }
    unsigned int getNbPtsPrivilege() const { return nbPtsPrivilege; }
};
ostream& operator<<(ostream& f, const Carte& c);

class JeuCarte {
private:
    // appliquer le design pattern singleton plus tard
    // eventuellement membre static pour chaque nombre de carte n1, n2, n3
    array<const Carte*, 30> cartes_nv1; 
    array<const Carte*, 24> cartes_nv2;
    array<const Carte*, 13> cartes_nv3;
    array<const Carte*, 4> cartes_nobles;
public:
    JeuCarte();
    ~JeuCarte();
    size_t getNbCartes_nv1() const { return 30; }
    size_t getNbCartes_nv2() const { return 24; }
    size_t getNbCartes_nv3() const { return 13; }
    size_t getNbCartes_nobles() const { return 4; }
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
    size_t nb_cartes = 0;
public:
    explicit Pioche(const JeuCarte& j, TypeCarte t); // j'ai pris ca depuis le td mais a t on besoin du explicit ?
    ~Pioche();
    bool estVide() const { return nb_cartes == 0; }
    size_t getNbCartes() const { return nb_cartes; }
    const Carte& piocher();
    Pioche(const Pioche& p) = delete;
    Pioche& operator=(const Pioche& p) = delete;
};

#endif


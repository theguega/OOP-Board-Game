#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
using namespace std;


class CarteException{
private:
    string info;
public:
    CarteException(const string& i) : info(i) {}
    string getInfo() const { return info; }
};


enum class CouleurCarte {blanc, bleu, vert, noir, rouge, perle, indt}; // ajout de "indetermin�" car certaines carte ont une couleur de Bonus variable

string toString(CouleurCarte c);
ostream& operator<<(ostream& f, CouleurCarte c);
extern std::initializer_list<CouleurCarte> CouleursCarte;
std::map<std::string, CouleurCarte> stringToCouleurCarteMap = {
        {"blanc", CouleurCarte::blanc},
        {"bleu", CouleurCarte::bleu},
        {"vert", CouleurCarte::vert},
        {"noir", CouleurCarte::noir},
        {"rouge", CouleurCarte::rouge},
        {"perle", CouleurCarte::perle},
        {"indt", CouleurCarte::indt}
};
CouleurCarte StringToCouleurCarte(const string& couleurStr);


enum class TypeCarte { Niv1, Niv2, Niv3, Noble };
string toString(TypeCarte t);
ostream& operator<<(ostream& f, TypeCarte t);
extern std::initializer_list<TypeCarte> TypesCarte;


enum class Capacite { NewTurn, TakePrivilege, TakeJetonFromBonus, TakeJetonToAdv, AssociationBonus, None };
std::map<std::string, Capacite> stringToCapaciteMap = {
        {"NewTurn", Capacite::NewTurn},
        {"TakePrivilege", Capacite::TakePrivilege},
        {"TakeJetonFromBonus", Capacite::TakeJetonFromBonus},
        {"TakeJetonToAdv", Capacite::TakeJetonToAdv},
        {"AssociationBonus", Capacite::AssociationBonus},
        {"None", Capacite::None}
};
string toString(Capacite c);
ostream& operator<<(ostream& f, Capacite c);
Capacite StringToCapacite(const string& capaciteStr);



class Prix { // on l'encapsule dans la classe carte ? ou bien il y'a d'autres �l�ments qui ont un cout ?
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
    Capacite capacite; 
    Bonus bonus;
    unsigned int nbCouronnes;
    unsigned int nbPtsPrivilege;
    bool reserve = false;
public:
    Carte(TypeCarte t, Prix& p, Capacite c, Bonus& b, unsigned int nbC, unsigned int nbP); // constructeur classique
    Carte(TypeCarte t, Capacite c, unsigned int nbP); // constructeur carte noble
    ~Carte() = default;
    void reserver() { reserve = true; }
    bool isReserve() const { return reserve; }
    TypeCarte getType() const { return type; }
    Prix getPrix() const { return prix; }
    Capacite getCapacite() const { return capacite; }
    Bonus getBonus() const { return bonus; }
    unsigned int getNbCouronnes() const { return nbCouronnes; }
    unsigned int getNbPtsPrivilege() const { return nbPtsPrivilege; }
};
ostream& operator<<(ostream& f, const Carte& c);

class JeuCarte {
private:
    // appliquer le design pattern singleton plus tard
    // eventuellement membre static pour chaque nombre de carte n1, n2, n3
    array<const Carte*, 10> cartes_nv1; 
    array<const Carte*, 10> cartes_nv2;
    array<const Carte*, 10> cartes_nv3;
    array<const Carte*, 4> cartes_nobles;
public:
    JeuCarte();
    ~JeuCarte();
    size_t getNbCartes_nv1() const { return 10; }
    size_t getNbCartes_nv2() const { return 10; }
    size_t getNbCartes_nv3() const { return 10; }
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


//Je pense qu'il faudrait faire � peu pr�s comme le TD 4 : 
// classe pioche --> pour nous il y aura 3 instances de pioches (3 niveaux)
// classe Plateau --> classe Pyramide pour nous (l� o� il y a les cartes, le mot plateau est reserv� pour les jetons)


#pragmaonce
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class CarteException{
private:
    string info;
public:
    CarteException(const string& i) : info(i) {}
    string getInfo() const { return info; }
};

enum class Couleur {blanc, bleu, vert, noir, rouge, perle, indt}; // ajout de "indetermin�" car certaines carte ont une couleur de Bonus variable

enum class TypeCarte { Niv1, Niv2, Niv3, Royale };

enum class Capacite { NewTurn, TakePrivilege, TakeJetonFromBonus, TakeJetonToAdv, AssociationBonus };

class Prix { // on l'encapsule dans la classe carte ? ou bien il y'a d'autres �l�ments qui ont un cout ?
private:
    unsigned int blanc;
    unsigned int bleu;
    unsigned int vert;
    unsigned int noir;
    unsigned int rouge;
    unsigned int perle;
public:
    Prix(unsigned int bla, unsigned int ble, unsigned int v, unsigned int n, unsigned int r, unsigned int p) : blanc(bla), bleu(ble), vert(v), noir(n), rouge(r), perle(p) {}
    unsigned int getBlanc() const { return blanc; }
    unsigned int getBleu() const { return bleu; }
    unsigned int getVert() const { return vert; }
    unsigned int getNoir() const { return noir; }
    unsigned int getRouge() const { return rouge; }
    unsigned int getPerle() const { return perle; }
};
ostream& operator<<(ostream& f, const Prix& p) const;


class Bonus {
private:
    Couleur couleur;
    unsigned int nbBonus;
public:
    Bonus(Couleur c = 6, int n = 0) : couleur(c), nbBonus(n) {}
    setCouleur(Couleur c) : couleur(c) {};
    Couleur getCouleur() const { return couleur; }
    unsigned int getNbBonus() const { return nbBonus; }
};


class Carte {
private:
    TypeCarte type;
    Prix prix;
    Capacite capacite; 
    Bonus bonus;
    unsigned int nbCouronnes;
    unsigned int nbPtsPrivilege;
public:
    Carte(TypeCarte t, Prix& p, Capacite c, Bonus& b, unsigned int nbC, unsigned int nbP) : type(t), prix(p), capacite(c), bonus(b), nbCouronnes(nbC), nbPtsPrivilege(nbP) {}
    ~Carte() = default;
};

// Ajout de enum Type carte
// Ajout de enum Couleur
// Ajout de enum Capacite
// Ajout de classe Bonus
// Ajout de classe Prix


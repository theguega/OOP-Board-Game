#pragmaonce
#include <iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;


class CarteException{
private:
    string info;
public:
    CarteException(const string& i) : info(i) {}
    string getInfo() const { return info; }
};

enum class CouleurCarte {blanc, bleu, vert, noir, rouge, perle, indt}; // ajout de "indeterminé" car certaines carte ont une couleur de Bonus variable

enum class TypeCarte { Niv1, Niv2, Niv3, Royale };

enum class Capacite { NewTurn, TakePrivilege, TakeJetonFromBonus, TakeJetonToAdv, AssociationBonus };

class Prix { // on l'encapsule dans la classe carte ? ou bien il y'a d'autres éléments qui ont un cout ?
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
ostream& operator<<(ostream& f, const Prix& p) const;


class Bonus {
private:
    CouleurCarte couleur;
    unsigned int nbBonus;
public:
    Bonus(CouleurCarte c = 6, int n = 0) : couleur(c), nbBonus(n) {}
    setCouleur(Couleur c) : couleur(c) {};
    CouleurCarte getCouleur() const { return couleur; }
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
    TypeCarte getType() const { return type; }
    Prix getPrix() const { return prix; }
    Capacite getCapacite() const { return capacite; }
    Bonus getBonus() const { return bonus; }
    unsigned int getNbCouronnes() const { return nbCouronnes; }
    unsigned int getNbPtsPrivilege() const { return nbPtsPrivilege; }
};


// Ici est-ce que le jeu de cartes c'est l'ensemble des 3 paquets (+nobles) ou bien chaque paquet est un jeu ??
class JeuCarte {
private:
    // TypeCarte type;

    array<const Carte*, n1> cartes_nv1;
    array<const Carte*, n2> cartes_nv2;
    array<const Carte*, n3> cartes_nv3;
    array<const Carte*, 4> cartes_nobles;
public:
    JeuCarte();
    ~JeuCarte();
    size_t getNbCartes_nv1() const { return n1; }
    size_t getNbCartes_nv2() const { return n2; }
    size_t getNbCartes_nv3() const { return n3; }
    size_t getNbCartes_nobles() const { return 4; }
    const Carte& getCarteNiv1(size_t i) const;
    const Carte& getCarteNiv2(size_t i) const;
    const Carte& getCarteNiv3(size_t i) const;
    const Carte& getCarteNoble(size_t i) const;
    JeuCarte(const JeuCarte& j) = delete;
    JeuCarte& operator=(const JeuCarte& j) = delete
    // à poursuivre
};


// Ajout de enum Type carte
// Ajout de enum Couleur
// Ajout de enum Capacite
// Ajout de classe Bonus
// Ajout de classe Prix


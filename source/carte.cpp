#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "carte.h"

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


ostream& operator<<(ostream& f, const Prix& p){
	f << "Blanc : " << p.getBlanc() << "\n";
    f << "Bleu : " << p.getBleu() << "\n";
    f << "Vert : " << p.getVert() << "\n";
    f << "Noir : " << p.getNoir() << "\n";
    f << "Rouge : " << p.getRouge() << "\n";
    f << "Perle : " << p.getPerle() << "\n";

    return f;
}

ostream& operator<<(ostream& f, const Bonus& b){
    f << b.getNbBonus() << " " << b.getCouleur();
    return f;
}

JeuCarte::JeuCarte(){
    // TODO avec lecture de fichier XML
}

JeuCarte::~JeuCarte(){
    for (size_t i = 0; i < getNbCartes_nv1(); ++i){
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
    if (i >= n1)
        throw CarteException("Il n'y a que n1 cartes");
    return *cartes_nv1[i];
}

const Carte& JeuCarte::getCarteNiv2(size_t i) const{
    if (i >= n2)
        throw CarteException("Il n'y a que n2 cartes");
    return *cartes_nv2[i];
}

const Carte& JeuCarte::getCarteNiv3(size_t i) const{
    if (i >= n3)
        throw CarteException("Il n'y a que n3 cartes");
    return *cartes_nv3[i];
}

const Carte& JeuCarte::getCarteNoble(size_t i) const{
    if (i >= 4)
        throw CarteException("Il n'y a que 4 cartes");
    return *cartes_nobles[i];
}

Carte::Carte(TypeCarte t, Prix& p, Capacite c, Bonus& b, unsigned int nbC, unsigned int nbP) : type(t), prix(p), capacite(c), bonus(b), nbCouronnes(nbC), nbPtsPrivilege(nbP) {
    if (t == TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprié");
}

Carte::Carte(TypeCarte t, Capacite c, unsigned int nbP) : type(t), prix(0, 0, 0, 0, 0, 0), capacite(c), bonus(), nbCouronnes(0), nbPtsPrivilege(nbP) {
    if (t != TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprié");
}

Pioche::Pioche(const JeuCarte& j, TypeCarte t) : type_carte(t){
    if (t == TypeCarte::Niv1) {
        nb_cartes = j.getNbCartes_nv1();
        for (size_t i = 0; i < nb_cartes; i++)
            cartes.push_back(&j.getCarteNiv1(i));
    }
    if (t == TypeCarte::Niv2) {
        nb_cartes = j.getNbCartes_nv2();
        for (size_t i = 0; i < nb_cartes; i++)
            cartes.push_back(&j.getCarteNiv2(i));
    }
    if (t == TypeCarte::Niv3) {
        nb_cartes = j.getNbCartes_nv3();
        for (size_t i = 0; i < nb_cartes; i++)
            cartes.push_back(&j.getCarteNiv3(i));
    }
    // est-ce qu'on fait une pioche pour les cartes nobles, je suis pas sûr
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
        cartes[i - 1] = cartes[i]; //Dplace toutes les cartes  droite vers la gauche.
    nb_cartes--;
    return *c;

}

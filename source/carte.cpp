#include <iostream>
#include <string>
#include <vector>
#include "carte.h"

ostream& operator<<(ostream& f, const Prix& p) const{
	f << "Blanc : " << blanc << "\n";
    f << "Bleu : " << bleu << "\n";
    f << "Vert : " << vert << "\n";
    f << "Noir : " << noir << "\n";
    f << "Rouge : " << rouge << "\n";
    f << "Perle : " << perle << "\n";

    return f;
}

ostream& operator<<(ostream& f, const Bonus& b) const{
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
    if(t==TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprié")
}

Carte::Carte(TypeCarte t, Capacite c, unsigned int nbP) : type(t), prix(0, 0, 0, 0, 0, 0), capacite(c), bonus(), nbCouronnes(0), nbPtsPrivilege(nbP) {
    if (t != TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprié")
}


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

JeuCarte::JeuCarte(){
    // TODO
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

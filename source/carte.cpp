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

ostream& operator<<(ostream& f, const Carte& c) const{
    // TODO: insérer une instruction return ici
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

Pioche::Pioche(const JeuCarte& j, TypeCarte t) : type_carte(t){
    if (t == TypeCarte::Niv1) {
        cartes(new const Carte * [j.getNbCartes_nv1()]);
        nb_cartes(j.getNbCartes_nv1());
        for (size_t i = 0; i < nb_cartes; i++)
            cartes[i] = &j.getCarteNiv1(i);
    }
    if (t == TypeCarte::Niv2) {
        cartes(new const Carte * [j.getNbCartes_nv2()]);
        nb_cartes(j.getNbCartes_nv2());
        for (size_t i = 0; i < nb_cartes; i++)
            cartes[i] = &j.getCarteNiv2(i);
    }
    if (t == TypeCarte::Niv3) {
        cartes(new const Carte * [j.getNbCartes_nv3()]);
        nb_cartes(j.getNbCartes_nv3());
        for (size_t i = 0; i < nb_cartes; i++)
            cartes[i] = &j.getCarteNiv3(i);
    }
    // est-ce qu'on fait une pioche pour les cartes nobles, je suis pas sûr
}

Pioche::~Pioche(){
    delete[] cartes;
}

const Carte& Pioche::piocher(){
    // TODO: insérer une instruction return ici
}

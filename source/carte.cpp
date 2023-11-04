#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include "carte.h"
#include "data_cartes/Cartes.xml"
#include "data_cartes/Nobles.xml"
#include "pugixml/pugixml.hpp"
using namespace std;

std::initializer_list<CouleurCarte> CouleursCarte = { CouleurCarte::blanc, CouleurCarte::bleu, CouleurCarte::vert, CouleurCarte::noir, CouleurCarte::rouge, CouleurCarte::perle, CouleurCarte::indt };
std::initializer_list<TypeCarte> TypesCarte = { TypeCarte::Niv1, TypeCarte::Niv2, TypeCarte::Niv3, TypeCarte::Noble };

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


Carte::Carte(TypeCarte t, Prix& p, Capacite c, Bonus& b, unsigned int nbC, unsigned int nbP) : type(t), prix(p), capacite(c), bonus(b), nbCouronnes(nbC), nbPtsPrivilege(nbP) {
    if (t == TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprié");
}


Carte::Carte(TypeCarte t, Capacite c, unsigned int nbP) : type(t), prix(0, 0, 0, 0, 0, 0), capacite(c), bonus(), nbCouronnes(0), nbPtsPrivilege(nbP) {
    if (t != TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprié");
}


ostream& operator<<(ostream& f, const Carte& c){
    f << "-------------------------------------\n";
    f << c.getType() << "        " << "Bonus : " << c.getBonus() << "\n";
    f << "-------------------------------------\n";
    f << "Capacite : " << c.getCapacite() << "\n";
    f << "-------------------------------------\n";
    f << "Prix :\n" << c.getPrix() << "\n";
    f << "-------------------------------------\n";
    f << "Privileges : " << c.getNbPtsPrivilege() << "        " << "Couronnes : " << c.getNbCouronnes() << "\n";
    f << "-------------------------------------\n";
    return f;
}


JeuCarte::JeuCarte(){
    pugi::xml_document doc_cartes;
    pugi::xml_document doc_nobles;

    unsigned int n1 = this->getNbCartes_nv1();
    unsigned int n2 = this->getNbCartes_nv2();
    unsigned int n3 = this->getNbCartes_nv3();
    unsigned int n4 = this->getNbCartes_nobles();

    if (doc_cartes.load_file("Cartes.xml")) {
        pugi::xml_node liste_cartes = doc_cartes.child("Cartes");
        int i = 0;
        for (pugi::xml_node carte = liste_cartes.child("Carte"); carte; carte = carte.next_sibling("Carte")) {
            string type = carte.child_value("TYPE");
            unsigned int p_blanc = std::stoi(carte.child_value("PRIX_BLANC"));
            unsigned int p_bleu = std::stoi(carte.child_value("PRIX_BLEU"));
            unsigned int p_vert = std::stoi(carte.child_value("PRIX_VERT"));
            unsigned int p_noir = std::stoi(carte.child_value("PRIX_NOIR"));
            unsigned int p_rouge = std::stoi(carte.child_value("PRIX_ROUGE"));
            unsigned int p_perle = std::stoi(carte.child_value("PRIX_PERLE"));
            string capacite = carte.child_value("CAPACITE");
            string couleur_bonus = carte.child_value("COULEUR_BONUS");
            unsigned int bonus = std::stoi(carte.child_value("NB_BONUS"));
            unsigned int nb_couronnes = std::stoi(carte.child_value("NB_COURONNES"));
            unsigned int nb_pts_privileges = std::stoi(carte.child_value("NB_PTS_PRIVILEGE"));

            if (i < n1) {
                cartes_nv1[i] = new Carte(TypeCarte::Niv1, Prix(p_blanc, p_bleu, p_vert, p_noir, p_rouge, p_perle), StringToCapacite(capacite), Bonus(StringToCouleurCarte(couleur_bonus), bonus), nb_couronnes, nb_pts_privileges);
            }
            else if (i >= n1 && i < n2) {
                cartes_nv2[i-n1] = new Carte(TypeCarte::Niv2, Prix(p_blanc, p_bleu, p_vert, p_noir, p_rouge, p_perle), StringToCapacite(capacite), Bonus(StringToCouleurCarte(couleur_bonus), bonus), nb_couronnes, nb_pts_privileges);
            }
            else if (i >= n2) {
                cartes_nv3[i-n2] = new Carte(TypeCarte::Niv3, Prix(p_blanc, p_bleu, p_vert, p_noir, p_rouge, p_perle), StringToCapacite(capacite), Bonus(StringToCouleurCarte(couleur_bonus), bonus), nb_couronnes, nb_pts_privileges);
            }
            i++;
        }
    }
    else {
        throw CarteException("erreur dans la lecture du xml");
    }

    if (doc_cartes.load_file("Nobles.xml")) {
        pugi::xml_node liste_nobles = doc_cartes.child("Nobles");
        int j = 0;
        for (pugi::xml_node carte = liste_nobles.child("Noble"); carte; carte = carte.next_sibling("Noble")) {
            string type = carte.child_value("TYPE");
            string capacite = carte.child_value("CAPACITE");
            unsigned int nb_pts_privileges = std::stoi(carte.child_value("NB_PTS_PRIVILEGE"));

            cartes_nobles[j] = new Carte(TypeCarte::Noble, StringToCapacite(capacite), nb_pts_privileges);
            j++;
        }
    }
    else {
        throw CarteException("erreur dans la lecture du xml");
    }

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

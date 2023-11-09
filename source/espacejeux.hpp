#ifndef ESPACEJEUX_H
#define ESPACEJEUX_H
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "splendor.hpp"
#include "joueur.hpp"
#include "jetons.hpp"
#include "carte.h"
/*

Une solution pour reserver des cartes ? ou peut etre un vecteur de carte reservee dans joueur ?

class CarteReservee {
    Joueur& mon_joueur; 
    std::vector<const Carte&> cartes_reservees;
    public:

        CarteReservee(Joueur& j): mon_joueur(j) {};
        ~CarteReservee() = default;

        void ajouterCarte(const Carte& c);
        void acheterCarte(const Carte& c);
        void supprimerCarte(const Carte& c);

        bool estVide() const;

        int getNbCartes() const;
        std::vector<const Carte&> getCartes() const;

        CarteReservee(const CarteReservee&) = delete;
        CarteReservee& operator=(const CarteReservee&) = delete;
}; 

*/

class Pyramide {

    private:    
        std::vector<const Carte*> array_cartes[4];
    public:

        // peut etre mettre les pioches en attributs pour ne pas avoir a les passer en parametre a chaque fois    

        Pyramide( Pioche &pNv1, Pioche &pNv2,Pioche &pNv3,Pioche &pNoble); // constructeur
        ~Pyramide(); 

        bool estVide() const;

        void remplirPyramide(Pioche &pNv1, Pioche &pNv2,Pioche &pNv3,Pioche &pNoble); // parcour de toute la pyramide pour remplir les cases vides   
        void remplircasePyramide(int i, int j, Pioche &pNv1, Pioche &pNv2, Pioche &pNv3, Pioche &pNoble); // remplir une case de la pyramide
        
        void reserverCarte(int i, int j, Joueur& joueur, Pioche &pNv1, Pioche &pNv2, Pioche &pNv3, Pioche &pNoble); 
        void acheterCarte(int i, int j, Joueur& joueur, Pioche &pNv1, Pioche &pNv2, Pioche &pNv3, Pioche &pNoble); 

        Pyramide(const Pyramide&) = delete;
        Pyramide& operator=(const Pyramide&) = delete;


};

class EspaceJeux {
    private:
        // idealement espace jeux initialise tout les elements de jeux jsp si c'est pertinant d'init en reference
        
        // --------- init des jetons ---------
        LotDeJetons *lotJetons = new LotDeJetons();
        LotPrivileges *lotPrivileges = new LotPrivileges(); 
        Sac *sac  = new Sac(*lotJetons); 
        Plateau *plateau = new Plateau(*sac, *lotPrivileges); 
        
        // --------- init des cartes ---------
        
        JeuCarte *jeuxCartes = new JeuCarte();
        Pioche *piocheNv1 = new Pioche(*jeuxCartes, TypeCarte::Niv1);
        Pioche *piocheNv2 = new Pioche(*jeuxCartes, TypeCarte::Niv2);
        Pioche *piocheNv3 = new Pioche(*jeuxCartes, TypeCarte::Niv3);
        Pioche *piocheNoble = new Pioche(*jeuxCartes, TypeCarte::Noble);
        Pyramide *pyramide = new Pyramide(*piocheNv1, *piocheNv2, *piocheNv3, *piocheNoble);
    public:
        EspaceJeux();
        ~EspaceJeux();

        EspaceJeux(const EspaceJeux&) = delete;
        EspaceJeux& operator=(const EspaceJeux&) = delete;
};
 


#endif  //ESPACEJEUX_H
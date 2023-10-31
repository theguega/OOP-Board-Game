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

class Pyramide {
    private:
        std::vector<const Carte &> cartes[4];

    public:
        Pyramide( Pioche &pNv1, Pioche &pNv2,Pioche &pNv3,Pioche &pNoble); // constructeur
        ~Pyramide(); 

        void estVide() const;

        void remplirPyramide(Pioche &pNv1, Pioche &pNv2,Pioche &pNv3,Pioche &pNoble);

        void reserverCarte(int i, int j); 
        void acheterCarte( int i, int j); 
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
};
 


#endif  //ESPACEJEUX_H
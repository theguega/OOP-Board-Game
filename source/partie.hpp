#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>

#include <string>

#include <array>

#include <vector>

#include "splendor.hpp"
#include "joueur.hpp"
#include "jetons.hpp"
#include "carte.h"
//le code 

//La classe partie qui initialise les joueurs, le tour et l'espace de jeux 
class Partie {  
    
    EspaceJeux espaceJeux;
   
    std::vector<Joueur*> joueurs;
    
    int tour;

    Joueur joueurCourant;
    
    bool finPartie;

    public:
    // constructeurs JvsIA, JvsJ, IAvsIA
        //on push deux ia dans le vecteur de joueurs
        Partie() { tour = 0; finPartie = false; }
        
        Partie( Joueur* joueur1);
        
        Partie( Joueur* joueur1, Joueur* joueur2);

    // destructeur
        ~Partie();

    // getters
        EspaceJeux getEspaceJeux() const { return espaceJeux; }
        
        std::vector<Joueur*> getJoueurs() const { return joueurs; }
        
        int getTour() const { return tour; }

        Joueur getJoueurCourant() const { return joueurCourant; }

        bool getFinPartie() const { return finPartie; }

    // setters
        void setEspaceJeux(EspaceJeux e) { espaceJeux = e; }
        
        void setJoueurs(std::vector<Joueur*> j) { joueurs = j; }

        void setTour(int t) { tour = t; }
        
        void setJoueurCourant(Joueur j) { joueurCourant = j; }

        void setFinPartie(bool f) { finPartie = f; }    

    // methodes
        
    

#endif //PARTIE_H









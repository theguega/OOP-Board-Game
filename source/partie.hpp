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
#include "espacejeux.hpp"


//La classe partie qui initialise les joueurs, le tour et l'espace de jeux 
class Partie {  
    
    EspaceJeux* espaceJeux = new EspaceJeux(); ;
    Joueur* joueurs[2];
    int tour;
    int joueurCourant;
    
    public:

        /*Partie( vector<Joueur*> joueurs );  // utile ?? constructeur a partir d'un vecteur de joueurs */
        
        Partie( std::string nomJoueur1, std::string prenomJoueur1);
        
        Partie( std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2);

    // destructeur
        ~Partie();
    
    // getters
        
        int getTour() const { return tour; }
        int getjoueurCourant() const { return joueurCourant; }
        
        bool finPartie();
        void changerJoueurCourant();
        void tour_suivant(){tour++;}
        //erreur jsp pk 
        Partie(const Partie&) = delete;
        Partie& operator=(const Partie&) = delete;
        


        }; 
        
   

#endif 

#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>

#include <string>

#include <array>

#include <vector>

#include "joueur.hpp"
#include "jetons.hpp"
#include "carte.h"
#include "espacejeux.hpp"


//La classe partie qui initialise les joueurs, le tour et l'espace de jeux 
class Partie {  

    static Partie* instance;
    
    EspaceJeux* espaceJeux = new EspaceJeux(); ;
    Joueur* joueurs[2];
    
    int tour;
    int joueurCourant;
    
    /*Partie( vector<Joueur*> joueurs );  // utile ?? constructeur a partir d'un vecteur de joueurs */

    Partie();

    Partie( std::string nomJoueur1, std::string prenomJoueur1);
        
    Partie( std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2);

    ~Partie() {delete joueurs[0]; delete joueurs[1]; delete espaceJeux;};

    Partie(const Partie&) = delete;
    Partie& operator=(const Partie&) = delete;
    
    public: 
        
        int getTour() const { return tour; }
        Joueur* getjoueurCourant() const { return joueurs[joueurCourant]; }
        
        bool finPartie();
        void changerJoueurCourant();
        void tour_suivant(){tour++;}

        static Partie& getInstance();
        static Partie& getInstance(std::string nomJoueur1, std::string prenomJoueur1);
        static Partie& getInstance(std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2);

        static void libererInstance();

        void sauvegardePartie();
   

        }; 
        
   

#endif 

#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>
#include <string>

#include <array>
#include <vector>
#include <unordered_map>
#include <map>

#include <random>

// ###### Mettez ici le chemin absolu de la librairie sqlite de votre pc, masquez les autres #####
//#include "C:\Users\Beziat\source\repos\Projet_LO21\source\sqlite\sqlite3.h"
//#include "/Users/robertantaluca/Desktop/Projet_LO21/source/sqlite/sqlite3.h"
#include "/Users/theoguegan/Documents/UTC/GI01/LO21/Projet_LO21/source/sqlite/sqlite3.h"
//Samuel M
//Maxime

#include "joueur.hpp"
#include "espacejeux.hpp"

//La classe partie qui initialise les joueurs, le tour et l'espace de jeux 
class Partie {  

    //static Partie* instance;
    
    EspaceJeux* espaceJeux = new EspaceJeux(); ;
    Joueur* joueurs[2];
    
    int tour;
    int joueurCourant;
    
    /*Partie( vector<Joueur*> joueurs );  // utile ?? constructeur a partir d'un vecteur de joueurs */

   
    /*
    Partie(const Partie&) = delete;
    Partie& operator=(const Partie&) = delete;
    */
    public: 
        
        Partie();

        Partie( std::string nomJoueur1, std::string prenomJoueur1);
            
        Partie( std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2);

        ~Partie() {delete joueurs[0]; delete joueurs[1]; delete espaceJeux;};
        
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
        //void chargerPartie(); //si l'on décide qu'il est possible de joueur plusieurs partie en même temps

        void enregisterScore();

        }; 



//  ######  Debut du pattern Builder, pour l'instant il n'est pas utilisé comme constructeur de Partie  ######
// Masquez cette partie si vous compilez

//class PartieBuilder {
//public:
//    virtual ~PartieBuilder() {};
//    virtual void setEspaceJeu() const = 0;
//    virtual void setJoueurs(string nomJoueur1, string prenomJoueur1, string nomJoueur2, string prenomJoueur2) const = 0;
//    virtual void setTours() const = 0;
//    virtual void setJoueurCourant() const = 0;
//};
//
//
//class NewPartieBuilder : public PartieBuilder {
//private:
//    Partie* partie;
//public:
//    NewPartieBuilder() { this->Reset(); }
//    ~NewPartieBuilder() { delete partie; }
//    void Reset() { this->partie = new Partie(); }
//    void setEspaceJeu() const override;
//    void setJoueurs(string nomJoueur1, string prenomJoueur1, string nomJoueur2, string prenomJoueur2) const override;
//    void setTours() const override;
//    void setJoueurCourant()const override;
//};
//
//
//class LastPartieBuilder : public PartieBuilder {
//private:
//    Partie* partie;
//public:
//    LastPartieBuilder() { this->Reset(); }
//    ~LastPartieBuilder() { this->Reset(); }
//    void Reset() { this->partie = new Partie(); }
//    void setEspaceJeu() const override;
//    void setJoueurs(string nomJoueur1, string prenomJoueur1, string nomJoueur2, string prenomJoueur2) const override;
//    void setTours() const override;
//    void setJoueurCourant()const override;
//};
//
//
//class Director {
//private:
//    PartieBuilder* builder;
//public:
//    void set_builder(PartieBuilder* builder) { this->builder = builder; }
//    void BuildNewPartie();
//    void BuildLastPartie();
//};

//  ######  Fin du pattern Builder  ######


#endif 
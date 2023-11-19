#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <map>
#include <random>
#include <filesystem>
#include "carte.hpp"
#include "jetons.hpp"
#include "strategy.hpp"
#include "joueur.hpp"
#include "espacejeux.hpp"
#include "sqlite/sqlite3.h"

extern std::filesystem::path projectPath;

class PartieException {
private:
    string info;
public:
    PartieException(const string& i) : info(i) {}
    string getInfo() const { return info; }
};


class Partie { 
    friend class PartieBuilder;
    friend class NewPartieBuilder;
    friend class LastPartieBuilder;
private:
    EspaceJeux* espaceJeux = new EspaceJeux();
    Joueur* joueurs[2]; 
    int tour;
    int joueurCourant;
    //static Partie* instance; 
    //Partie( vector<Joueur*> joueurs );  // utile ?? constructeur a partir d'un vecteur de joueurs
    //Partie(const Partie&) = delete;
    //Partie& operator=(const Partie&) = delete;
public: 
    ~Partie() {delete espaceJeux; delete joueurs[0]; delete joueurs[1];}   
    Partie();

    Partie(std::string nomJoueur1, std::string prenomJoueur1);

    Partie(std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2);

    EspaceJeux& getEspaceJeux() const { return *espaceJeux; }

    Joueur& getJoueur1() const { return *joueurs[0]; }
    Joueur& getJoueur2() const { return *joueurs[1]; }
    void setJoueur1(Joueur& j);
    void setJoueur2(Joueur& j);

    int getTour() const { return tour; }
    void setTour(int n) { tour = n; }

    Joueur* getJoueurCourant() const { return joueurs[joueurCourant]; }
    void setJoueurCourant(int n);

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



//  ######  Debut du pattern Builder  ######

//class PartieBuilder {
//public:
//    virtual ~PartieBuilder() {};
//    virtual void setJoueurs() const {};
//    virtual void setCartesJoueurs() const {};
//    virtual void setJetonsJoueurs() const {};
//    virtual void updateEspaceJeu() const {};
//    virtual void setInfosPartie() const {};
//    friend class Partie;
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
//
//    void setJoueurs() const override {
//        partie->joueurs[0] = new Joueur("Alain", "telligence", type::IA);
//        partie->joueurs[1] = new Joueur("AL", "Gorythme", type::IA);
//    };
//
//    void setInfosPartie() const override {
//        partie->tour = 0;
//        partie->joueurCourant = 0;
//    };
//
//    Partie* GetProduct() {
//        Partie* result = this->partie;
//        return result;
//    }
//};
//
//
//class LastPartieBuilder : public PartieBuilder {
//private:
//    Partie* partie;
//public:
//    LastPartieBuilder() { this->Reset(); }
//    ~LastPartieBuilder() { delete partie; }
//    void Reset() { this->partie = new Partie(); }
//
//    virtual void setJoueurs();
//    virtual void setCartesJoueurs() const override;
//    virtual void setJetonsJoueurs() const override;
//    virtual void updateEspaceJeu() const override;
//    virtual void setInfosPartie() const override;
//
//    Partie* GetProduct() {
//        Partie* result = this->partie;
//        return result;
//    }
//};
//
//
//class Director {
//private:
//    PartieBuilder* builder;
//public:
//    void set_builder(PartieBuilder* builder) { this->builder = builder; }
//
//    void BuildNewPartie() {
//        builder->setJoueurs();
//        builder->setInfosPartie();
//    };
//
//    void BuildLastPartie() {
//        builder->setCartesJoueurs();
//        builder->setJetonsJoueurs();
//        builder->updateEspaceJeu();
//        builder->setInfosPartie();
//    }
//};


//  ######  Fin du pattern Builder  ######


#endif 

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
    EspaceJeux* espaceJeux;
    Joueur* joueurs[2]; 
    int tour;
    // #### implementation Singleton ####
    //static Partie* instance; 
    //Partie( vector<Joueur*> joueurs );  // utile ?? constructeur a partir d'un vecteur de joueurs
    //Partie(const Partie&) = delete;
    //Partie& operator=(const Partie&) = delete;
public:
    Partie();
    ~Partie() {delete espaceJeux; delete joueurs[0]; delete joueurs[1];}   

    EspaceJeux& getEspaceJeux() const { return *espaceJeux; }

    Joueur* getJoueur(size_t i) const { return joueurs[i]; }
    Joueur* getJoueur1() const { return joueurs[0]; }
    Joueur* getJoueur2() const { return joueurs[1]; }
    void setJoueur1(Joueur& j);
    void setJoueur2(Joueur& j);

    int getTour() const { return tour; }
    void setTour(int n) { tour = n; }
    void incrementeTour() { tour++; }

    bool finPartie();

    static Partie& getInstance();
    static Partie& getInstance(std::string nomJoueur1, std::string prenomJoueur1);
    static Partie& getInstance(std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2);
    static void libererInstance();
    void enregisterScore();
}; 



//  ######  Debut du pattern Builder  ######

class PartieBuilder {
public:
    virtual ~PartieBuilder() {};
    virtual void setJoueurs(string pseudo1, type t1, string pseudo2, type t2) const = 0;
    virtual void setJoueurs() const = 0;
    virtual void setCartesJoueurs() const = 0;
    virtual void setJetonsJoueurs() const = 0;
    virtual void updateEspaceJeu() const = 0;
    virtual void setInfosPartie() const = 0;
    friend class Partie;
};


class NewPartieBuilder : public PartieBuilder {
private:
    Partie* partie;
public:
    NewPartieBuilder() { this->Reset(); }
    ~NewPartieBuilder() { delete partie; }
    void Reset() { this->partie = new Partie(); }

    void setJoueurs(string pseudo1, type t1, string pseudo2, type t2) const override {
        partie->joueurs[0] = new Joueur(pseudo1, t1);
        partie->joueurs[1] = new Joueur(pseudo2, t2);
    };

    void setJoueurs() const override {};
    void setCartesJoueurs() const override {};
    void setJetonsJoueurs() const override {};
    void updateEspaceJeu() const override {};

    void setInfosPartie() const override {
        partie->tour = 0;
    };

    Partie* GetProduct() {
        Partie* result = this->partie;
        return result;
    }
};


class LastPartieBuilder : public PartieBuilder {
private:
    Partie* partie;
public:
    LastPartieBuilder() { this->Reset(); }
    ~LastPartieBuilder() { delete partie; }
    void Reset() { this->partie = new Partie(); }

    virtual void setJoueurs(string pseudo1, type t1, string pseudo2, type t2) const {};
    virtual void setJoueurs() const override;
    virtual void setCartesJoueurs() const override;
    virtual void setJetonsJoueurs() const override;
    virtual void updateEspaceJeu() const override;
    virtual void setInfosPartie() const override;

    Partie* GetProduct() {
        Partie* result = this->partie;
        return result;
    }
};


class Director {
private:
    PartieBuilder* builder;
public:
    void set_builder(PartieBuilder* builder) { this->builder = builder; }

    void BuildNewPartie(string pseudo1, type t1, string pseudo2, type t2) {
        builder->setJoueurs(pseudo1, t1, pseudo2, t2);
        builder->setInfosPartie();
    };

    void BuildLastPartie() {
        builder->setJoueurs();
        builder->setCartesJoueurs();
        builder->setJetonsJoueurs();
        builder->updateEspaceJeu();
        builder->setInfosPartie();
    }
};


//  ######  Fin du pattern Builder  ######


#endif 

#ifndef PARTIE_H
#define PARTIE_H

/*
-----------------------------
  _____           _   _
 |  __ \         | | (_)
 | |__) |_ _ _ __| |_ _  ___
 |  ___/ _` | '__| __| |/ _ \
 | |  | (_| | |  | |_| |  __/
 |_|   \__,_|_|   \__|_|\___|

-----------------------------
*/

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <map>
#include <random>
#include "joueur.hpp"
#include "espacejeux.hpp"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>




//Implémentation de la partie

//La classe partie sert a contenir tous les éléments du jeu, a savoir les joueurs, et l'espace de jeu contenant le plateau et la pyramide de carte
class Partie {
    friend class PartieBuilder;
    friend class NewPartieBuilder;
    friend class LastPartieBuilder;
    private:
        EspaceJeux * espaceJeux;
        Joueur * joueurs[2];
        int tour;
    public:
        Partie();
        ~Partie() {
        delete espaceJeux;
        delete joueurs[0];
        delete joueurs[1];
        }

    //Getter
    EspaceJeux & getEspaceJeux() const {
        return * espaceJeux;
    }
    Joueur * getJoueurs() const {
        return * joueurs;
    }
    Joueur * getJoueur(size_t i) const {
        return joueurs[i];
    }
    Joueur * getJoueur1() const {
        return joueurs[0];
    }
    Joueur * getJoueur2() const {
        return joueurs[1];
    }
    int getTour() const {
        return tour;
    }

    //Setter
    void setJoueur1(Joueur & j);
    void setJoueur2(Joueur & j);
    void setTour(int n) {
        tour = n;
    }

    // Autres
    void incrementeTour() {
        tour++;
    }
};




//  ######  Implementation du pattern Builder  ######

//Classe abstraite pour construire une partie (nouvelle ou ancienne)

class PartieBuilder {
    public:
    virtual~PartieBuilder() {}
    virtual void setJoueurs(string pseudo1, type t1, string pseudo2, type t2) const = 0;
    virtual void setJoueurs() const = 0;
    virtual void setCartesJoueurs() const = 0;
    virtual void setJetonsJoueurs() const = 0;
    virtual void updateEspaceJeu() const = 0;
    virtual void setInfosPartie() const = 0;
    friend class Partie;
};




class NewPartieBuilder: public PartieBuilder {
    private: Partie * partie;
    public:
        NewPartieBuilder() {
            this -> Reset();
        }
        ~NewPartieBuilder() {
            delete partie;
        }
        void Reset() {
            this -> partie = new Partie();
        }
        void setJoueurs(string pseudo1, type t1, string pseudo2, type t2) const override {
            partie -> joueurs[0] = new Joueur(pseudo1, t1);
            partie -> joueurs[1] = new Joueur(pseudo2, t2);
        }
        void setInfosPartie() const override {
            partie -> tour = 0;
        }
        Partie * GetProduct() {
            Partie * result = this -> partie;
            return result;
        }

        // unused
        void setJoueurs() const override {}
        void setCartesJoueurs() const override {}
        void setJetonsJoueurs() const override {}
        void updateEspaceJeu() const override {}
};




class LastPartieBuilder: public PartieBuilder {
    private:
        Partie * partie;
    public:
        LastPartieBuilder() {
            this -> Reset();
        }
        ~LastPartieBuilder() {
            delete partie;
        }
        void Reset() {
            this -> partie = new Partie();
        }
        void setJoueurs() const override;
        void setCartesJoueurs() const override;
        void setJetonsJoueurs() const override;
        void updateEspaceJeu() const override;
        void setInfosPartie() const override;

        Partie * GetProduct() {
            Partie * result = this -> partie;
            return result;
        }

        //unused
        virtual void setJoueurs([[maybe_unused]]string pseudo1,[[maybe_unused]]type t1,[[maybe_unused]]string pseudo2,[[maybe_unused]]type t2) const override {}

};




class Director {
    private:
        PartieBuilder * builder;
    public:
        void set_builder(PartieBuilder * builder) {
        this -> builder = builder;
        }

        //Nouvelle partie
        void BuildNewPartie(string pseudo1, type t1, string pseudo2, type t2) {
            builder -> setJoueurs(pseudo1, t1, pseudo2, t2);
            builder -> setInfosPartie();
        }

        //Ancienne partie
        void BuildLastPartie() {
            builder -> setJoueurs();
            builder -> setCartesJoueurs();
            builder -> setJetonsJoueurs();
            builder -> updateEspaceJeu();
            builder -> setInfosPartie();
        }
};

#endif

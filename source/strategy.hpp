//
// Created by samma on 31/10/2023.
//

#ifndef PROJET_LO21_STRATEGY_HPP
#define PROJET_LO21_STRATEGY_HPP

#include "splendor.hpp"
#include "jetons.hpp"
#include "joueur.hpp"
#include <iostream>
#include <string>
#include <array>
#include <vector>

class Strategy {
public:
    virtual ~Strategy() = default;

    // actions optionnelles
    virtual Privilege utiliserPrivilege(const Joueur& joueur, const EspaceJeux& espaceJeux) = 0;
    virtual Privilege remplirPlateau(const Joueur& joueur, const EspaceJeux& espaceJeux) = 0;

    // actions obligatoires
    virtual Jeton piocherJeton(const Joueur& joueur, const EspaceJeux& espaceJeux) = 0;
    virtual Carte orReserverCarte(const Joueur& joueur, const EspaceJeux& espaceJeux) = 0;
    virtual Carte acheterCarteJoaillerie(const Joueur& joueur, const EspaceJeux& espaceJeux) = 0;
};

class StrategyHumain : public Strategy {
public:
    Privilege utiliserPrivilege(const Joueur& joueur, const EspaceJeux& espaceJeux) override {
        // Logique de choix pour l'humain
    }
};

class StrategyIA : public Strategy {
public:
    Privilege utiliserPrivilege(const Joueur& joueur, const EspaceJeux& espaceJeux) override {
        // Logique de choix pour l'IA
    }
};


#endif //PROJET_LO21_STRATEGY_HPP

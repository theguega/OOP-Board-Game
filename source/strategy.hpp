//
// Created by samma on 31/10/2023.
//

#ifndef PROJET_LO21_STRATEGY_HPP
#define PROJET_LO21_STRATEGY_HPP

#include "splendor.hpp"
#include "jetons.hpp"
#include <iostream>
#include <string>
#include <array>
#include <vector>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual const Jeton& choisirJeton(Plateau& plateau) = 0;

    // actions optionnelles
    /*virtual Privilege utiliserPrivilege(const EspaceJeux& espaceJeux) = 0;
    virtual Privilege remplirPlateau(const EspaceJeux& espaceJeux) = 0;

    // actions obligatoires
    virtual Jeton piocherJeton(const EspaceJeux& espaceJeux) = 0;
    virtual Carte orReserverCarte(const EspaceJeux& espaceJeux) = 0;
    virtual Carte acheterCarteJoaillerie(const EspaceJeux& espaceJeux) = 0;*/
};


class StrategyHumain : public Strategy {
public:
    const Jeton& choisirJeton(Plateau& plateau) override;
    //Privilege utiliserPrivilege(const EspaceJeux& espaceJeux) override;
};

class StrategyIA : public Strategy {
public:
    //Privilege utiliserPrivilege(const EspaceJeux& espaceJeux) override;
};



#endif //PROJET_LO21_STRATEGY_HPP

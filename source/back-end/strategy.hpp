#ifndef PROJET_LO21_STRATEGY_HPP
#define PROJET_LO21_STRATEGY_HPP

/*
-------------------------------------------
   _____ _             _
  / ____| |           | |
 | (___ | |_ _ __ __ _| |_ ___  __ _ _   _
  \___ \| __| '__/ _` | __/ _ \/ _` | | | |
  ____) | |_| | | (_| | ||  __/ (_| | |_| |
 |_____/ \__|_|  \__,_|\__\___|\__, |\__, |
                                __/ | __/ |
                               |___/ |___/
-------------------------------------------
*/

#include "espacejeux.hpp"




class Strategy  {
public:
    virtual ~Strategy() = default;

    virtual unsigned int choix_min_max(unsigned int min, unsigned int j) = 0;
    virtual unsigned int choixMenu(vector<int> poss) = 0;
    virtual Couleur choixCouleur() = 0;
    virtual Couleur choixCouleurNonINDT() = 0;
};




class StrategyHumain : public Strategy {
public:
    virtual unsigned int choix_min_max(unsigned int min, unsigned int j) override;
    virtual unsigned int choixMenu(vector<int> poss) override;
    virtual Couleur choixCouleur() override;
    virtual Couleur choixCouleurNonINDT() override;
};




class StrategyIA : public Strategy {
public:
    virtual unsigned int choix_min_max(unsigned int min, unsigned int j) override;
    virtual unsigned int choixMenu(vector <int> poss) override;
    virtual Couleur choixCouleur() override;
    virtual Couleur choixCouleurNonINDT() override;
};

#endif

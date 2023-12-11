#ifndef PROJET_LO21_STRATEGY_HPP
#define PROJET_LO21_STRATEGY_HPP

#include "espacejeux.hpp"

class Strategy  {

public:
    virtual ~Strategy() = default;

    //Nouvelle version de strategy
    virtual unsigned int choix_min_max(unsigned int min, unsigned int j) = 0;
    virtual unsigned int choixMenu() = 0;
    virtual Couleur choixCouleur() = 0;
    virtual Couleur choixCouleurNonINDT() = 0;
};


class StrategyHumain : public Strategy {
public:
    //Nouvelle version de strategy
    virtual unsigned int choix_min_max(unsigned int min, unsigned int j) override;
    virtual unsigned int choixMenu() override;
    virtual Couleur choixCouleur() override;
    virtual Couleur choixCouleurNonINDT() override;
};

class StrategyIA : public Strategy {
public:
    //Nouvelle version de strategy
    virtual unsigned int choix_min_max(unsigned int min, unsigned int j) override;
    virtual unsigned int choixMenu() override;
    virtual Couleur choixCouleur() override;
    virtual Couleur choixCouleurNonINDT() override;
};



#endif //PROJET_LO21_STRATEGY_HPP

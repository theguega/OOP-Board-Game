#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "jetons.hpp"

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual const Jeton& choisirJeton(Plateau& plateau) = 0;
    virtual void remplirPlateauStrat(Plateau& plateau, Sac& sac) = 0;

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
    void remplirPlateauStrat(Plateau& plateau, Sac& sac) override;

    //Privilege utiliserPrivilege(const EspaceJeux& espaceJeux) override;
};

class StrategyIA : public Strategy {
public:
    //Privilege utiliserPrivilege(const EspaceJeux& espaceJeux) override;
};



#endif //PROJET_LO21_STRATEGY_HPP

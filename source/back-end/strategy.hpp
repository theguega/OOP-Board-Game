#ifndef PROJET_LO21_STRATEGY_HPP
#define PROJET_LO21_STRATEGY_HPP

#include "espacejeux.hpp"

class StrategyException
{
public:
    StrategyException(const std::string& i) :info(i) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual std::pair<unsigned int, unsigned int> choisirJeton(Plateau& plateau) = 0;
    virtual void remplirPlateauStrat(Plateau& plateau, Sac& sac) = 0;

    virtual std::vector<const Jeton*> recupJetonStrat(Plateau& plateau) = 0;


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
    std::pair<unsigned int, unsigned int> choisirJeton(Plateau& plateau) override;
    void remplirPlateauStrat(Plateau& plateau, Sac& sac) override;
    std::vector<const Jeton*> recupJetonStrat(Plateau& plateau) override;


    //Privilege utiliserPrivilege(const EspaceJeux& espaceJeux) override;
};

class StrategyIA : public Strategy {
public:
    std::pair<unsigned int, unsigned int> choisirJeton(Plateau& plateau) override;
    std::vector<const Jeton*> recupJetonStrat(Plateau& plateau) override;
    void remplirPlateauStrat(Plateau& plateau, Sac& sac) override;


    //Privilege utiliserPrivilege(const EspaceJeux& espaceJeux) override;



};



#endif //PROJET_LO21_STRATEGY_HPP

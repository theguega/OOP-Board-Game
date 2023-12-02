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
    virtual unsigned int choixNiveau() = 0;
    virtual std::pair<unsigned int, unsigned int> reservationCarte(Pyramide& pyramide) = 0;
    virtual std::pair<unsigned int, unsigned int> achatNoble(Pyramide& pyramide) = 0;
    virtual unsigned int choixAchat() = 0;
    virtual std::pair< Couleur, unsigned int> achatReserve(unsigned int nbCartesReservees) = 0;
    virtual unsigned int choixActionsOptionelles() = 0;
    virtual unsigned int choixActionsObligatoires() = 0;

};


class StrategyHumain : public Strategy {
public:
    std::pair<unsigned int, unsigned int> choisirJeton(Plateau& plateau) override;
    void remplirPlateauStrat(Plateau& plateau, Sac& sac) override;
    std::vector<const Jeton*> recupJetonStrat(Plateau& plateau) override;
    unsigned int choixNiveau() override;
    unsigned int choixAchat() override;
    std::pair<unsigned int, unsigned int> achatNoble(Pyramide& pyramide) override;

    std::pair< Couleur, unsigned int> achatReserve(unsigned int nbCartesReservees) override;

    std::pair<unsigned int, unsigned int> reservationCarte(Pyramide& pyramide) override;

    virtual unsigned int choixActionsOptionelles() override;
    virtual unsigned int choixActionsObligatoires() override;

    //Privilege utiliserPrivilege(const EspaceJeux& espaceJeux) override;
};

class StrategyIA : public Strategy {
public:
    std::pair<unsigned int, unsigned int> choisirJeton(Plateau& plateau) override;
    std::vector<const Jeton*> recupJetonStrat(Plateau& plateau) override;
    void remplirPlateauStrat(Plateau& plateau, Sac& sac) override;
    unsigned int choixNiveau() override;
    unsigned int choixAchat() override;
    std::pair< Couleur, unsigned int> achatReserve(unsigned int nbCartesReservees) override;
    std::pair<unsigned int, unsigned int> achatNoble(Pyramide& pyramide) override;


    std::pair<unsigned int, unsigned int> reservationCarte(Pyramide& pyramide) override;

    virtual unsigned int choixActionsOptionelles() override;
    virtual unsigned int choixActionsObligatoires() override;


    //Privilege utiliserPrivilege(const EspaceJeux& espaceJeux) override;



};



#endif //PROJET_LO21_STRATEGY_HPP

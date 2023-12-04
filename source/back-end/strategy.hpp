#ifndef PROJET_LO21_STRATEGY_HPP
#define PROJET_LO21_STRATEGY_HPP

#include "espacejeux.hpp"

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual std::pair<unsigned int, unsigned int> choisirJeton(Plateau& plateau) = 0;

    //virtual std::vector<const Jeton*> recupJetonStrat(Plateau& plateau) = 0;
    virtual unsigned int choixNiveau() = 0;
    virtual std::pair<unsigned int, unsigned int> reservationCarte(Pyramide& pyramide) = 0;
    virtual std::pair<unsigned int, unsigned int> achatNoble(Pyramide& pyramide) = 0;
    virtual unsigned int choixAchat() = 0;
    virtual std::pair< Couleur, unsigned int> achatReserve(unsigned int nbCartesReservees) = 0;
    virtual unsigned int utiliserPrivilege() = 0;

    //choix de l'action
    virtual unsigned int choixActionsOptionelles() = 0;
    virtual unsigned int choixActionsObligatoires() = 0;

    //Nouvelle version de strategy
    virtual unsigned int choix_min_max(unsigned int min, unsigned int j) = 0;
    virtual unsigned int choixMenu() = 0;

};


class StrategyHumain : public Strategy {
public:
    std::pair<unsigned int, unsigned int> choisirJeton(Plateau& plateau) override;
    //std::vector<const Jeton*> recupJetonStrat(Plateau& plateau) override;
    unsigned int choixNiveau() override;
    unsigned int choixAchat() override;
    std::pair<unsigned int, unsigned int> achatNoble(Pyramide& pyramide) override;

    std::pair< Couleur, unsigned int> achatReserve(unsigned int nbCartesReservees) override;

    std::pair<unsigned int, unsigned int> reservationCarte(Pyramide& pyramide) override;

    virtual unsigned int choixActionsOptionelles() override;
    virtual unsigned int choixActionsObligatoires() override;

    virtual unsigned int utiliserPrivilege() override;

    //Nouvelle version de strategy
    virtual unsigned int choix_min_max(unsigned int min, unsigned int j) override;
    virtual unsigned int choixMenu() override;
};

class StrategyIA : public Strategy {
public:
    std::pair<unsigned int, unsigned int> choisirJeton(Plateau& plateau) override;
    //std::vector<const Jeton*> recupJetonStrat(Plateau& plateau) override;
    unsigned int choixNiveau() override;
    unsigned int choixAchat() override;
    std::pair< Couleur, unsigned int> achatReserve(unsigned int nbCartesReservees) override;
    std::pair<unsigned int, unsigned int> achatNoble(Pyramide& pyramide) override;


    std::pair<unsigned int, unsigned int> reservationCarte(Pyramide& pyramide) override;

    virtual unsigned int choixActionsOptionelles() override;
    virtual unsigned int choixActionsObligatoires() override;

    virtual unsigned int utiliserPrivilege() override;

    //Nouvelle version de strategy
    virtual unsigned int choix_min_max(unsigned int min, unsigned int j) override;
    virtual unsigned int choixMenu() override;
};



#endif //PROJET_LO21_STRATEGY_HPP

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <random>
#include "partie.hpp"

class Controller {
private:
	Partie* partie;
	Joueur* joueurCourant = nullptr;
	
	StrategyHumain strategy_Humain;
	StrategyIA strategy_IA;

	Strategy * strategy_courante  = nullptr;
	
public:
	Controller();
	~Controller() { delete partie; }
	// getters
	Partie& getPartie() { return *partie; };
    Joueur& getJoueurCourant() { return *joueurCourant; }
    Joueur& getJoueurAdverse() {for (int i = 0; i < 2; i++) { if (partie->getJoueur(i) != joueurCourant) { return *partie->getJoueur(i); } }; }
	// setters
	void setJoueurCourant(int n);
	// actions partie
	void lancerPartie();
	void tour_suivant();
    void changerJoueurCourant();

    unsigned int choixActionsOptionelles() {return strategy_courante->choixActionsOptionelles(); };
    unsigned int choixActionsObligatoires() {return strategy_courante->choixActionsObligatoires(); };

    bool verifAchatCarte(const Carte& carte, EspaceJeux& espaceJeux);
	// Actions optionnelles
	void utiliserPrivilege(Plateau& plateau);
	void remplirPlateau(Plateau& plateau, Sac& sac, Joueur& joueurAdverse);

	// Actions obligatoires
	void recupererJetons(Plateau& plateau);
    void acheterCarteNoble (Pyramide& pyramide);
    void acheterCarteJoaillerie(EspaceJeux& espaceJeux);
	void orReserverCarte(Pyramide& pyramide, Plateau& plateau);

	//gestion données
	void sauvegardePartie();
	void enregisterScore();

	// verifications

};


#endif

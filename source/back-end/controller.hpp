#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <random>
#include "partie.hpp"

class Controller {
private:
	Partie* partie;
	Joueur* joueurCourant = nullptr;
public:
	Controller();
	~Controller() { delete partie; }
	// getters
	Partie& getPartie() { return *partie; };
	Joueur& getJoueurCourant() { return *joueurCourant; }
	Joueur& getJoueurAdverse() {for (int i = 0; i < 2; i++) { if (partie->getJoueur(i) != joueurCourant) { return *partie->getJoueur(i); } } }
	// setters
	void setJoueurCourant(int n);
	// actions partie
	void lancerPartie();
	void tour_suivant();
    void changerJoueurCourant();

    unsigned int choixActionsOptionelles() {return joueurCourant->strategy->choixActionsOptionelles(); };
    unsigned int choixActionsObligatoires() {return joueurCourant->strategy->choixActionsObligatoires(); };

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

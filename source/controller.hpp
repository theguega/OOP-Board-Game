#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "partie.hpp"

class Controller {
private:
	Partie* partie;
	Joueur* joueur_courant;
public:
	Controller();
	~Controller();
	// getters
	Joueur& getJoueurCourant{ return joueur_courant; }
	Partie& getPartie{ return partie; }
	void lancerPartie();
	// actions obligatoires

	// actions optionnelles

	// end of turn checkings
	
	void newTurn();

};

#endif
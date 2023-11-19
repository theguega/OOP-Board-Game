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

	// actions optionnelles
	void utiliserPrivilege(Plateau& plateau);
	void remplirPlateau(Plateau& plateau, Sac& sac, Joueur& joueurAdverse);

	// Actions obligatoires
	void recupererJetons(Plateau& plateau);
	void acheterCarteJoaillerie(Pyramide& pyramide);
	void orReserverCarte(Pyramide& pyramide, Plateau& plateau);

	// end of turn checkings
	
	void newTurn();

};

#endif
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
	Joueur& getJoueurAdverse();
	// setters
	void setJoueurCourant(int n);
	// actions partie
	void lancerPartie();
	void tour_suivant();

	// Actions optionnelles

	void utiliserPrivilege(Plateau& plateau);
	void remplirPlateau(Plateau& plateau, Sac& sac, Joueur& joueurAdverse);

	// Actions obligatoires
	void recupererJetons(Plateau& plateau);
	void acheterCarteJoaillerie(Pyramide& pyramide);
	void orReserverCarte(Pyramide& pyramide, Plateau& plateau);

	//gestion données
	void sauvegardePartie();
	void enregisterScore();

	// verifications

};


#endif
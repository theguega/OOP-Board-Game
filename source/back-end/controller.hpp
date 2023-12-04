#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <random>
#include "partie.hpp"

class Controller {
private:
	Partie* partie;
	Joueur* joueurCourant = nullptr;
    Strategy * strategy_courante  = nullptr;
	
	StrategyHumain strategy_Humain;
	StrategyIA strategy_IA;
public:
	Controller();
	~Controller() { delete partie; }

	// getters
	Partie& getPartie() { return *partie; };
    Joueur& getJoueurCourant() { return *joueurCourant; }
    Strategy& getStrategyCourante() {return *strategy_courante;}
    Joueur& getJoueurAdverse() {
        for (int i = 0; i < 2; i++) {
            if (partie->getJoueur(i) != joueurCourant) {
                return *partie->getJoueur(i);
            }
        }
        throw SplendorException("pas de d'adverssaire trouvé..\n");
    };

	// setters
	void setJoueurCourant(int n);

	// actions partie
	void lancerPartie();
    void changerJoueurCourant();
    void quitter();

    //Choix de l'action
    unsigned int choixActionsOptionelles();
    unsigned int choixActionsObligatoires();

	// Actions optionnelles
	void utiliserPrivilege(Plateau& plateau);
    void remplirPlateau(Plateau& plateau, Sac& sac);

	// Actions obligatoires
	void recupererJetons(Plateau& plateau);
    void acheterCarteJoaillerie(EspaceJeux& espaceJeux);
	void orReserverCarte(Pyramide& pyramide, Plateau& plateau);

    //s'effectue automatiquement lorsque le joueur a 3,6 pts prestige
    void acheterCarteNoble (Pyramide& pyramide);

	//gestion données
	void sauvegardePartie();
	void enregisterScore();

	// verifications
    void verifPrivileges();
    void verifPlateauvide();
    void verifSacvide();
    bool verifAchatCarte(const Carte& carte, EspaceJeux& espaceJeux);
};


#endif

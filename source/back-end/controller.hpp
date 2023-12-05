#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <random>
#include "partie.hpp"
#include <cstdlib>

class Controller {
private:
	Partie* partie;
	Joueur* joueurCourant = nullptr;
    Strategy * strategy_courante  = nullptr;
	
	StrategyHumain strategy_Humain;
	StrategyIA strategy_IA;
public:
	Controller();
    Controller(QString statut_partie, QString pseudo_j_1, type type_j_1, QString pseudo_j_2, type type_j_2);
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
    Plateau& getPlateau() const {return partie->getEspaceJeux().getPlateau();}
    Pyramide& getPyramide() const {return partie->getEspaceJeux().getPyramide();}
	// setters
	void setJoueurCourant(int n);

	// actions partie
	void lancerPartie();
    void changerJoueurCourant();
    void jouer();
    void quitter();

    //Choix de l'action
    unsigned int choixActionsOptionelles();
    unsigned int choixActionsObligatoires();

	// Actions optionnelles
	void utiliserPrivilege(Plateau& plateau);
    void remplirPlateau(Plateau& plateau, Sac& sac);

	// Actions obligatoires
    void recupererJetons();
    void acheterCarteJoaillerie(EspaceJeux& espaceJeux);
	void orReserverCarte(Pyramide& pyramide, Plateau& plateau);

    //donne un privilege au joueur adverse en suivant la logique de splendor duel
    void donPrivilegeAdverse();

    //s'effectue automatiquement lorsque le joueur a 3,6 pts prestige
    void acheterCarteNoble (Pyramide& pyramide);

	//gestion données
	void sauvegardePartie();
	void enregisterScore();

	// verifications
    void verifPrivileges();
    void verifPlateauvide();
    void verifSacvide();
    void verifOrSurPlateau();
    bool verifAchatCarte(const Carte& carte, EspaceJeux& espaceJeux);

};


#endif

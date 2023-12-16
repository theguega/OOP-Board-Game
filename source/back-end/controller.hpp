#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <random>
#include "partie.hpp"
#include <QDebug>
#include <cstdlib>

class Controller {
private:
    string stat_partie;
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
    string getStatutPartie()const{return stat_partie;}
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
    EspaceJeux& getEspaceJeux() const{return partie->getEspaceJeux();}
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

    // Capacite
    bool appliquerCapacite(Capacite capa,const Carte &carte);

	// Actions optionnelles
	void utiliserPrivilege(Plateau& plateau);
    void remplirPlateau(Plateau& plateau, Sac& sac);

	// Actions obligatoires
    void recupererJetons(bool capacite,Couleur coulBonus = Couleur::INDT);
    bool acheterCarteJoaillerie(EspaceJeux& espaceJeux);
	void orReserverCarte(Pyramide& pyramide, Plateau& plateau);

    //donne un privilege au joueur adverse en suivant la logique de splendor duel
    void donPrivilegeAdverse();

    //s'effectue automatiquement lorsque le joueur a 3,6 pts prestige
    void acheterCarteNoble (Pyramide& pyramide);

	//gestion données
	void sauvegardePartie();
	void enregisterScore();

	// verifications
    vector<int> verifActionsImpossibles();
    vector<int> verifActionsOptImpossibles();
    void verifPrivileges();
    void verifPlateauvide();
    void verifSacvide();
    void verifOrSurPlateau();
    void verifTroisCarteReserve();
    void verifJetonSupDix();
    bool verifAchatCarte(const Carte* carte);
    vector<pair<int, int>> GenereCartePyramideDispo();
    vector<pair<Couleur, int>> GenereCarteResaDispo();

};


#endif

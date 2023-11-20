#include "controller.hpp"

Controller::Controller() {
	Director* director = new Director();
	string statut_partie;
	std::cout << "ancienne ou nouvelle partie ?";
	std::cin >> statut_partie;
	if (statut_partie == "New") {
		NewPartieBuilder* builder = new NewPartieBuilder();
		director->set_builder(builder);
		cout << "Combien de joueur voulez vous jouer ? (0,1,2)" << std::endl;
		int nbJoueur;
		cin >> nbJoueur;
        switch (nbJoueur) {
        case 0:
        {   cout << "IA vs IA" << std::endl;
            director->BuildNew2IAPartie();
            Partie* p = builder->GetProduct();
            partie = p;
            break;
        }
        case 1:
        {
            cout<<"IA vs HUMAIN"<<std::endl;
            cout<<"Veuillez saisir le pseudo du joueur"<<std::endl;
            string pseudo;
            std::cin>>pseudo;
            director->BuildNew1playerPartie(pseudo);
            Partie* p = builder->GetProduct();
            partie = p;
            break;
        }
        case 2:
        {
            cout<<"HUMAIN vs HUMAIN"<<std::endl;
            cout<<"Veuillez saisir le pseudo du joueur 1"<<std::endl;
            string pseudo1;
            cin>>pseudo1;
            std::cout<<"Veuillez saisir le pseudo du joueur 2"<<std::endl;
            string pseudo2;
            cin>>pseudo2;
            director->BuildNew2playerPartie(pseudo1, pseudo2);
            Partie* p = builder->GetProduct();
            partie = p;
            break;
        }
        default:
            throw PartieException("veuillez entrer un nombre valide");
            break;
        }
        delete director;
	}
}


void Controller::setJoueurCourant(int n) {
    //switch (joueurCourant) {
    //case 0:
    //    joueurCourant = 1;
    //    break;
    //case 1:
    //    joueurCourant = 0;
    //    break;
    //default:
    //    break;
    //}
}

void Controller::lancerPartie() {
    // TODO
}

void Controller::tour_suivant() {
    // TODO
}


///////////////////////// Actions d'un joueur /////////////////////////

void Controller::utiliserPrivilege(Plateau& plateau) {
    //if (nbPrivileges == 0) {
    //    throw JoueurException("Le joueur n'a pas de privilège");
    //}
    ///*if (plateau.getNbJtons()==0){
    //    throw JoueurException("Le plateau n'a pas de jetons");
    //}*/
    //const Privilege& privilege = supPrivilege();
    //plateau.poserPrivilege(privilege);
    //const Jeton& jetonSelec = strategy->choisirJeton(plateau);
    //addJeton(jetonSelec);

}

void Controller::remplirPlateau(Plateau& plateau, Sac& sac, Joueur& joueurAdverse) {
    //strategy->remplirPlateauStrat(plateau, sac);
    //if (nbPrivileges == 3) {
    //    std::cout << "Vous avez deja 3 privileges. Vous n'en recupererez donc pas plus !" << std::endl;
    //    return;
    //}
    //// Verifier s'il reste des privileges sur le plateau
    //if (!plateau.pivilegeDisponible()) {
    //    std::cout << "Il n'y a plus de privileges sur le plateau !\nLe joueur adverse perd donc un privilege..." << std::endl;
    //    const Privilege& privilege = joueurAdverse.supPrivilege(); // recuperation du privilege du joueur adverse
    //    addPrivilege(privilege); // ajout du privilege au joueur
    //    return;
    //}
    //// Cas standard
    //const Privilege& privilege = plateau.recupererPrivilege();
    //addPrivilege(privilege);
}

void Controller::recupererJetons(Plateau& plateau) {
    //std::cout << "Combien de jetons souhaitez-vous recuperer ? (1 a 3)" << std::endl;
    //unsigned int nbJetonsRecup;
    //std::cin >> nbJetonsRecup;
    //if (nbJetonsRecup > 3 || nbJetonsRecup < 1) {
    //    throw JoueurException("Le nombre de jetons est impossible");
    //}

    //std::cout << "Merci de selectionner des jetons adjacents en ligne, en colonne ou en diagonale." << std::endl;

    //std::vector<std::pair<unsigned int, unsigned int>> vecteurCoordonnees;
    //std::vector<const Jeton*> jetonsRecup;


    //for (unsigned int k = 0; k < nbJetonsRecup; k++) {
    //    unsigned int i, j;
    //    std::cout << "Entrez la valeur de i : ";
    //    std::cin >> i;
    //    std::cout << "Entrez la valeur de j : ";
    //    std::cin >> j;
    //    const Jeton& jeton = plateau.recupererJeton(i, j);
    //    // Ajout des coordonnees
    //    vecteurCoordonnees.push_back(std::make_pair(i, j));
    //    // Ajout du jeton
    //    jetonsRecup.push_back(&jeton);
    //}

    //// Verifier que les jetons sont adjacents
    //if (nbJetons > 1) {
    //    bool result1 = true;
    //    bool result2 = true;
    //    bool result3 = true;

    //    for (int i = 0; i < vecteurCoordonnees.size() - 1; i++) {
    //        if (vecteurCoordonnees[i].first != vecteurCoordonnees[i + 1].first) {
    //            result1 = false;
    //        }
    //    }
    //    for (int i = 0; i < vecteurCoordonnees.size() - 1; i++) {
    //        if (vecteurCoordonnees[i].second != vecteurCoordonnees[i + 1].second) {
    //            result2 = false;
    //        }
    //    }
    //    for (int i = 0; i < vecteurCoordonnees.size() - 1; i++) {
    //        // A modifier pour les diagonales
    //        if (vecteurCoordonnees[i].second != vecteurCoordonnees[i + 1].second - 1) {
    //            result3 = false;
    //        }
    //    }

    //    if (!result1 && !result2 && !result3) {
    //        throw JoueurException("Les jetons ne sont pas adjacents");
    //    }

    //}

    //// ajout des jetons dans la main du joueur
    //for (int i = 0; i < jetonsRecup.size(); i++) {
    //    addJeton(*jetonsRecup[i]);
    //}

}

void Controller::orReserverCarte(Pyramide& pyramide, Plateau& plateau) {
    //std::cout << "Volez-vous réserver une carte de la pyramide ou de la pioche de niveau i ? (0, 1, 2, 3)" << std::endl;
    //unsigned int choix;
    //std::cin >> choix;

    //if (choix == 0) {
    //    // Reservation de la carte
    //    std::cout << "Voici les cartes de la pyramide : " << std::endl;
    //    pyramide.afficherPyramide();
    //    std::cout << "Tapez le niveau de la carte que vous voulez réserver : " << std::endl;
    //    unsigned int niveau;
    //    std::cin >> niveau;
    //    std::cout << "Tapez le numero de la carte que vous voulez réserver : " << std::endl;
    //    int numCarte;
    //    std::cin >> numCarte;
    //    // Vérifications
    //    if (numCarte > pyramide.getNbCartesNiv(niveau)) {
    //        throw JoueurException("Le numéro de la carte est incorrect");
    //    }
    //    const Carte& carte = pyramide.reserverCarte(niveau, numCarte);
    //    addCarteReservee(carte);

    //    //pyramide.supprimerCarte(niveau, numCarte);

    //    // Recuperation d'un jeton or
    //    const Jeton& jeton = strategy->choisirJeton(plateau);
    //    if (jeton.getCouleur() != Couleur::OR) {
    //        throw JoueurException("Le jeton choisi n'est pas un jeton or");
    //    }
    //    addJeton(jeton);


    //}
    //else if (choix == 1 || choix == 2 || choix == 3) {
    //    // Reservation de la carte
    //    const Carte& carte = pyramide.ReserverCartePioche(choix);
    //    addCarteReservee(carte);

    //    // Recuperation d'un jeton or
    //    const Jeton& jeton = strategy->choisirJeton(plateau);
    //    if (jeton.getCouleur() != Couleur::OR) {
    //        throw JoueurException("Le jeton choisi n'est pas un jeton or");
    //    }
    //    addJeton(jeton);
    //}


}

void Controller::acheterCarteJoaillerie(Pyramide& pyramide) {
    //// Voir comment gérer les bonus
    //std::cout << "Tapez 1 pour acheter une carte Réservée.\nTapez 2 pour acheter une carte du plateau." << std::endl;
    //unsigned int choix;
    //std::cin >> choix;
    //// Achat carte reservee
    //if (choix == 1) {
    //    std::cout << "Voici les cartes réservées : " << std::endl;
    //    unsigned int i = 0;
    //    // Affichage de la réserve
    //    for (auto& cartesReservee : cartesReservees) {
    //        std::cout << "Numéro " << i << " : ";
    //        std::cout << cartesReservee;
    //        i++;
    //    }
    //    std::cout << "Tapez le numéro de la carte que vous voulez acheter : " << std::endl;
    //    unsigned int numCarte;
    //    std::cin >> numCarte;
    //    // Vérifications -> voir plus au niveau des jetons dans la main
    //    if (numCarte > cartesReservees.size()) {
    //        throw JoueurException("Le numéro de la carte est invalide.");
    //    }
    //    const Carte& carte = *cartesReservees[numCarte];
    //    if (carte.getNbPtsPrivilege() > ptsPrestige) {
    //        throw JoueurException("Vous n'avez pas assez de points de prestige pour acheter cette carte...");
    //    }
    //    addCarte(carte);
    //    supCarteReservee(carte);
    //}
    //// Achat carte du plateau
    //else if (choix == 2) {
    //    // Affichage des cartes
    //    std::cout << "Voici les cartes du plateau : " << std::endl;
    //    pyramide.afficherPyramide(); //Gerer l'affichage de la pyramide

    //    std::cout << "Tapez le niveau de la carte que vous voulez acheter : " << std::endl;
    //    unsigned int niveau;
    //    std::cin >> niveau;
    //    std::cout << "Tapez le numero de la carte que vous voulez acheter : " << std::endl;
    //    int numCarte;
    //    std::cin >> numCarte;

    //    // Vérifications
    //    if (numCarte > pyramide.getNbCartesNiv(niveau)) {
    //        throw JoueurException("Le numéro de la carte est incorrect");
    //    }

    //    const Carte& carte = pyramide.acheterCarte(niveau, numCarte);
    //    if (carte.getNbPtsPrivilege() > ptsPrestige) {
    //        throw JoueurException("Vous n'avez pas assez de points de prestige pour acheter cette carte");
    //    }
    //    addCarte(carte);
    //    //pyramide.supprimerCarte(niveau, numCarte);*/
    //}
    //else {
    //    throw JoueurException("Le choix est incorrect");
    //}
}
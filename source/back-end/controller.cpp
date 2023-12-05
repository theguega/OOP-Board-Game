#include "controller.hpp"

Controller::Controller() {
    //Choix du type de partie
    //Choix du type de partie
	Director* director = new Director();
	string statut_partie;
    std::cout << "\033[1;33mAncienne ou nouvelle partie ? (New/Old)\033[0m" << std::endl;
	std::cin >> statut_partie;

    //Si nouvelle partie
	if (statut_partie == "New") {
		NewPartieBuilder* builder = new NewPartieBuilder();
		director->set_builder(builder);
        std::cout << "\033[1;33mA combien de joueurs voulez-vous jouer ? (0, 1, 2)\033[0m" << std::endl;
		int nbJoueur;
		cin >> nbJoueur;
        switch (nbJoueur) {
        case 0:
        {   cout << "\nIA vs IA\n\n";
            director->BuildNewPartie("Alain Telligence", type::IA, "Al Gorythme", type::IA);
            Partie* p = builder->GetProduct();
            partie = p;
            break;
        }
        case 1:
        {
            cout<<"\nIA vs HUMAIN\n\n";
            std::cout << "\033[1;33mVeuillez saisir le pseudo du joueur\033[0m" << std::endl;
            string pseudo;
            std::cin>>pseudo;
            director->BuildNewPartie(pseudo, type::HUMAIN, "Al Gorythme", type::IA);
            Partie* p = builder->GetProduct();
            partie = p;
            break;
        }
        case 2:
        {
            cout<<"\nHUMAIN vs HUMAIN\n\n";
            std::cout << "\033[1;33mVeuillez saisir le pseudo du joueur 1\033[0m" << std::endl;
            string pseudo1;
            cin>>pseudo1;
            std::cout << "\033[1;33mVeuillez saisir le pseudo du joueur 2\033[0m" << std::endl;
            string pseudo2;
            cin>>pseudo2;
            director->BuildNewPartie(pseudo1, type::HUMAIN, pseudo2, type::HUMAIN);
            Partie* p = builder->GetProduct();
            partie = p;
            break;
        }
        default:
            throw SplendorException("veuillez entrer un nombre valide");
            break;
        }
        delete director;

	} else if (statut_partie == "Old") {
        LastPartieBuilder* builder = new LastPartieBuilder();
        director->set_builder(builder);
        director->BuildLastPartie();
        Partie* p = builder->GetProduct();
        partie = p;
        delete director;

        // restitution
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn3");
        db.setDatabaseName("data/save.sqlite");
        if (!db.open()) {
            std::cerr << "Impossible d'ouvrir la base de donnees 8: " << db.lastError().text().toStdString() << std::endl;
            return;
        }
        QSqlQuery query(db);
        if (!query.exec("SELECT * FROM infopartie")) {
            std::cerr << "Erreur de preparation de la requete 9: " << query.lastError().text().toStdString() << std::endl;
            db.close();
            return;
        }

        if (query.next()) {
            int joueur_c = query.value(1).toInt();
            if (joueur_c == 0)
                joueurCourant = partie->getJoueur1();
            else if (joueur_c == 1)
                joueurCourant = partie->getJoueur2();
            partie->setTour(query.value(2).toInt());
        }

        db.close();
    } else {
        throw SplendorException("Veuillez entrer un statut valide (New ou Old)");
    }
}

//surcharge du constructeur du controller pour la partie graphique
Controller::Controller(QString statut_partie, QString pseudo_j_1, type type_j_1, QString pseudo_j_2, type type_j_2){
    Director* director = new Director();

    //Si nouvelle partie
    if (statut_partie == "New") {
        NewPartieBuilder* builder = new NewPartieBuilder();
        director->set_builder(builder);
        director->BuildNewPartie(pseudo_j_1.toStdString(), type_j_1, pseudo_j_2.toStdString(), type_j_2);
        Partie* p = builder->GetProduct();
        partie = p;
        delete director;

    } else if (statut_partie == "Old") {
        LastPartieBuilder* builder = new LastPartieBuilder();
        director->set_builder(builder);
        director->BuildLastPartie();
        Partie* p = builder->GetProduct();
        partie = p;
        delete director;

        // restitution
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn3");
        db.setDatabaseName("data/save.sqlite");
        if (!db.open()) {
            std::cerr << "Impossible d'ouvrir la base de donnees 8: " << db.lastError().text().toStdString() << std::endl;
            return;
        }
        QSqlQuery query(db);
        if (!query.exec("SELECT * FROM infopartie")) {
            std::cerr << "Erreur de preparation de la requete 9: " << query.lastError().text().toStdString() << std::endl;
            db.close();
            return;
        }

        if (query.next()) {
            int joueur_c = query.value(1).toInt();
            if (joueur_c == 0)
                joueurCourant = partie->getJoueur1();
            else if (joueur_c == 1)
                joueurCourant = partie->getJoueur2();
            partie->setTour(query.value(2).toInt());
        }

        db.close();
    } else {
        throw SplendorException("Statut invalide");
    }
}








void Controller::setJoueurCourant(int n) {
    switch (n) {
    case 0:
        joueurCourant = partie->getJoueur1();
        break;
    case 1:
        joueurCourant = partie->getJoueur2();
        break;
    default:
        break;
    }

    if (joueurCourant->getTypeDeJoueur() == type::IA) 
        strategy_courante = &strategy_IA;
    else 
        strategy_courante = &strategy_Humain;
}

void Controller::changerJoueurCourant() {
    //changement du joueur courant
    if (joueurCourant == partie->getJoueur1())
        joueurCourant = partie->getJoueur2();
    else
        joueurCourant = partie->getJoueur1();

    if (joueurCourant->getTypeDeJoueur() == type::IA) 
        strategy_courante = &strategy_IA;
    else 
        strategy_courante = &strategy_Humain;
}








void Controller::lancerPartie() {
    // choix aleatoire entre 0 et 1 pour le choix du joueur qui commence
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);
    int rd_number = distrib(gen);
    setJoueurCourant(rd_number);
    switch (rd_number) {
    case 0:
        std::cout << "\033[1;36mC'est " << partie->getJoueur1()->getPseudo() << " qui commence, son adversaire recoit donc 1 privilege.\033[0m\n";
        partie->getJoueur2()->addPrivilege(partie->getEspaceJeux().getPlateau().recupererPrivilege());
        break;
    case 1:
        std::cout << "\033[1;36mC'est " << partie->getJoueur2()->getPseudo() << " qui commence, son adversaire recoit donc 1 privilege.\033[0m\n";
        partie->getJoueur1()->addPrivilege(partie->getEspaceJeux().getPlateau().recupererPrivilege());
        break;
    default:
        break;
    }
    partie->setTour(0);
    partie->getEspaceJeux().getPyramide().remplirPyramide();
    partie->getEspaceJeux().getPlateau().remplirPlateau(partie->getEspaceJeux().getSac());
    // TODO
}

void Controller::quitter() {
    std::string sauvegarde;
    std::cout<<"Vous avez decider de quitter la partie\n";
    std::cout<<"Voulez vous la sauvegarde ? (Oui, Non)\n";
    std::cin>>sauvegarde;
    if (sauvegarde=="OUI"||sauvegarde=="oui"||sauvegarde=="Oui")
        sauvegardePartie();
    else
        std::cout<<"tant pis...\n";
    return;
}

void Controller::jouer() {
    while (1) {
        // tour pour chacun des joueurs
        std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
        std::cout<< "Tour numero" << getPartie().getTour()+1 << endl;

        //correpond au tour de chaque joueur
        for (unsigned int i = 0; i < 2; i++) {
            std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------\n";
            std::cout<<"C'est a " << getJoueurCourant().getPseudo()<<" de jouer : \n\n";
            getJoueurCourant().afficherJoueur();

            unsigned int etat_tour = 0;
            while (etat_tour != 10) {

                // actions optionelles
                switch (etat_tour) {
                case 0: {
                    bool a_deja_utilise_privilege = false;
                    bool a_deja_rempli_plateau = false;
                    unsigned int etat_action = 0;
                    while (etat_action != 10) {
                        switch (etat_action)
                        {
                        case 0:{
                            //appel du menu de choix des actions
                            etat_action = choixActionsOptionelles();
                            break;}
                        case 1:{
                            try
                            {
                                //utilisation d'un privilege
                                if (a_deja_utilise_privilege)
                                    throw SplendorException("Vous avez deja utilise cette action");
                                utiliserPrivilege(getPartie().getEspaceJeux().getPlateau());
                                a_deja_utilise_privilege = true;
                                etat_action = 0;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        }
                        case 2:{
                            try
                            {
                                //remplissage du plateau
                                if (a_deja_rempli_plateau)
                                    throw SplendorException("Vous avez deja utilise cette action");
                                remplirPlateau(getPartie().getEspaceJeux().getPlateau(),getPartie().getEspaceJeux().getSac());
                                a_deja_rempli_plateau = true;
                                etat_action = 0;

                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        }
                        case 3:{
                            etat_tour = 1;
                            etat_action = 10;
                            break;
                        }

                        case 9:{
                            quitter();
                            return;
                        }

                        default:{
                            etat_action=0;
                            std::cout<<"Veuillez faire un choix correct !\n";
                            break;
                        }
                        }
                    }
                    break;
                }




                    //actions obligatoires :
                case 1:{
                    unsigned int etat_action = 0;
                    while (etat_action != 10) {
                        switch (etat_action)
                        {
                        case 0:
                            //menu de choix des actions obligatoires
                            etat_action = choixActionsObligatoires();
                            break;
                        case 1:
                            try
                            {
                                //recuperation de jetons
                                recupererJetons();
                                etat_action = 10;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        case 2:
                            try
                            {
                                //achat carte joaillerie
                                acheterCarteJoaillerie(getPartie().getEspaceJeux());
                                etat_action = 10;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        case 3:
                            try
                            {
                                //reservation carte
                                orReserverCarte(getPartie().getEspaceJeux().getPyramide(), getPartie().getEspaceJeux().getPlateau());
                                etat_action = 10;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        case 9:{
                            quitter();
                            return;

                        }
                        default:
                            etat_action=0;
                            std::cout<<"Veuillez faire un choix correct !\n";
                            break;
                        }
                        etat_tour = 2;
                    }
                    break;
                }



                    //verification fin de tour d'un joueur
                case 2:{
                    //achat obligatoire d'une carte noble si le joueur a 3 ou 6 pts de prestige
                    if (getJoueurCourant().getptsPrestige() >= 3 or getJoueurCourant().getptsPrestige() >= 6) {
                        //rajouter une verif si il y a bien des cartes nobles
                        acheterCarteNoble(getPartie().getEspaceJeux().getPyramide());
                    }

                    //simulation de victoire

                    /*if (getJoueurCourant().getNbJetons() >= 4) {
                        //affichage rigolo
                        const std::string message = "Le Joueur " + getJoueurCourant().getPseudo() +" a gagne !";
                        for (size_t j = 0; j<250; j++) {
                            for (std::size_t i = 0; i < message.size(); ++i) {
                                // Utilisation des codes ANSI pour le texte en gras et avec differentes couleurs
                                std::cout << "\033[1;3" << (i % 7) + 1 << "m" << message[i];
                            }
                            std::cout<<"\n";
                            for (std::size_t l = 0; l < j; ++l)
                                std::cout<<" ";
                        };
                        // Reinitialisation du style apres la derniere lettre
                        std::cout << "\033[0m\n";

                        etat_tour = 3;
                        break;
                    }*/
                    verifJetonSupDix();
                    //fin du tour du joueur, on passe au joueur suivant
                    changerJoueurCourant();
                    etat_tour = 10;
                    break;
                }
                case 3:{
                    std::cout << "Fin de la partie !\n";
                    return;
                    break;
                }
                default:{
                    break;
                }
                }
            }
            //fin du tour :
            getPartie().incrementeTour();
        }
    }
}


///////////////////////// Actions d'un joueur /////////////////////////


//Menu choix des actions
unsigned int Controller::choixActionsObligatoires() {
    std::cout << "\033[1mActions obligatoires:\033[0m\n";
    std::cout << "1. Recuperer des jetons\n";
    std:: cout << "2. Acheter une carte joaillerie\n";
    std::cout << "3. Reserver une carte\n";
    std::cout << "9. Quitter le jeu\n";
    std::cout << "Votre choix (1/2/3/9):" << std::endl;

    return strategy_courante->choixMenu();;
}

unsigned int Controller::choixActionsOptionelles() {
    std::cout << "\033[1mActions optionnelles:\033[0m\n";
    std::cout << "1. Utiliser un privilege\n";
    std:: cout << "2. Remplir le plateau\n";
    std::cout << "3. Ne plus faire d'actions optionnelles\n";
    std::cout << "9. Quitter le jeu\n";
    std::cout << "Votre choix (1/2/3/9):" << std::endl;

    return strategy_courante->choixMenu();;
}


// Utiliser un privilege
void Controller::utiliserPrivilege(Plateau& plateau){
    //on verifie d'abord si le joueur a un/des privilege
    verifPrivileges();

    std::cout << "Combien de privileges voulez vous utiliser ?\n";
    unsigned int priv = strategy_courante->choix_min_max(1,3);
    if (priv>joueurCourant->getNbPrivileges())
        throw SplendorException("Vous n'avez pas assez de privilege");

    //on recupere autant de jetons que de privilege
    for (size_t k=0; k<priv;k++) {
        std::cout<<"Utiliser un privilege permet de recup un jeton de couleur ou perle de votre choix (i,j):\n";
        std::cout<<plateau<<"\n";

        unsigned int i = strategy_courante->choix_min_max(1,5)-1;
        unsigned int j = strategy_courante->choix_min_max(1,5)-1;

        if(plateau.caseVide(i, j))
            throw SplendorException("La case est vide");
        if(plateau.caseOr(i, j))
            throw SplendorException("Vous ne pouvez pas prendre de jeton Or avec un privilege");

        const Jeton& jetonSelec = plateau.recupererJeton(i, j);
        joueurCourant->addJeton(jetonSelec);
        //on repose le privilege
        const Privilege& privilege = joueurCourant->supPrivilege();
        plateau.poserPrivilege(privilege);
    }

    std::cout << "Voici le nouveau plateau (apres recuperation) \n" << getPartie().getEspaceJeux().getPlateau();
                     joueurCourant->afficherJoueur();
    return;
}

void Controller::remplirPlateau(Plateau& plateau, Sac& sac){
    verifSacvide();

    std::cout<<"Le joueur rempli le plateau :\n"<<plateau<<endl;

    //on donne un privilege au joueur adverse
    donPrivilegeAdverse();

    plateau.remplirPlateau(sac);
    std::cout<<"Nouveau plateau : \n"<<plateau;

    return;
}

void Controller::donPrivilegeAdverse() {
    if (partie->getEspaceJeux().getPlateau().getNbPrivileges()==0){
        //si il n'y a plus de privileges sur le plateau
        if(getJoueurAdverse().getNbPrivileges()!=3) {
            //si il n'a pas déjà les 3 privilèges, il prends celui du joueur actuel, sinon il n'en recupere pas
            getJoueurAdverse().addPrivilege(joueurCourant->supPrivilege());
        }
    } else {
        //si il y a un jetons sur le plateau, le joueur le recupere
        getJoueurAdverse().addPrivilege(partie->getEspaceJeux().getPlateau().recupererPrivilege());
    }
    return;
}




// Recuperer des jetons
void Controller::recupererJetons(){
    std::cout<<"Vous avez decider de recuperer des jetons sur le plateau :\n"<<getPlateau();

    // Recuperation des jetons 1 2 ou 3 jetons en fonction de la strategy

    std::cout << "Combien de jetons souhaitez-vous recuperer ? (1,2,3) " << std::endl;
    unsigned int nbJetons = strategy_courante->choix_min_max(1,3);

    std::cout << "Merci de selectionner des jetons adjacents en ligne, en colonne ou en diagonale.\n\n";

    std::vector<std::pair<int, int>> vecteurCoordonnees;
    std::cout<<"Vous allez rentrer les coordonnees des jetons : \n";
    // Recup des coordonnees des jetons
    for (unsigned int k = 0; k < nbJetons; k++){

        // Ajout des coordonnees
        std::cout<<"Jetons numero "<<k+1<<" : \n";

        std::cout << "Numero de ligne (1,2,3,4,5) : \n";
        int indice_i = strategy_courante->choix_min_max(1, 5);
        std::cout << "Numero de colonne (1,2,3,4,5) : \n";
        int indice_j = strategy_courante->choix_min_max(1, 5);
        vecteurCoordonnees.emplace_back(std::make_pair(indice_i-1, indice_j-1));
    }

    // Verifier que les jetons sont adjacents
    if (nbJetons > 1) {
        bool result1 = true;
        bool result2 = true;
        bool result3 = false; // Diago 1
        bool result4 = false; // Diago 2

        // Verif que les jetons sont adjacents en ligne
        for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            if (vecteurCoordonnees[i].first != vecteurCoordonnees[i + 1].first) {
                result1 = false;
            }
        }
        // verif qu'ils ne sont pas distants de + d'une case
        if(result1){
            for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
                if (abs(vecteurCoordonnees[i].second - vecteurCoordonnees[i + 1].second) != 1)
                    result1 = false;
            }
        }
        // Verif que les jetons sont adjacents en colonne
        for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            if (vecteurCoordonnees[i].second != vecteurCoordonnees[i + 1].second) {
                result2 = false;
            }
        }
        // verif qu'ils ne sont pas distants de + d'une case
        if(result2){
            for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
                if (abs(vecteurCoordonnees[i].first - vecteurCoordonnees[i + 1].first) != 1)
                    result2 = false;
            }
        }
        // Verif que les jetons sont adjacents en diagonale

        // Fonction de comparaison pour trier en fonction du premier element de la paire
        auto comparaison = [](const auto& a, const auto& b) {
            return a.first < b.first;
        };
        std::sort(vecteurCoordonnees.begin(), vecteurCoordonnees.end(), comparaison);


        // il manque la verification que les jetons ne sont pas distants de + d'une case
        for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            // premiere diagonale
            if ((vecteurCoordonnees[i].first+1 == vecteurCoordonnees[i + 1].first) && (vecteurCoordonnees[i].second-1 == vecteurCoordonnees[i + 1].second)) {
                result3 = true;
            }
        }
        for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            // seconde diagonale
            if ((vecteurCoordonnees[i].first+1 == vecteurCoordonnees[i + 1].first) && (vecteurCoordonnees[i].second+1 == vecteurCoordonnees[i + 1].second)) {
                result4 = true;
            }
        }

        if (!result1 && !result2 && !result3 && !result4) {
            throw SplendorException("\nLes jetons ne sont pas adjacents");
        }
    }


    // Recup des jetons
    std::vector<const Jeton*> jetonsRecup;
    for (unsigned int k = 0; k < nbJetons; k++){
        if (getPlateau().caseVide(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second) || getPlateau().caseOr(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second))
            throw SplendorException("Il y a une case vide ou un jeton Or dans votre selection");
    }
    for (unsigned int k = 0; k < nbJetons; k++){
        jetonsRecup.push_back(&getPlateau().recupererJeton(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second));
    }

    // ajout des jetons dans la main du joueur
    for (auto & i : jetonsRecup){
        joueurCourant->addJeton(*i);
    }

    std::cout<<"Voici le nouveau plateau (apres recuperation) \n" << getPlateau();
    std::cout<<"Voici l'etat du joueur apres recuperation :\n" ;
    joueurCourant->afficherJoueur();
    return;
}

//TODO
void Controller::acheterCarteJoaillerie (EspaceJeux& espaceJeux){
    unsigned int choix = strategy_courante->choixAchat();


    // Achat carte reservee
    if (choix == 1){
        std::cout << "Voici les cartes reservees : " << std::endl;
        unsigned int i = 0;
        // Affichage de la reserve
        for (const auto& couleurEtCartes : joueurCourant->cartesReservees) {
            const std::vector<const Carte*>& cartes = couleurEtCartes.second;
            for (const Carte* carte : cartes) {
                std::cout << "Numero "<<++i<<" : \n"<< *carte << std::endl;
            }
        }

        std::pair< Couleur, unsigned int> carteDescr = strategy_courante->achatReserve(joueurCourant->cartesReservees.size());
        if(carteDescr.second >= joueurCourant->cartesReservees[carteDescr.first].size() || joueurCourant->cartesReservees[carteDescr.first].size()==0)
            throw SplendorException("vous n'avez pas cette carte dans votre reserve ou la reserve est vide");
        else{
            const Carte& carte = *(joueurCourant->cartesReservees[carteDescr.first][carteDescr.second]);

            if (!verifAchatCarte(carte, espaceJeux)) {
                throw SplendorException("Vous n'avez pas assez de gemmes pour acheter cette carte...");
            }
            joueurCourant->addCarte(carte);
            // rajout des couronnes
            joueurCourant->nbCouronnes += carte.getNbCouronnes();
            // Rajout du bonus dans le joueur
            joueurCourant->bonus[carte.getBonus().getCouleur()] += carte.getBonus().getNbBonus();
            joueurCourant->supCarteReservee(carte);
        }
    }
    // Achat carte du plateau
    else if (choix == 2){
        // Affichage des cartes
        std::cout << "Voici les cartes du plateau : " << std::endl;
        espaceJeux.getPyramide().afficherPyramide(); //Gerer l'affichage de la pyramide

        std::pair<unsigned int, unsigned int> carteDescr = strategy_courante->reservationCarte(espaceJeux.getPyramide());

        const Carte& carte = espaceJeux.getPyramide().acheterCarte(carteDescr.first, carteDescr.second);
        if (!verifAchatCarte(carte, espaceJeux)){
            throw SplendorException("Vous n'avez pas assez de gemmes pour acheter cette carte");
        }
        joueurCourant->addCarte(carte);
        // rajout des couronnes
        joueurCourant->nbCouronnes += carte.getNbCouronnes();
        // Rajout du bonus dans le joueur
        joueurCourant->bonus[carte.getBonus().getCouleur()] += carte.getBonus().getNbBonus();
    }
    else {
        std::cout<<"Le choix est incorrect\n"<<std::endl;
    }
}

void Controller::acheterCarteNoble (Pyramide& pyramide){
    std::cout<<"Vous devez achter une carte noble car vous avez 3 ou 6 pts de prestige\n";
    // affichage cartes nobles
    pyramide.afficherNobles();

    unsigned int i = strategy_courante->choix_min_max(0,pyramide.getNbCartesNiv(4));

    const Carte& carte = pyramide.acheterCarte(4, i);

    joueurCourant->addCarteNoble(carte);
}

void Controller::orReserverCarte (Pyramide& pyramide, Plateau& plateau){
    verifOrSurPlateau();
    cout << "Commencez par choisir un jeton Or : \n";
    cout <<  getPlateau();
    cout << "Choisissez une ligne : \n";
    unsigned int coord_ligne = strategy_courante->choix_min_max(1, 5);
    cout << "Choisissez une colonne : \n";
    unsigned int coord_col = strategy_courante->choix_min_max(1, 5);
    while(getPlateau().caseVide(coord_ligne-1, coord_col-1) || !getPlateau().caseOr(coord_ligne-1, coord_col-1)){
        cout << "La case est vide ou ce n'est pas un jeton Or\n";
        cout << "Choisissez une ligne : \n";
        coord_ligne = strategy_courante->choix_min_max(1, 5);
        cout << "Choisissez une colonne : \n";
        coord_col = strategy_courante->choix_min_max(1, 5);
    }

    cout << "Voulez-vous reserver une carte de la pyramide (0) ou celle d'une pioche (1, 2, 3) ?\n";
    unsigned int choix = strategy_courante->choix_min_max(0, 3);

    if (choix == 0){
        // Reservation de la carte
        std::cout << "Voici les cartes de la pyramide : " << std::endl;
        getPyramide().afficherPyramide(); //Gerer l'affichage de la pyramide

        cout << "rentrez le niveau de la carte souhaitee : \n";
        unsigned int niveau = strategy_courante->choix_min_max(1, 3);
        cout << "rentrez le numero de la carte souhaitee : \n";
        unsigned int num_carte = strategy_courante->choix_min_max(1, getPyramide().getNbCartesNiv(niveau-1));

        const Carte& carte = pyramide.acheterCarte(niveau, num_carte);
        joueurCourant->addCarteReservee(carte);

        const Jeton& jeton = plateau.recupererJeton(coord_ligne-1, coord_col-1);
        joueurCourant->addJeton(jeton);
    }
    else if (choix == 1 || choix == 2 || choix == 3){
        // Reservation de la carte
        const Carte& carte = pyramide.ReserverCartePioche(choix);
        joueurCourant->addCarteReservee(carte);

        const Jeton& jeton = plateau.recupererJeton(coord_ligne-1, coord_col-1);
        joueurCourant->addJeton(jeton);
    }
    cout << "Etat du joueur apres l'action : \n";
    joueurCourant->afficherJoueur();
}

///////////////////////////////////////////////////////////////////////////////////
///////// Méthodes qui restent à implementer de manière fonctionnelle /////////////
///////////////////////////////////////////////////////////////////////////////////




bool Controller::verifAchatCarte(const Carte& carte, EspaceJeux& espaceJeux) {
    // 1 recuperer les points necessaires pour acheter la carte
    // 2 voir le nb de jetons par couleur
    // 3 ajouter les bonus
    // 4 voir si le joueur a assez de points pour acheter la carte
    // 5 si pas assez essayer avec les jetons or

    // recup des points necessaires pour acheter la carte
    unsigned int needBlanc =  carte.getPrix().getBlanc() ;
    unsigned int needBleu =  carte.getPrix().getBleu();
    unsigned int needVert =  carte.getPrix().getVert();
    unsigned int needRouge =  carte.getPrix().getRouge();
    unsigned int needNoir =  carte.getPrix().getNoir();
    unsigned int needPerle = carte.getPrix().getPerle();

    // recup des jetons du joueur
    // Map des bonus associes a chaque couleur

// Map des bonus associes a chaque couleur


    unsigned int nbBlanc = 0;
    auto itBlanc = joueurCourant->jetons.find(Couleur::BLANC);
    if (itBlanc != joueurCourant->jetons.end()) {
        nbBlanc = itBlanc->second.size();

        auto itBonusBlanc = joueurCourant->bonus.find(Couleur::BLANC);
        if (itBonusBlanc != joueurCourant->bonus.end()) {
            nbBlanc += itBonusBlanc->second;
        }
    }

    unsigned int nbBleu = 0;
    auto itBleu = joueurCourant->jetons.find(Couleur::BLEU);
    if (itBleu != joueurCourant->jetons.end()) {
        nbBleu = itBleu->second.size();

        auto itBonusBleu = joueurCourant->bonus.find(Couleur::BLEU);
        if (itBonusBleu != joueurCourant->bonus.end()) {
            nbBleu += itBonusBleu->second;
        }
    }

    unsigned int nbVert = 0;
    auto itVert = joueurCourant->jetons.find(Couleur::VERT);
    if (itVert != joueurCourant->jetons.end()) {
        nbVert = itVert->second.size();

        auto itBonusVert = joueurCourant->bonus.find(Couleur::VERT);
        if (itBonusVert != joueurCourant->bonus.end()) {
            nbVert += itBonusVert->second;
        }
    }

    unsigned int nbRouge = 0;
    auto itRouge = joueurCourant->jetons.find(Couleur::ROUGE);
    if (itRouge != joueurCourant->jetons.end()) {
        nbRouge = itRouge->second.size();

        auto itBonusRouge = joueurCourant->bonus.find(Couleur::ROUGE);
        if (itBonusRouge != joueurCourant->bonus.end()) {
            nbRouge += itBonusRouge->second;
        }
    }

    unsigned int nbNoir = 0;
    auto itNoir = joueurCourant->jetons.find(Couleur::NOIR);
    if (itNoir != joueurCourant->jetons.end()) {
        nbNoir = itNoir->second.size();

        auto itBonusNoir = joueurCourant->bonus.find(Couleur::NOIR);
        if (itBonusNoir != joueurCourant->bonus.end()) {
            nbNoir += itBonusNoir->second;
        }
    }

    unsigned int nbPerle = 0;
    auto itPerle = joueurCourant->jetons.find(Couleur::PERLE);
    if (itPerle != joueurCourant->jetons.end()) {
        nbPerle = itPerle->second.size();

    }

    unsigned int nbOr = 0;
    auto itOr = joueurCourant->jetons.find(Couleur::OR);
    if (itOr != joueurCourant->jetons.end()) {
        nbOr = itOr->second.size();

    }

    if (nbBlanc >= needBlanc && nbBleu >= needBleu && nbVert >= needVert &&
        nbRouge >= needRouge && nbNoir >= needNoir && nbPerle >= needPerle) {

        // On supprime les jetons utilises
        joueurCourant->supJetonNb(needBlanc, Couleur::BLANC, espaceJeux);
        joueurCourant->supJetonNb(needBleu, Couleur::BLEU, espaceJeux);
        joueurCourant->supJetonNb(needVert, Couleur::VERT, espaceJeux);
        joueurCourant->supJetonNb(needRouge, Couleur::ROUGE, espaceJeux);
        joueurCourant->supJetonNb(needNoir, Couleur::NOIR, espaceJeux);
        joueurCourant->supJetonNb(needPerle, Couleur::PERLE, espaceJeux);


        return true;  // Le joueur a suffisamment de jetons pour acheter la carte
    }

    // 5. Si pas assez, essayer avec les jetons or
    unsigned int jetonsOrUtilises = 0;

    // Fonction pour ajouter des jetons or a une couleur donnee
    auto ajouterJetonsOr = [&jetonsOrUtilises, &nbOr](unsigned int& nbCouleur, unsigned int& besoin) {
        while (nbOr > 0 && besoin > nbCouleur) {
            // Utiliser un jeton or pour completer le besoin
            nbOr--;
            //nbCouleur++;
            jetonsOrUtilises++;
            besoin--;
        }
    };

    ajouterJetonsOr(nbBlanc, needBlanc);
    ajouterJetonsOr(nbBleu, needBleu);
    ajouterJetonsOr(nbVert, needVert);
    ajouterJetonsOr(nbRouge, needRouge);
    ajouterJetonsOr(nbNoir, needNoir);
    ajouterJetonsOr(nbPerle, needPerle);

    // Verifier a nouveau si le joueur a maintenant assez de points pour acheter la carte
    if (needBlanc <= nbBlanc && needBleu <= nbBleu && needVert <= nbVert &&
        needRouge <= nbRouge && needNoir <= nbNoir && needPerle <= nbPerle) {
        std::cout << "Carte achetable avec " << jetonsOrUtilises << " jeton(s) or utilise(s)." << std::endl;

        joueurCourant->supJetonNb(needBlanc, Couleur::BLANC, espaceJeux);
        joueurCourant->supJetonNb(needBleu, Couleur::BLEU, espaceJeux);
        joueurCourant->supJetonNb(needVert, Couleur::VERT, espaceJeux);
        joueurCourant->supJetonNb(needRouge, Couleur::ROUGE, espaceJeux);
        joueurCourant->supJetonNb(needNoir, Couleur::NOIR, espaceJeux);
        joueurCourant->supJetonNb(needPerle, Couleur::PERLE, espaceJeux);
        joueurCourant->supJetonNb(jetonsOrUtilises, Couleur::OR, espaceJeux);

        return true;
    } else {
        std::cout << "Le joueur n'a pas assez de jetons pour acheter la carte." << std::endl;
        return false;
    }
}

///////////////////////// Verifications /////////////////////////

void Controller::verifPrivileges(){
    if (joueurCourant->privileges.empty())
        throw SplendorException("\nLe joueur courant n'a pas de privileges");
}

void Controller::verifPlateauvide(){
    if (partie->getEspaceJeux().getPlateau().estVide()){
        throw SplendorException("\nIl n'y a aucun jeton a recuperer sur le plateau");
    }
}

void Controller::verifSacvide(){
    if (partie->getEspaceJeux().getSac().estVide()){
        throw SplendorException("\nLe sac de jetons est vide");
    }
}

void Controller::verifOrSurPlateau(){
    if(!getPlateau().contientOr())
        throw SplendorException("\nLe plateau ne contient aucun jeton Or, vous ne pouvez pas reserver de carte\n");
}

void Controller::verifJetonSupDix(){
    cout << "Verification que le joueur courant n'a pas plus de 10 jetons dans sa main\n";
    while(joueurCourant->getNbJetons() > 10){
        cout << "Vous devez reposer des jetons dans le sac : \n";
        cout << "Choisissez une couleur parmi : \n";
        cout << "1 - Blanc\n2 - Bleu\n3 - Vert\n4 - Rouge\n5 - Noir\n6 - Perle\n7 - Or\n";
        unsigned int choix = strategy_courante->choix_min_max(1, 7);
        Couleur choix_c = static_cast<Couleur>(choix-1);
        if (joueurCourant->getNbJetons(choix_c) == 0)
            cout << "Vous n'avez pas de jetons de cette couleur !\n";
        else{
            joueurCourant->supJetonNb(1, choix_c, getEspaceJeux());
        }
    }
}


///////////////////////// Sauvegarde /////////////////////////

void Controller::sauvegardePartie() {
   //Cette fonction aura pour objectif de push toutes les donnees importantes de la partie dans la base de donnee
   //Afin de pouvoir reprendre la partie plus tard
   //Pour cela, il faudra creer une base de donnee avec les tables suivantes :
   // joueur1, joueur2, plateau, infopartie, pyramide

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn1");
    db.setDatabaseName("data/save.sqlite");
    if (!db.open()) {
        std::cerr << "Erreur lors de la connexion a la base de donnee" << std::endl;
        return;
    }

    // Nettoyage de l'ancienne sauvegarde
    QSqlQuery query(db);
    QStringList tables = db.tables();
    foreach (const QString &table, tables) {
            if (!query.exec("DELETE FROM " + table)) {
                qWarning() << "echec de la suppression des donnees de la table " << table << " : " << query.lastError().text();
            }
        }

    for (size_t i = 0; i < 2; i++) {
        // Infos du joueur
        QString sql = "INSERT INTO joueur (id, pseudo, type_joueur, privileges) VALUES (" + QString::number(i + 1) + ", '" + QString::fromStdString(getPartie().getJoueur(i)->getPseudo()) + "', '" + QString::fromStdString(toStringType(getPartie().getJoueur(i)->getTypeDeJoueur())) + "', " + QString::number(getPartie().getJoueur(i)->getNbPrivileges()) + ");";
        if (!query.exec(sql)) {
            std::cerr << "Erreur lors de la sauvegarde du joueur " << std::endl;
            db.close();
            return;
        }
        // Jetons (toutes les couleurs sauf indt)
        for (Couleur c : Couleurs) {
            if (c != Couleur::INDT) {
                for (size_t j = 0; j < getPartie().getJoueur(i)->getNbJetons(c); j++) {
                    sql = "INSERT INTO jeton (id_joueur, couleur) VALUES (" + QString::number(i + 1) + ", '" + QString::fromStdString(toStringCouleur(c)) + "');";
                    if (!query.exec(sql)) {
                        std::cerr << "Erreur lors de la sauvegarde du jeton " << std::endl;
                        db.close();
                        return;
                    }
                }
            }
        }
        // Cartes (toutes les couleurs sauf ind et or)
        for (Couleur c : Couleurs) {
            if (c != Couleur::INDT && c != Couleur::OR) {
                for (size_t j = 0; j < getPartie().getJoueur(i)->getNbCartes(c); j++) {
                    sql = "INSERT INTO carte (id_joueur, id_carte, noble, reservee) VALUES (" + QString::number(i + 1) + ", " + QString::number(getPartie().getJoueur(i)->getCarte(c, j).getId()) + ",0,0);";
                    if (!query.exec(sql)) {
                        std::cerr << "Erreur lors de la sauvegarde de la carte " << std::endl;
                        db.close();
                        return;
                    }
                }
            }
        }
        // Cartes nobles
        for (size_t j = 0; j < getPartie().getJoueur(i)->getNbCartesNobles(); j++) {
            sql = "INSERT INTO carte (id_joueur, id_carte, noble, reservee) VALUES (" + QString::number(i + 1) + ", " + QString::number(getPartie().getJoueur(i)->getCarteNoble(j).getId()) + ",1,0);";
            if (!query.exec(sql)) {
                std::cerr << "Erreur lors de la sauvegarde de la carte" << std::endl;
                db.close();
                return;
            }
        }
        // Cartes reservees (toutes les couleurs sauf ind et or)
        for (Couleur c : Couleurs) {
            if (c != Couleur::INDT && c != Couleur::OR) {
                for (size_t j = 0; j < getPartie().getJoueur(i)->getNbCartesReservees(c); j++) {
                    sql = "INSERT INTO carte (id_joueur, id_carte, noble, reservee) VALUES (" + QString::number(i + 1) + ", " + QString::number(getPartie().getJoueur(i)->getCarteReservee(c, j).getId()) + ", " + QString::fromStdString(TypeCartetoString(getPartie().getJoueur(i)->getCarteReservee(c, j).getType())) + ",1);";
                    if (!query.exec(sql)) {
                        std::cerr << "Erreur lors de la sauvegarde de la carte " << std::endl;
                        db.close();
                        return;
                    }
                }
            }
        }
    }

    // Sauvegarde plateau
    Plateau& plateau = getPartie().getEspaceJeux().getPlateau();
    for (size_t i = 0; i < plateau.getLargeurMatrice(); i++) {
        for (size_t j = 0; j < plateau.getLargeurMatrice(); j++) {
            if (plateau.getJeton(i, j) != nullptr) {
                QString sql = "INSERT INTO plateau (i, j, couleur) VALUES (" + QString::number(i) + ", " + QString::number(j) + ", '" + QString::fromStdString(toStringCouleur(plateau.getJeton(i, j)->getCouleur())) + "');";
                if (!query.exec(sql)) {
                    std::cerr << "Erreur lors de la sauvegarde du plateau" << std::endl;
                    db.close();
                    return;
                }
            }
        }
    }

   // Sauvegarde de la pyramide
    Pyramide& pyramide = getPartie().getEspaceJeux().getPyramide();
    for (int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < pyramide.getNbCartesNiv(i); j++) {
            const Carte* carte = pyramide.getCarte(i, j);
            QString sql = "INSERT INTO pyramide (i, j, id) VALUES (" + QString::number(i) + ", " + QString::number(j) + ", " + QString::number(carte->getId()) + ");";
            if (!query.exec(sql)) {
                std::cerr << "Erreur lors de la sauvegarde de la pyramide" << std::endl;
                db.close();
                return;
            }
        }
    }



   //Sauvegarde des infos de la partie
    int joueurCourant = 0;
    if (getPartie().getJoueur2() == this->joueurCourant) {
        joueurCourant = 1;
    }
    int tour = getPartie().getTour();
    QString sql = "INSERT INTO infopartie (tour, joueurCourant) VALUES (" + QString::number(tour) + ", " + QString::number(joueurCourant) + ");";
    if (!query.exec(sql)) {
        std::cerr << "Erreur lors de la sauvegarde des infos de la partie" << std::endl;
        db.close();
        return;
    }

    // Fermeture de la base de donnee
    db.close();
}


//sauvegarde du score des joueurs a la fin de la partie
void Controller::enregisterScore() {
   //a la fin d'une partie il faut enregistrer le score des joueurs dans la base de donnee
   //on regarde si il existe deja et on lui ajoute une victoire ou une defaite
   //sinon on le cree et on lui ajoute une victoire ou une defaite

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn4");
    db.setDatabaseName("data/score.sqlite");
    if (!db.open()) {
        std::cerr << "Erreur lors de la connexion a la base de donnee" << std::endl;
        return;
    }

    QSqlQuery query(db);
    for (int i = 0; i < 2; i++) {
        // On regarde si le joueur existe deja
        QString sql = "SELECT * FROM score WHERE pseudo = '" + QString::fromStdString(getPartie().getJoueur(i)->getPseudo()) + "';";
        if (!query.exec(sql)) {
            std::cerr << "Erreur lors de la recherche du joueur dans la base de donnee" << std::endl;
            db.close();
            return;
        }

        if (query.next()) {
            // Le joueur existe deja
            // On recupere son nombre de victoires et de defaites
            int nbVictoire = query.value(2).toInt();
            int nbDefaite = query.value(3).toInt();
            // On met a jour son nombre de victoires ou de defaites
            if (getPartie().getJoueur(i)->estGagnant()) {
                nbVictoire++;
            } else {
                nbDefaite++;
            }
            // On met a jour le score du joueur
            sql = "UPDATE score SET nbVictoire = " + QString::number(nbVictoire) + ", nbDefaite = " + QString::number(nbDefaite) + " WHERE pseudo = '" + QString::fromStdString(getPartie().getJoueur(i)->getPseudo()) + "';";
            std::cout << sql.toStdString() << std::endl;
            if (!query.exec(sql)) {
                std::cerr << "Erreur lors de la mise a jour du score du joueur" << std::endl;
                db.close();
            }
        } else {
            // Sinon, on ajoute le joueur dans la base de donnee avec le bon score
            int nbVictoire = 0;
            int nbDefaite = 0;
            if (getPartie().getJoueur(i)->estGagnant()) {
                nbVictoire++;
            } else {
                nbDefaite++;
            }
            sql = "INSERT INTO score (pseudo, nbVictoire, nbDefaite) VALUES ('" + QString::fromStdString(getPartie().getJoueur(i)->getPseudo()) + "', " + QString::number(nbVictoire) + ", " + QString::number(nbDefaite) + ");";
            std::cout << sql.toStdString() << std::endl;
            if (!query.exec(sql)) {
                std::cerr << "Erreur lors de l'ajout du joueur dans la base de donnee" << std::endl;
                db.close();
            }
        }
    }

    db.close();
}

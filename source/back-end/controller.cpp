#include "controller.hpp"
#include <QDebug>




Controller::Controller() {
    //Choix du type de partie
    Director* director = new Director();

    qDebug() << "\033[1;33mAncienne ou nouvelle partie ? (New/Old)\033[0m\n";
    string statut_partie;
    cin>>statut_partie;

   //Si nouvelle partie
    if (statut_partie == "New") {
        stat_partie="New";
        NewPartieBuilder* builder = new NewPartieBuilder();
        director->set_builder(builder);
        qDebug() << "\033[1;33mA combien de joueurs voulez-vous jouer ? (0, 1, 2)\033[0m\n";

        int nbJoueur;
        cin >> nbJoueur;
        switch (nbJoueur) {
        case 0:
        {   qDebug()  << "\nIA vs IA\n\n";
            director->BuildNewPartie("Alain Telligence", type::IA, "Al Gorythme", type::IA);
            Partie* p = builder->GetProduct();
            partie = p;
            break;
        }
        case 1:
        {
            qDebug() <<"\nIA vs HUMAIN\n\n";
            qDebug() << "\033[1;33mVeuillez saisir le pseudo du joueur\033[0m\n";

            string pseudo;
            std::cin>>pseudo;
            director->BuildNewPartie(pseudo, type::HUMAIN, "Al Gorythme", type::IA);
            Partie* p = builder->GetProduct();
            partie = p;
            break;
        }
        case 2:
        {
            qDebug() <<"\nHUMAIN vs HUMAIN\n\n";
            qDebug() << "\033[1;33mVeuillez saisir le pseudo du joueur 1\033[0m\n";

            string pseudo1;
            cin>>pseudo1;
            qDebug() << "\033[1;33mVeuillez saisir le pseudo du joueur 2\033[0m\n";

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

    }
    // si ancienne partie
    else if (statut_partie == "Old") {
        stat_partie="Old";
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
            qCritical() << "Impossible d'ouvrir la base de donnees 8: " << db.lastError().text().toStdString() << '\n';
            return;
        }
        QSqlQuery query(db);
        if (!query.exec("SELECT * FROM infopartie")) {
            qCritical() << "Erreur de preparation de la requete 9: " << query.lastError().text().toStdString() << '\n';
            db.close();
            return;
        }

        if (query.next()) {
            int joueur_c = query.value(1).toInt();
            if (joueur_c == 0)
                setJoueurCourant(0);
            else if (joueur_c == 1)
                setJoueurCourant(1);
        }
        db.close();
    } else {
        throw SplendorException("Veuillez entrer un statut valide (New ou Old)");
    }
}



//Surcharge du constructeur du controller pour la partie graphique
Controller::Controller(QString statut_partie, QString pseudo_j_1, type type_j_1, QString pseudo_j_2, type type_j_2){
    Director* director = new Director();

    //Si nouvelle partie
    if (statut_partie == "New") {
        stat_partie="New";
        NewPartieBuilder* builder = new NewPartieBuilder();
        director->set_builder(builder);
        director->BuildNewPartie(pseudo_j_1.toStdString(), type_j_1, pseudo_j_2.toStdString(), type_j_2);
        Partie* p = builder->GetProduct();
        partie = p;
        delete director;

    } else if (statut_partie == "Old") {
        stat_partie="Old";
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
            qCritical() << "Impossible d'ouvrir la base de donnees 8: " << db.lastError().text().toStdString() << '\n';
            return;
        }
        QSqlQuery query(db);
        if (!query.exec("SELECT * FROM infopartie")) {
            qCritical() << "Erreur de preparation de la requete 9: " << query.lastError().text().toStdString() << '\n';
            db.close();
            return;
        }

        if (query.next()) {
            int joueur_c = query.value(1).toInt();
            if (joueur_c == 0)
                setJoueurCourant(0);
            else if (joueur_c == 1)
                setJoueurCourant(1);
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

    if (joueurCourant->getTypeDeJoueur() == type::IA){

        strategy_courante = &strategy_IA;
    }
    else
        strategy_courante = &strategy_Humain;
}




void Controller::changerJoueurCourant() {
    //changement du joueur courant
    if(!nouveau_tour){
        if (joueurCourant == partie->getJoueur1())
            joueurCourant = partie->getJoueur2();
        else
            joueurCourant = partie->getJoueur1();

        if (joueurCourant->getTypeDeJoueur() == type::IA) {
            strategy_courante = &strategy_IA;
            //Tour_ia();
        }
        else
            strategy_courante = &strategy_Humain;
    }
}

void Controller::changerJoueurCourantGraphique() {
    //changement du joueur courant
    if(!nouveau_tour){
        if (joueurCourant == partie->getJoueur1())
            joueurCourant = partie->getJoueur2();
        else
            joueurCourant = partie->getJoueur1();

        if (joueurCourant->getTypeDeJoueur() == type::IA) {
            strategy_courante = &strategy_IA;
            Tour_ia();
        }
        else
            strategy_courante = &strategy_Humain;
    }
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
        qDebug() << "\033[1;36mC'est " << partie->getJoueur1()->getPseudo() << " qui commence, son adversaire recoit donc 1 privilege.\033[0m\n";
        partie->getJoueur2()->addPrivilege(partie->getEspaceJeux().getPlateau().recupererPrivilege());
        break;
    case 1:
        qDebug() << "\033[1;36mC'est " << partie->getJoueur2()->getPseudo() << " qui commence, son adversaire recoit donc 1 privilege.\033[0m\n";
        partie->getJoueur1()->addPrivilege(partie->getEspaceJeux().getPlateau().recupererPrivilege());
        break;
    default:
        break;
    }
    partie->setTour(0);
    partie->getEspaceJeux().getPyramide().remplirPyramide();
    partie->getEspaceJeux().getPlateau().remplirPlateau(partie->getEspaceJeux().getSac());
}




void Controller::quitter() {
    std::string sauvegarde;
    qDebug()<<"Vous avez decider de quitter la partie\n";
    qDebug()<<"Voulez vous la sauvegarde ? (Oui, Non)\n";
    std::cin>>sauvegarde;
    if (sauvegarde=="OUI"||sauvegarde=="oui"||sauvegarde=="Oui")
        sauvegardePartie();
    else
        qDebug()<<"tant pis...\n";
    return;
}




void Controller::jouer() {
    while (1) {
        // tour pour chacun des joueurs
        qDebug() << "\n\n\n\n\n\n\n\n\n\n\n\n";
        bool tourEnPlus;

        // correpond au tour de chaque joueur
        for (unsigned int i = 0; i < 2; i++) {
            qDebug() << "--------------------------------------------------------------------------------------------------------------------------------------------\n";
            tourEnPlus = false;
            bool a_deja_utilise_privilege = false;
            bool a_deja_rempli_plateau = false;

            unsigned int etat_tour = 0;
            while (etat_tour != 10) {
                tourEnPlus = false;

                // actions optionelles
                switch (etat_tour) {
                case 0: {
                    unsigned int etat_action = 0;
                    while (etat_action != 10) {
                        switch (etat_action) {
                        case 0: {
                            // affichage de l'etat en cours
                            qDebug() << "C'est a " << getJoueurCourant().getPseudo() << " de jouer : \n";
                            qDebug() << "Nous en sommes au tour : " << getPartie().getTour() + 1 << "\n";

                            // appel du menu de choix des actions
                            getJoueurCourant().afficherJoueur();
                            etat_action = choixActionsOptionelles();
                            qDebug() << etat_action;
                            break;
                        }
                        case 1: {
                            try {
                                // utilisation d'un privilege
                                if (a_deja_utilise_privilege) throw SplendorException("Vous avez deja utilise cette action");
                                utiliserPrivilege(getPartie().getEspaceJeux().getPlateau());
                                a_deja_utilise_privilege = true;
                                etat_action = 0;
                            } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_action = 0; }
                            break;
                        }
                        case 2: {
                            try {
                                // remplissage du plateau
                                if (a_deja_rempli_plateau) throw SplendorException("Vous avez deja utilise cette action");
                                remplirPlateau(getPartie().getEspaceJeux().getPlateau(), getPartie().getEspaceJeux().getSac());
                                a_deja_rempli_plateau = true;
                                etat_action = 0;
                            } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_action = 0; }
                            break;
                        }
                        case 3: {
                            etat_tour = 1;
                            etat_action = 10;
                            break;
                        }
                        case 9: {
                            quitter();
                            return;
                        }
                        default: {
                            etat_action = 0;
                            qDebug() << "Veuillez faire un choix correct !\n";
                            break;
                        }
                        }
                    }
                    break;
                }
                // actions obligatoires :
                case 1: {
                    unsigned int etat_action = 0;
                    while (etat_action != 10) {
                        switch (etat_action) {
                        case 0:
                            // menu de choix des actions obligatoires
                            etat_action = choixActionsObligatoires();
                            qDebug() << etat_action;
                            break;
                        case 1:
                            try {
                                // recuperation de jetons
                                qDebug() << joueurCourant->getPseudo();
                                recupererJetons(false);
                                etat_action = 10;
                                etat_tour = 2;
                            } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_tour = 0; etat_action = 10; }
                            break;
                        case 2:
                            try {
                                // achat carte joaillerie
                                tourEnPlus = acheterCarteJoaillerie(getPartie().getEspaceJeux());
                                if (tourEnPlus) { etat_tour = 0; etat_action = 0; }
                                else { etat_action = 10; etat_tour = 2; }
                            } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_tour = 0; etat_action = 10; }
                            break;
                        case 3:
                            try {
                                // reservation carte
                                orReserverCarte(getPartie().getEspaceJeux().getPyramide(), getPartie().getEspaceJeux().getPlateau());
                                etat_action = 10;
                                etat_tour = 2;
                            } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_tour = 0; etat_action = 10; }
                            break;
                        case 9: {
                            quitter();
                            return;
                        }
                        default:
                            etat_action = 0;
                            qDebug() << "Veuillez faire un choix correct !\n";
                            break;
                        }
                    }
                    break;
                }
                // verification fin de tour d'un joueur
                case 2: {
                    // achat obligatoire d'une carte noble si le joueur a 3 pts et 0 cartes nobles ou 6 pts de prestige et 1 carte noble
                    while ((getJoueurCourant().getNbCouronnes() >= 3 && getJoueurCourant().getNbCartesNobles() == 0) ||
                           (getJoueurCourant().getNbCouronnes() >= 6 && getJoueurCourant().getNbCartesNobles() == 1)) {
                        try { acheterCarteNoble(getPartie().getEspaceJeux().getPyramide()); } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n'; };
                    }

                    verifJetonSupDix();

                    // Conditions victoires :
                    if (getJoueurCourant().getNbCouronnes() >= 10) getJoueurCourant().setGagnant();
                    if (getJoueurCourant().getptsPrestige() >= 20) getJoueurCourant().setGagnant();
                    if (getJoueurCourant().nbPtsPrestigeParCouleurSupDix()) getJoueurCourant().setGagnant();

                    //Sauvegarde automatique
                    if (getPartie().getTour()==30) {
                        sauvegardePartie();
                    }

                    // Fin de partie :
                    if (getJoueurCourant().estGagnant())
                        etat_tour = 3;
                    else{
                    // fin du tour du joueur, on passe au joueur suivant
                    changerJoueurCourant();
                    etat_tour = 10;
                    }
                    break;
                }
                case 3: {

                    // affichage rigolo
                    const std::string message = "Le Joueur " + getJoueurCourant().getPseudo() + " a gagne apres " + std::to_string(getPartie().getTour()) + " tours !";
                    for (size_t j = 0; j < 100; j++) {
                        for (std::size_t i = 0; i < message.size(); ++i) {
                            // Utilisation des codes ANSI pour le texte en gras et avec différentes couleurs
                            std::cout << "\033[1;3" << (i % 7) + 1 << "m" << message[i];
                        }
                        std::cout << "\n\n";
                        for (std::size_t l = 0; l < j; ++l) std::cout << " ";
                    };
                    // Reinitialisation du style après la dernière lettre
                    std::cout << "\033[0m\n";

                    //enregistrement des score
                    qDebug() << "Enregistrement des score...\n";
                    enregisterScore();
                    qDebug() << "DONE\n";

                    std::cout << "Fin de la partie !\n";
                    return;
                    break;
                }
                default: {
                    break;
                }
                }
            }
        }
        // fin du tour :
        getPartie().incrementeTour();
    }
}




///////////////////////// Actions d'un joueur /////////////////////////

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




// Capacite
bool Controller::appliquerCapacite(Capacite capa,const Carte &carte){
    //NewTurn, TakePrivilege, TakeJetonFromBonus, TakeJetonToAdv, AssociationBonus, None

    switch (capa) {
        case Capacite::NewTurn: { // Modifier achar carte et la boucle de jeu pour que ça soit effectif
            return true;
            break;
        }
        case Capacite::TakePrivilege: {
            if (partie->getEspaceJeux().getPlateau().getNbPrivileges()==0){
                //si il n'y a plus de privileges sur le plateau
                if(joueurCourant->getNbPrivileges()!=3) {
                    //si il n'a pas déjà les 3 privilèges, il prends celui du joueur actuel, sinon il n'en recupere pas
                    joueurCourant->addPrivilege(getJoueurAdverse().supPrivilege());
                }
            } else {
                //si il y a un jetons sur le plateau, le joueur le recupere
                joueurCourant->addPrivilege(partie->getEspaceJeux().getPlateau().recupererPrivilege());
            }
            qDebug()<<"Ajout d'un privilège correspondant à la capacite\n";
            break;
        }
        case Capacite::TakeJetonFromBonus: {
            qDebug()<<"Recuperation d'un jeton correspondant à la capacite\n";
            recupererJetons(true, carte.getBonus().getCouleur());
            break;
        }
        case Capacite::TakeJetonToAdv: {
            // le joueur prend 1 jeton Gemme ou Perle à son adversaire. Si ce dernier n’en a pas,
            //cette capacité est sans effet. Il est interdit de prendre un jeton Or à son adversaire.
            qDebug()<<"Voici les jetons de votre adversaire\n";
            //getJoueurAdverse().afficherJoueur();

            std::string coulJetonStr;
            qDebug()<<"Quel est la couleur du jeton que vous voulez recuperer que Gemme ou perle ?\n";

            Couleur coulJeton = strategy_courante->choixCouleur();
            // On verifie que le jeton est bien un jeton gemme ou perle
            while(coulJeton == Couleur::OR || coulJeton == Couleur::INDT){
                qDebug()<<"Veuillez selectionner un jeton Gemme ou perle\n";
                coulJeton = strategy_courante->choixCouleur();
            }

            // Si le joueur adverse n'as pas de jeton de cette couleur on ne fait rien
            if(getJoueurAdverse().jetons.at(coulJeton).empty())
                throw SplendorException("Impossible le joueur adverse ne possede pas de jetons de cette couleur");
            // Recup du jeton a l'adversaire
            const Jeton &jeton = getJoueurAdverse().RecupJetonCoul(coulJeton);

            qDebug()<<"Ajout du jeton grace a la capacite\n";
            joueurCourant->addJeton(jeton);
            break;
        }
        case Capacite::AssociationBonus: {
            break;
        }

        default:{
            qDebug()<<"Impossible\n";
            break;
        }
    }
    return false;
}




//Menu choix des actions
unsigned int Controller::choixActionsObligatoires() {
    qDebug() << "\033[1mActions obligatoires:\033[0m\n";
    qDebug() << "1. Recuperer des jetons\n";
    qDebug()  << "2. Acheter une carte joaillerie\n";
    qDebug() << "3. Reserver une carte\n";
    qDebug() << "9. Quitter le jeu\n";
    qDebug() << "Votre choix (1/2/3/9):\n";

    return strategy_courante->choixMenu(verifActionsImpossibles());;
}




unsigned int Controller::choixActionsOptionelles() {
    qDebug() << "1. Utiliser un privilege\n";
    qDebug()  << "2. Remplir le plateau\n";
    qDebug() << "3. Ne plus faire d'actions optionnelles\n";
    qDebug() << "9. Quitter le jeu\n";
    qDebug() << "Votre choix (1/2/3/9):\n";

    return strategy_courante->choixMenu(verifActionsOptImpossibles());;
}




// Utiliser un privilege
void Controller::utiliserPrivilege(Plateau& plateau){
    //on verifie d'abord si le joueur a un/des privilege
    verifPrivileges();
    verifPlateauvide();

    qDebug() << "Combien de privileges voulez vous utiliser ?\n";
    unsigned int priv = strategy_courante->choix_min_max(1,joueurCourant->getNbPrivileges());
    if (priv>joueurCourant->getNbPrivileges())
        throw SplendorException("Vous n'avez pas assez de privilege");
    if (priv>plateau.getNbJetons())
        throw SplendorException("Il n'y a plus assez de jetons sur le plateau");

    //on recupere autant de jetons que de privilege
    for (size_t k=0; k<priv;k++) {
        qDebug()<<"Utiliser un privilege permet de recup un jeton de couleur ou perle de votre choix (i,j):\n";

        qDebug()<<plateau<<"\n";

        qDebug() << "Voici les jetons disponibles: \n";

        std::vector<std::pair<int, int>> jetonsDispo = getEspaceJeux().getPlateau().getVectorDispo();
        if(jetonsDispo.size() == 0){
            getEspaceJeux().getPlateau().remplirPlateau(getEspaceJeux().getSac());
            throw SplendorException("\n Plus de Jetons disponibles");
        }

        for (unsigned int i =0; i<jetonsDispo.size(); i++) {
            qDebug() << "(" << jetonsDispo[i].first << "," << jetonsDispo[i].second << ") (" << i << ")";
        }


        int choix_indice_jeton = strategy_courante->choix_min_max(1, jetonsDispo.size());

        int i = jetonsDispo[choix_indice_jeton-1].first;
        int j = jetonsDispo[choix_indice_jeton-1].second;

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

    qDebug() << "Voici le nouveau plateau (apres recuperation) \n" << getPartie().getEspaceJeux().getPlateau();
    //joueurCourant->afficherJoueur();
    return;
}




void Controller::remplirPlateau(Plateau& plateau, Sac& sac){
    if(joueurCourant->getNbJetons() > 10 && getPlateau().contientOnlyOr() && getEspaceJeux().getSac().estVide())
        verifJetonSupDix();
    //on verifie d'abord si le joueur a un/des privilege
    verifSacvide();

    qDebug()<<"Le joueur rempli le plateau :\n" << plateau << '\n';

    //on donne un privilege au joueur adverse
    donPrivilegeAdverse();

    plateau.remplirPlateau(sac);
    qDebug()<<"Nouveau plateau : \n" <<plateau;

    return;
}




// Recuperer des jetons
void Controller::recupererJetons(bool capacite,Couleur coulBonus){
    qDebug()<<"Vous avez decider de recuperer des jetons sur le plateau :\n" << getPlateau();
    verifPlateauvide();

    // Recuperation des jetons 1 2 ou 3 jetons en fonction de la strategy

    unsigned int nbJetons;
    // Recuperation d'un jeton pour la capacite
    if(capacite){
        nbJetons = 1;
    } else {
        qDebug() << "Combien de jetons souhaitez-vous recuperer ? (1,2,3) \n";

        nbJetons = strategy_courante->choix_min_max(1,3);
    }


    if (nbJetons>partie->getEspaceJeux().getPlateau().getNbJetons())
        throw SplendorException("Il n'y a plus assez de jetons sur le plateau");


    if(capacite){
        qDebug() << "Merci de selectionner un jeton de la meme couleur que le bonus.\n\n";
    }else {
        qDebug() << "Merci de selectionner des jetons adjacents en ligne, en colonne ou en diagonale.\n\n";
    }


    std::vector<std::pair<int, int>> vecteurCoordonnees;
    qDebug()<<"Vous allez rentrer les coordonnees des jetons : \n";
    // Recup des coordonnees des jetons

    std::vector<std::pair<int, int>> jetonsDispo;

    if(capacite){
        jetonsDispo = getEspaceJeux().getPlateau().getVectorCouleurDispo(coulBonus);
    }else {
        jetonsDispo = getEspaceJeux().getPlateau().getVectorDispo();
    }



    for (unsigned int k = 0; k < nbJetons; k++){

        // Ajout des coordonnees
        qDebug()<<"Jetons numero "<<k+1<<" : \n";

        qDebug() << "Voici les jetons disponibles: \n";

        if(jetonsDispo.size() == 0){
            getEspaceJeux().getPlateau().remplirPlateau(getEspaceJeux().getSac());
            throw SplendorException("\n Plus de Jetons disponibles");
        }

        for (unsigned int i =0; i<jetonsDispo.size(); i++) {
            qDebug() << "(" << jetonsDispo[i].first << "," << jetonsDispo[i].second << ") (" << i+1 << ")";
        }


        int choix_indice_jeton = strategy_courante->choix_min_max(1, jetonsDispo.size());

        vecteurCoordonnees.push_back(jetonsDispo[choix_indice_jeton-1]);

        jetonsDispo.erase(jetonsDispo.begin() + choix_indice_jeton-1);

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
        if (capacite && jetonsRecup[k]->getCouleur() != coulBonus)
            throw SplendorException("Le jeton n'est pas de la couleur du bonus");
    }

    // ajout des jetons dans la main du joueur
    for (auto & i : jetonsRecup){
        joueurCourant->addJeton(*i);
    }

    // Ajout privilège joueur adv si 3 jetons mm couleur ou 2 jetons perle
    unsigned int nbJetonsPerle = 0;
    bool troisJetons = true;
    Couleur coulPremierJeton = jetonsRecup[0]->getCouleur();
    for(unsigned int k = 0; k < nbJetons; k++){
        if(jetonsRecup[k]->getCouleur() == Couleur::PERLE){
            nbJetonsPerle++;
        }
        if(jetonsRecup[k]->getCouleur() != coulPremierJeton && troisJetons != false){
            troisJetons = false;
        }
    }
    if(nbJetonsPerle == 2 || (troisJetons == true && jetonsRecup.size()== 3)){
        qDebug()<<"Ajout d'un privilège pour le joueur adverse\n" ;
        donPrivilegeAdverse();
        qDebug()<<"Voici l'etat du joueur adverse apres recuperation :\n" ;
        getJoueurAdverse().afficherJoueur();

    }


    qDebug()<<"Voici le nouveau plateau (apres recuperation) \n" << getPlateau();
    qDebug()<<"Voici l'etat du joueur apres recuperation :\n" ;
    joueurCourant->afficherJoueur();
    return;
}





void Controller::recupererJetons(const std::vector<std::pair<int, int> > &coord){

    // Recup des jetons
    std::vector<const Jeton*> jetonsRecup;
    for (unsigned int k = 0; k < coord.size(); k++){
        jetonsRecup.push_back(&getPlateau().recupererJeton(coord[k].first, coord[k].second));
    }

    // ajout des jetons dans la main du joueur
    for (auto & i : jetonsRecup){
        joueurCourant->addJeton(*i);
    }

    // Ajout privilège joueur adv si 3 jetons mm couleur ou 2 jetons perle
    unsigned int nbJetonsPerle = 0;
    bool troisJetons = true;
    Couleur coulPremierJeton = jetonsRecup[0]->getCouleur();
    for(unsigned int k = 0; k < coord.size(); k++){
        if(jetonsRecup[k]->getCouleur() == Couleur::PERLE){
            nbJetonsPerle++;
        }
        if(jetonsRecup[k]->getCouleur() != coulPremierJeton && troisJetons != false){
            troisJetons = false;
        }
    }
    if(nbJetonsPerle == 2 || (troisJetons == true && jetonsRecup.size()== 3)){
        donPrivilegeAdverse();
    }
    return;
}




//TODO
bool Controller::acheterCarteJoaillerie (EspaceJeux& espaceJeux){
    qDebug()<<"Vous avez decider d'acheter une carte joaillerie\n";
    qDebug()<<"Voulez vous acheter une carte reservee (1) ou une carte du plateau de jeu (2)\n";
    unsigned int choix = strategy_courante->choix_min_max(1,2);


    // Achat carte reservee
    if (choix == 1){
        if(joueurCourant->getNbCartesReservees()==0)
            throw SplendorException("Vous n'avez pas de carte rerservee\n");

        vector<pair<Couleur, int>> resa_dispo = GenereCarteResaDispo();
        if(resa_dispo.size() == 0)
            throw SplendorException("Vous ne pouvez acheter aucun carte reservee\n");

        qDebug() << "Voici les cartes reservees que vous pouvez acheter: \n";

        for (unsigned int i =0; i < resa_dispo.size(); i++){
            qDebug() << i+1 << " : \n" << joueurCourant->getCarteReservee(resa_dispo[i].first, resa_dispo[i].second) << "\n\n\n";
        }

        // on recupere la couleur de la carte reservee

        qDebug() << "veuillez choisir une carte parmi elles\n";
        unsigned int choix = strategy_courante->choix_min_max(1, resa_dispo.size())-1;

        const Carte& carte = joueurCourant->getCarteReservee(resa_dispo[choix].first, resa_dispo[choix].second);
        //on verifie que le joueur peut bien acheter la carte, sinon on la repose

        paiementCarte(carte, espaceJeux);

        // Si la carte a une capacite on l'execute
        bool res = false;
        if(carte.getCapacite1() != Capacite::None && carte.getCapacite1() != Capacite::AssociationBonus){
            res = appliquerCapacite(carte.getCapacite1(), carte);
            // On regarde si on ajoute un tour
            return res;
        }
        if(carte.getCapacite2() != Capacite::None && carte.getCapacite2() != Capacite::AssociationBonus){
            res = appliquerCapacite(carte.getCapacite2(), carte);
            // On regarde si on ajoute un tour
            return res;
        }

        if(carte.getCapacite1() == Capacite::AssociationBonus || carte.getCapacite2() == Capacite::AssociationBonus){
            qDebug()<<"La carte a une capacite qui permet d'ajouter un bonus a la couleur de votre choix\n";

            std::string coulJetonStr;
            qDebug()<<"Quel est la couleur du bonus que vous voulez recuperer ?\n";

            Couleur coulBonus = strategy_courante->choixCouleur();
            // On verifie que la validite de la couleur du bonus
            while(coulBonus == Couleur::PERLE || coulBonus == Couleur::INDT){
                qDebug()<<"Veuillez selectionner un jeton Gemme ou perle\n";
                coulBonus = strategy_courante->choixCouleur();
            }
            // Ajout du bonus
            joueurCourant->addBonus(coulBonus, 1);
            qDebug()<<"Le bonus a bien ete ajoute\n";

            joueurCourant->cartes[coulBonus].push_back(&carte);
            joueurCourant->supCarteReservee(carte);
            joueurCourant->ptsPrestige += carte.getNbPtsPrivilege();
            joueurCourant->nbCouronnes += carte.getNbCouronnes();
        } else{
            //on ajoute la carte au joueur
            joueurCourant->addCarte(carte);
            joueurCourant->supCarteReservee(carte);
            joueurCourant->addBonus(carte.getBonus().getCouleur(), carte.getBonus().getNbBonus());
        }
        return res;
    }

    // Achat carte du plateau
    else {
        // Affichage des cartes
        getPyramide().afficherPyramide();
        vector<pair<int, int>> cartes_dispo = GenereCartePyramideDispo();

        if (cartes_dispo.size() == 0)
            throw SplendorException("Vous ne pouvez pas acheter de carte de la pyramide\n");

        qDebug() << "Voici les cartes que vous pouvez acheter : \n";
        for (unsigned int i = 0; i < cartes_dispo.size(); i++)
            qDebug() << i+1 << " : \n" <<  *getPyramide().getCarte(cartes_dispo[i].first, cartes_dispo[i].second) << "\n\n\n";
        unsigned int choix = strategy_courante->choix_min_max(1, cartes_dispo.size())-1;

        //on peut alors l'acheter, elle sera directement remplacer par une nouvelle
        const Carte& carte = partie->getEspaceJeux().getPyramide().acheterCarte(cartes_dispo[choix].first, cartes_dispo[choix].second);

        paiementCarte(carte, espaceJeux);

        // Si la carte a une capacite on l'execute
        bool res = false;
        if(carte.getCapacite1() != Capacite::None && carte.getCapacite1() != Capacite::AssociationBonus){
            res = appliquerCapacite(carte.getCapacite1(), carte);
            // On regarde si on ajoute un tour
            return res;
        }
        if(carte.getCapacite2() != Capacite::None && carte.getCapacite2() != Capacite::AssociationBonus){
            res = appliquerCapacite(carte.getCapacite2(), carte);
            // On regarde si on ajoute un tour
            return res;
        }

        if(carte.getCapacite1() == Capacite::AssociationBonus || carte.getCapacite2() == Capacite::AssociationBonus){
            qDebug()<<"La carte a une capacite qui permet d'ajouter un bonus a la couleur de votre choix\n";

            std::string coulJetonStr;
            qDebug()<<"Quel est la couleur du bonus que vous voulez recuperer ?\n";

            Couleur coulBonus = strategy_courante->choixCouleur();
            // On verifie que la validite de la couleur du bonus
            while(coulBonus == Couleur::PERLE || coulBonus == Couleur::INDT){
                qDebug()<<"Veuillez selectionner un jeton Gemme ou perle\n";
                coulBonus = strategy_courante->choixCouleur();
            }
            // Ajout du bonus
            joueurCourant->addBonus(coulBonus, 1);
            qDebug()<<"Le bonus a bien ete ajoute\n";

            joueurCourant->cartes[coulBonus].push_back(&carte);
            joueurCourant->ptsPrestige += carte.getNbPtsPrivilege();
            joueurCourant->nbCouronnes += carte.getNbCouronnes();
        } else{
            //on ajoute la carte au joueur
            joueurCourant->addCarte(carte);
            joueurCourant->addBonus(carte.getBonus().getCouleur(), carte.getBonus().getNbBonus());
            return res;
        }
        return res;
    }
}

void Controller::orReserverCarte (std::pair<int, int> coord){
    /*verifTroisCarteReserve();
    verifOrSurPlateau();
    qDebug()  << "Commencez par choisir un jeton Or : \n";
    qDebug()  <<  getPlateau();


    qDebug() << "Voici les jetons disponibles: \n";

    std::vector<std::pair<int, int>> jetonsOrDispo = getEspaceJeux().getPlateau().getVectorOrDispo();

    if(jetonsOrDispo.size() == 0){
        //getEspaceJeux().getPlateau().remplirPlateau(getEspaceJeux().getSac());
        throw SplendorException("Plus de Jetons Or disponibles");
    }

    for (int i =0; i<jetonsOrDispo.size(); i++) {
        qDebug() << "(" << jetonsOrDispo[i].first << "," << jetonsOrDispo[i].second << ") (" << i + 1 << ")";
    }

    int ChoixOrDispo = strategy_courante->choix_min_max(1, jetonsOrDispo.size());

    qDebug()  << "Voulez-vous reserver une carte de la pyramide (0) ou celle d'une pioche (1, 2, 3) ?\n";
    unsigned int choix = strategy_courante->choix_min_max(0, 3);

    if (choix == 0){
        // Reservation de la carte
        qDebug() << "Voici les cartes de la pyramide : \n";

        getPyramide().afficherPyramide();

        qDebug()  << "rentrez le niveau de la carte souhaitee : \n";
        unsigned int niveau = strategy_courante->choix_min_max(1, 3)-1;
        qDebug()  << "rentrez le numero de la carte souhaitee : \n";
        unsigned int num_carte = strategy_courante->choix_min_max(1, getPyramide().getNbCartesNiv(niveau))-1;

        const Carte& carte = pyramide.acheterCarte(niveau, num_carte);
        joueurCourant->addCarteReservee(carte);
    }
    else if (choix == 1 || choix == 2 || choix == 3){
        // Reservation de la carte
        const Carte& carte = pyramide.ReserverCartePioche(choix);
        joueurCourant->addCarteReservee(carte);
    }*/

    // Voir resa carte de la pioche
    //const Carte& carte = partie->getEspaceJeux().getPyramide().ReserverCartePioche(choix);


    const Carte& carte = partie->getEspaceJeux().getPyramide().acheterCarte(coord.first, coord.second);
    joueurCourant->addCarteReservee(carte);


    // Voir achat jeton or
    //const Jeton& jeton = plateau.recupererJeton( jetonsOrDispo[ChoixOrDispo-1].first,  jetonsOrDispo[ChoixOrDispo-1].second);
    //joueurCourant->addJeton(jeton);

    qDebug()  << "Etat du joueur apres l'action : \n";
    //joueurCourant->afficherJoueur();
}


void Controller::orReserverCartePioche (int nivPioche){
    /*verifTroisCarteReserve();
    verifOrSurPlateau();
    qDebug()  << "Commencez par choisir un jeton Or : \n";
    qDebug()  <<  getPlateau();


    qDebug() << "Voici les jetons disponibles: \n";

    std::vector<std::pair<int, int>> jetonsOrDispo = getEspaceJeux().getPlateau().getVectorOrDispo();

    if(jetonsOrDispo.size() == 0){
        //getEspaceJeux().getPlateau().remplirPlateau(getEspaceJeux().getSac());
        throw SplendorException("Plus de Jetons Or disponibles");
    }

    for (int i =0; i<jetonsOrDispo.size(); i++) {
        qDebug() << "(" << jetonsOrDispo[i].first << "," << jetonsOrDispo[i].second << ") (" << i + 1 << ")";
    }

    int ChoixOrDispo = strategy_courante->choix_min_max(1, jetonsOrDispo.size());

    qDebug()  << "Voulez-vous reserver une carte de la pyramide (0) ou celle d'une pioche (1, 2, 3) ?\n";
    unsigned int choix = strategy_courante->choix_min_max(0, 3);

    if (choix == 0){
        // Reservation de la carte
        qDebug() << "Voici les cartes de la pyramide : \n";

        getPyramide().afficherPyramide();

        qDebug()  << "rentrez le niveau de la carte souhaitee : \n";
        unsigned int niveau = strategy_courante->choix_min_max(1, 3)-1;
        qDebug()  << "rentrez le numero de la carte souhaitee : \n";
        unsigned int num_carte = strategy_courante->choix_min_max(1, getPyramide().getNbCartesNiv(niveau))-1;

        const Carte& carte = pyramide.acheterCarte(niveau, num_carte);
        joueurCourant->addCarteReservee(carte);
    }
    else if (choix == 1 || choix == 2 || choix == 3){
        // Reservation de la carte
        const Carte& carte = pyramide.ReserverCartePioche(choix);
        joueurCourant->addCarteReservee(carte);
    }*/

    // Voir resa carte de la pioche
    //const Carte& carte = partie->getEspaceJeux().getPyramide().ReserverCartePioche(choix);

    const Carte& carte = partie->getEspaceJeux().getPyramide().ReserverCartePioche(nivPioche);
    joueurCourant->addCarteReservee(carte);



    // Voir achat jeton or
    //const Jeton& jeton = plateau.recupererJeton( jetonsOrDispo[ChoixOrDispo-1].first,  jetonsOrDispo[ChoixOrDispo-1].second);
    //joueurCourant->addJeton(jeton);

    qDebug()  << "Etat du joueur apres l'action : \n";
    //joueurCourant->afficherJoueur();
}

void Controller::acheterCarteJoaillerie(std::pair<int, int> coord){

    //on peut alors l'acheter, elle sera directement remplacer par une nouvelle
    const Carte& carte = partie->getEspaceJeux().getPyramide().acheterCarte(coord.first, coord.second);

    paiementCarte(carte, getEspaceJeux());

    // Si la carte a une capacite on l'execute
    /*bool res = false;
    if(carte.getCapacite1() != Capacite::None && carte.getCapacite1() != Capacite::AssociationBonus){
        res = appliquerCapacite(carte.getCapacite1(), carte);
        // On regarde si on ajoute un tour
        return res;
    }
    if(carte.getCapacite2() != Capacite::None && carte.getCapacite2() != Capacite::AssociationBonus){
        res = appliquerCapacite(carte.getCapacite2(), carte);
        // On regarde si on ajoute un tour
        return res;
    }

    if(carte.getCapacite1() == Capacite::AssociationBonus || carte.getCapacite2() == Capacite::AssociationBonus){
        qDebug()<<"La carte a une capacite qui permet d'ajouter un bonus a la couleur de votre choix\n";

        std::string coulJetonStr;
        qDebug()<<"Quel est la couleur du bonus que vous voulez recuperer ?\n";

        Couleur coulBonus = strategy_courante->choixCouleur();
        // On verifie que la validite de la couleur du bonus
        while(coulBonus == Couleur::PERLE || coulBonus == Couleur::INDT){
            qDebug()<<"Veuillez selectionner un jeton Gemme ou perle\n";
            coulBonus = strategy_courante->choixCouleur();
        }
        // Ajout du bonus
        joueurCourant->addBonus(coulBonus, 1);
        qDebug()<<"Le bonus a bien ete ajoute\n";

        joueurCourant->cartes[coulBonus].push_back(&carte);
        joueurCourant->ptsPrestige += carte.getNbPtsPrivilege();
        joueurCourant->nbCouronnes += carte.getNbCouronnes();
    } else{*/
    //on ajoute la carte au joueur
    joueurCourant->addCarte(carte);
    joueurCourant->addBonus(carte.getBonus().getCouleur(), carte.getBonus().getNbBonus());
    //return res;
    //}
    //return res;
}




void Controller::paiementCarte(const Carte &carte, EspaceJeux& espaceJeux){
    int needBlanc =  carte.getPrix().getBlanc() ;
    int needBleu =  carte.getPrix().getBleu();
    int needVert =  carte.getPrix().getVert();
    int needRouge =  carte.getPrix().getRouge();
    int needNoir =  carte.getPrix().getNoir();
    int needPerle = carte.getPrix().getPerle();


    unsigned int nbBlanc = 0;
    auto itBlanc = joueurCourant->jetons.find(Couleur::BLANC);
    if (itBlanc != joueurCourant->jetons.end()) {
        nbBlanc = itBlanc->second.size();

        auto itBonusBlanc = joueurCourant->bonus.find(Couleur::BLANC);
        if (itBonusBlanc != joueurCourant->bonus.end()) {
            needBlanc -= itBonusBlanc->second;
        }
        if(needBlanc <0)
            needBlanc = 0;
    }


    unsigned int nbBleu = 0;
    auto itBleu = joueurCourant->jetons.find(Couleur::BLEU);
    if (itBleu != joueurCourant->jetons.end()) {
        nbBleu = itBleu->second.size();

        auto itBonusBleu = joueurCourant->bonus.find(Couleur::BLEU);
        if (itBonusBleu != joueurCourant->bonus.end()) {
            needBleu -= itBonusBleu->second;
        }
        if(needBleu<0)
            needBleu = 0;
    }

    unsigned int nbVert = 0;
    auto itVert = joueurCourant->jetons.find(Couleur::VERT);
    if (itVert != joueurCourant->jetons.end()) {
        nbVert = itVert->second.size();

        auto itBonusVert = joueurCourant->bonus.find(Couleur::VERT);
        if (itBonusVert != joueurCourant->bonus.end()) {
            needVert -= itBonusVert->second;
        }
        if(needVert <0)
            needVert = 0;
    }

    unsigned int nbRouge = 0;
    auto itRouge = joueurCourant->jetons.find(Couleur::ROUGE);
    if (itRouge != joueurCourant->jetons.end()) {
        nbRouge = itRouge->second.size();

        auto itBonusRouge = joueurCourant->bonus.find(Couleur::ROUGE);
        if (itBonusRouge != joueurCourant->bonus.end()) {
            needRouge -= itBonusRouge->second;
        }
        if(needRouge <0)
            needRouge = 0;
    }

    unsigned int nbNoir = 0;
    auto itNoir = joueurCourant->jetons.find(Couleur::NOIR);
    if (itNoir != joueurCourant->jetons.end()) {
        nbNoir = itNoir->second.size();

        auto itBonusNoir = joueurCourant->bonus.find(Couleur::NOIR);
        if (itBonusNoir != joueurCourant->bonus.end()) {
            needNoir -= itBonusNoir->second;
        }
        if(needNoir <0)
            needNoir = 0;
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

    unsigned int jetonsOrUtilises = 0;

    // Fonction pour ajouter des jetons or a une couleur donnee
    auto ajouterJetonsOr = [&jetonsOrUtilises, &nbOr](unsigned int& nbCouleur, int& besoin) {
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

    joueurCourant->supJetonNb(needBlanc, Couleur::BLANC, espaceJeux);
    joueurCourant->supJetonNb(needBleu, Couleur::BLEU, espaceJeux);
    joueurCourant->supJetonNb(needVert, Couleur::VERT, espaceJeux);
    joueurCourant->supJetonNb(needRouge, Couleur::ROUGE, espaceJeux);
    joueurCourant->supJetonNb(needNoir, Couleur::NOIR, espaceJeux);
    joueurCourant->supJetonNb(needPerle, Couleur::PERLE, espaceJeux);
    joueurCourant->supJetonNb(jetonsOrUtilises, Couleur::OR, espaceJeux);
}




void Controller::acheterCarteNoble (Pyramide& pyramide){
    qDebug()<<"Vous devez achter une carte noble car vous avez 3 ou 6 pts de prestige\n";
    // affichage cartes nobles
    //pyramide.afficherNobles();

    unsigned int i = strategy_courante->choix_min_max(1,pyramide.getNbCartesNiv(3))-1;

    const Carte& carte = pyramide.acheterCarte(3, i);

    joueurCourant->addCarteNoble(carte);
}




void Controller::orReserverCarte (Pyramide& pyramide, Plateau& plateau){
    verifTroisCarteReserve();
    verifOrSurPlateau();
    qDebug()  << "Commencez par choisir un jeton Or : \n";
    qDebug()  <<  getPlateau();


    qDebug() << "Voici les jetons disponibles: \n";

    std::vector<std::pair<int, int>> jetonsOrDispo = getEspaceJeux().getPlateau().getVectorOrDispo();

    if(jetonsOrDispo.size() == 0){
        //getEspaceJeux().getPlateau().remplirPlateau(getEspaceJeux().getSac());
        throw SplendorException("Plus de Jetons Or disponibles");
    }

    for (unsigned int i =0; i<jetonsOrDispo.size(); i++) {
        qDebug() << "(" << jetonsOrDispo[i].first << "," << jetonsOrDispo[i].second << ") (" << i + 1 << ")";
    }

    int ChoixOrDispo = strategy_courante->choix_min_max(1, jetonsOrDispo.size());

    qDebug()  << "Voulez-vous reserver une carte de la pyramide (0) ou celle d'une pioche (1, 2, 3) ?\n";
    unsigned int choix = strategy_courante->choix_min_max(0, 3);

    if (choix == 0){
        // Reservation de la carte
        qDebug() << "Voici les cartes de la pyramide : \n";

        getPyramide().afficherPyramide();

        qDebug()  << "rentrez le niveau de la carte souhaitee : \n";
        unsigned int niveau = strategy_courante->choix_min_max(1, 3)-1;
        qDebug()  << "rentrez le numero de la carte souhaitee : \n";
        unsigned int num_carte = strategy_courante->choix_min_max(1, getPyramide().getNbCartesNiv(niveau))-1;

        const Carte& carte = pyramide.acheterCarte(niveau, num_carte);
        joueurCourant->addCarteReservee(carte);
}
    else if (choix == 1 || choix == 2 || choix == 3){
        // Reservation de la carte
        const Carte& carte = pyramide.ReserverCartePioche(choix);
        joueurCourant->addCarteReservee(carte);
    }

    const Jeton& jeton = plateau.recupererJeton( jetonsOrDispo[ChoixOrDispo-1].first,  jetonsOrDispo[ChoixOrDispo-1].second);
    joueurCourant->addJeton(jeton);

    qDebug()  << "Etat du joueur apres l'action : \n";
    //joueurCourant->afficherJoueur();
}




vector<pair<int, int>> Controller::GenereCartePyramideDispo(){
    vector<pair<int, int>> vect_tmp;
    for(int i = 0; i < 3; i++){
        for(unsigned int j =0; j < getPyramide().getNbCartesNiv(i); j++){
            if (getPyramide().getCarte(i, j)!=nullptr) {
                if(verifAchatCarte(getPyramide().getCarte(i, j)))
                    vect_tmp.push_back(std::make_pair(i, j));
            }
        }
    }
    return vect_tmp;
}




vector<pair<Couleur, int>> Controller::GenereCarteResaDispo(){
    vector<pair<Couleur, int>> vect_tmp;
    for (const auto& couleurCartesPair : joueurCourant->cartesReservees) {
        Couleur couleur = couleurCartesPair.first;
        if (couleur != Couleur::OR) {
            const std::vector<const Carte*>& cartes = couleurCartesPair.second;
            for (unsigned int i = 0; i < cartes.size(); i++) {
                if (verifAchatCarte(cartes[i])) {
                    vect_tmp.push_back(std::make_pair(couleur, i));
                }
            }
        }
    }
    return vect_tmp;
}




///////////////////////////////////////////////////////////////////////////////////
///////// Méthodes qui restent à implementer de manière fonctionnelle /////////////
///////////////////////////////////////////////////////////////////////////////////




bool Controller::verifAchatCarte(const Carte* carte) {
    // recup des points necessaires pour acheter la carte
    int needBlanc =  carte->getPrix().getBlanc() ;
    int needBleu =  carte->getPrix().getBleu();
    int needVert =  carte->getPrix().getVert();
    int needRouge =  carte->getPrix().getRouge();
    int needNoir =  carte->getPrix().getNoir();
    int needPerle = carte->getPrix().getPerle();

    // recup des nb de jetons du joueur

    unsigned int nbBlanc = 0;
    auto itBlanc = joueurCourant->jetons.find(Couleur::BLANC);
    if (itBlanc != joueurCourant->jetons.end()) {
        nbBlanc = itBlanc->second.size();

        auto itBonusBlanc = joueurCourant->bonus.find(Couleur::BLANC);
        if (itBonusBlanc != joueurCourant->bonus.end()) {
            needBlanc -= itBonusBlanc->second;
            if(needBlanc < 0)
                needBlanc=0;
        }
    }

    unsigned int nbBleu = 0;
    auto itBleu = joueurCourant->jetons.find(Couleur::BLEU);
    if (itBleu != joueurCourant->jetons.end()) {
        nbBleu = itBleu->second.size();

        auto itBonusBleu = joueurCourant->bonus.find(Couleur::BLEU);
        if (itBonusBleu != joueurCourant->bonus.end()) {
            needBleu -= itBonusBleu->second;
            if(needBleu < 0)
                needBleu=0;
        }
    }

    unsigned int nbVert = 0;
    auto itVert = joueurCourant->jetons.find(Couleur::VERT);
    if (itVert != joueurCourant->jetons.end()) {
        nbVert = itVert->second.size();

        auto itBonusVert = joueurCourant->bonus.find(Couleur::VERT);
        if (itBonusVert != joueurCourant->bonus.end()) {
            needVert -= itBonusVert->second;
            if(needVert < 0)
                needVert=0;
        }
    }

    unsigned int nbRouge = 0;
    auto itRouge = joueurCourant->jetons.find(Couleur::ROUGE);
    if (itRouge != joueurCourant->jetons.end()) {
        nbRouge = itRouge->second.size();

        auto itBonusRouge = joueurCourant->bonus.find(Couleur::ROUGE);
        if (itBonusRouge != joueurCourant->bonus.end()) {
            needRouge -= itBonusRouge->second;
            if(needRouge < 0)
                needRouge=0;
        }
    }

    unsigned int nbNoir = 0;
    auto itNoir = joueurCourant->jetons.find(Couleur::NOIR);
    if (itNoir != joueurCourant->jetons.end()) {
        nbNoir = itNoir->second.size();

        auto itBonusNoir = joueurCourant->bonus.find(Couleur::NOIR);
        if (itBonusNoir != joueurCourant->bonus.end()) {
            needNoir -= itBonusNoir->second;
            if(needNoir < 0)
                needNoir=0;
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
        return true;  // Le joueur a suffisamment de jetons pour acheter la carte
    }

    // 5. Si pas assez, essayer avec les jetons or
    unsigned int jetonsOrUtilises = 0;

    // Fonction pour ajouter des jetons or a une couleur donnee
    auto ajouterJetonsOr = [&jetonsOrUtilises, &nbOr](unsigned int& nbCouleur, int& besoin) {
        while (nbOr > 0 && besoin > nbCouleur) {
            // Utiliser un jeton or pour completer le besoin
            nbOr--;
            //nbCouleur++;
            jetonsOrUtilises++;
            besoin--;
        }
        if(besoin < 0)
            besoin = 0;
    };

    ajouterJetonsOr(nbBlanc, needBlanc);
    ajouterJetonsOr(nbBleu, needBleu);
    ajouterJetonsOr(nbVert, needVert);
    ajouterJetonsOr(nbRouge, needRouge);
    ajouterJetonsOr(nbNoir, needNoir);
    ajouterJetonsOr(nbPerle, needPerle);

    // Verifier a nouveau si le joueur a maintenant assez de points pour acheter la carte
    if (needBlanc <= nbBlanc && needBleu <= nbBleu && needVert <= nbVert &&
        needRouge <= nbRouge && needNoir <= nbNoir && needPerle <= nbPerle)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
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

void Controller::verifTroisCarteReserve(){
    if(joueurCourant->getNbCartesReservees() == 3)
        throw SplendorException("\nVous avez deja 3 cartes reservees\n");
}

bool Controller::verifTroisCarteReserveBool(){
    if(joueurCourant->getNbCartesReservees() == 3)
        return true;
    return false;
}

void Controller::verifJetonSupDix(){
    qDebug()  << "Verification que le joueur courant n'a pas plus de 10 jetons dans sa main\n";
    while(joueurCourant->getNbJetons() > 10){
        qDebug()  << "Vous devez reposer des jetons dans le sac : \n";
        qDebug()  << "Choisissez une couleur parmi : \n";
        for (auto& couleur : Couleurs){
            if (couleur != Couleur::INDT)
                qDebug()  << static_cast<int>(couleur)+1 << " - " << toStringCouleur(couleur) << "\n";
        }
        unsigned int choix = strategy_courante->choix_min_max(1, 7);
        Couleur choix_c = static_cast<Couleur>(choix-1);
        if (joueurCourant->getNbJetons(choix_c) == 0)
            qDebug()  << "Vous n'avez pas de jetons de cette couleur !\n";
        else{
            joueurCourant->supJetonNb(1, choix_c, getEspaceJeux());
        }
    }
}

vector<int> Controller::verifActionsImpossibles(){
    vector<int> res;
    bool peut_recup = true;
    bool peut_resa = true;
    bool peut_achat = true;
    if(getPlateau().estVide() || getPlateau().contientOnlyOr())
        peut_recup = false;
    if(getPlateau().contientOr() == false || joueurCourant->getNbCartesReservees() == 3)
        peut_resa = false;
    if(peut_recup)
        res.push_back(1);
    res.push_back(2);
    if(peut_resa)
        res.push_back(3);
    return res;
    // on boucle sur chaque carte de la pyramide

    // on boucle sur chaque carte des cartes réservées
}





//////////////////////////////////////////////////////////////
///////////// Verif de la partie graphique ///////////////////
//////////////////////////////////////////////////////////////

std::pair<bool, QString> Controller::verifJetonOr(std::pair<int, int> coord){
    /*if(!coord.first && !coord.second){
        auto output = std::make_pair(false, "Veuillez selectionner UN jeton or.");
        return output;
    }*/
    auto output = std::make_pair(true, "");
    return output;
}

//TODO
std::pair<bool, QString> Controller::verifJetons(const std::vector<std::pair<int, int>>& coord, bool capa, Couleur coulBonus){
    std::vector<std::pair<int, int>> coord_tmp = coord;
    unsigned int nbJetons = coord.size();

    if(nbJetons == 0){
        auto output = std::make_pair(false, "Veuillez selectionner des jetons");
        return output;
    }
    // Verifier que les jetons sont adjacents
    if (nbJetons > 1) {
        bool result1 = true;
        bool result2 = true;
        bool result3 = true; // Diago 1
        bool result4 = true; // Diago 2

        // Verif que les jetons sont adjacents en ligne
        for (unsigned int i = 0; i < nbJetons-1; i++) {
            if (coord[i].first != coord[i + 1].first) {
                result1 = false;
            }
        }
        // verif qu'ils ne sont pas distants de + d'une case
        if(result1){
            int max = coord[0].second;
            int min = coord[0].second;
            for (unsigned int i = 1; i < nbJetons; i++) {
                if(coord[i].second > max)
                    max = coord[i].second;
                if(coord[i].second < min)
                    min = coord[i].second;
            }
            if (abs(max - min)  > 2 && nbJetons==3)
                result1 = false;
            if(abs(max-min) >1 && nbJetons==2)
                result1 = false;
        }
        // Verif que les jetons sont adjacents en colonne
        for (unsigned int i = 0; i < nbJetons-1; i++) {
            if (coord[i].second != coord[i + 1].second) {
                result2 = false;
            }
        }
        // verif qu'ils ne sont pas distants de + d'une case
        if(result2){
            int max = coord[0].first;
            int min = coord[0].first;
            for (unsigned int i = 0; i < nbJetons-1; i++) {
                for (unsigned int i = 1; i < nbJetons; i++) {
                    if(coord[i].first > max)
                        max = coord[i].first;
                    if(coord[i].second < min)
                        min = coord[i].first;
                }
                if (abs(max - min)  > 2 && nbJetons==3)
                    result2 = false;
                if(abs(max-min) >1 && nbJetons==2)
                    result2 = false;
            }
        }

        auto comparaison = [](const auto& a, const auto& b) {
            return a.first < b.first;
        };
        std::sort(coord_tmp.begin(), coord_tmp.end(), comparaison);
        //diagonales
        // il manque la verification que les jetons ne sont pas distants de + d'une case
        for (unsigned int i = 0; i < nbJetons-1; i++) {
            // premiere diagonale
            if ((coord_tmp[i].first+1 != coord_tmp[i + 1].first) || (coord_tmp[i].second-1 != coord_tmp[i + 1].second)) {
                result3 = false;
            }
        }
        for (unsigned int i = 0; i < nbJetons-1; i++) {
            // seconde diagonale
            if ((coord_tmp[i].first+1 != coord_tmp[i + 1].first) || (coord_tmp[i].second+1 != coord_tmp[i + 1].second)) {
                result4 = false;
            }
        }

        if(result3 || result4){
            int max = coord[0].second;
            int min = coord[0].second;
            for (unsigned int i = 1; i < nbJetons; i++) {
                if(coord[i].second > max)
                    max = coord[i].second;
                if(coord[i].second < min)
                    min = coord[i].second;
            }
            if (abs(max - min)  > 2 && nbJetons==3){
                if(result3)
                    result3 = false;
                if(result4)
                    result4 = false;
            }
            if (abs(max - min)  > 1 && nbJetons==2){
                if(result3)
                    result3 = false;
                if(result4)
                    result4 = false;
            }

            max = coord[0].first;
            min = coord[0].first;
            for (unsigned int i = 0; i < nbJetons-1; i++) {
                if(coord[i].first > max)
                    max = coord[i].first;
                if(coord[i].second < min)
                    min = coord[i].first;
                }
            if (abs(max - min)  > 2 && nbJetons==3){
                if(result3)
                    result3 = false;
                if(result4)
                    result4 = false;
            }
            if (abs(max - min)  > 1 && nbJetons==2){
                if(result3)
                    result3 = false;
                if(result4)
                    result4 = false;
            }
        }

        if (!result1 && !result2 && !result3 && !result4) {
            auto output = std::make_pair(false, "\nLes jetons ne sont pas adjacents");
            return output;
        }
    }

    for (unsigned int k = 0; k < nbJetons; k++){
        if (getPlateau().caseVide(coord[k].first, coord[k].second) || getPlateau().caseOr(coord[k].first, coord[k].second)){
            auto output = std::make_pair(false, "Il y a une case vide ou un jeton Or dans votre selection");
            return output;
        }
    }
    auto output = std::make_pair(true, "");
    return output;
}

std::pair<bool, QString> Controller::verifReservationCarte(std::pair<int, int> coord){
    //const Carte* carte = getPyramide().getCarte(coord.first, coord.second);

    //verifTroisCarteReserve();
    //verifOrSurPlateau();

    if(verifTroisCarteReserveBool() ){
        return std::make_pair(false, "Vous ne pouvez resever la carte, vous avez deja 3 cartes dans votre reserve");
    }
    // A modifier pour vois si on a bien un jeton Or
    if(verifTroisCarteReserveBool() ){
        return std::make_pair(false, "Vous ne pouvez resever la carte avec vous avez deja 3 cartes dans votre reserve");
    }

    return std::make_pair(true, "Vous pouvez reserver cette carte !");
}

std::pair<bool, QString> Controller::verifReservationCartePioche(int nivPioche){
    //const Carte* carte = getPyramide().getCarte(coord.first, coord.second);

    //verifTroisCarteReserve();
    //verifOrSurPlateau();

    if(verifTroisCarteReserveBool() ){
        return std::make_pair(false, "Vous ne pouvez resever la carte, vous avez deja 3 cartes dans votre reserve");
    }
    // A modifier pour vois si on a bien un jeton Or
    if(verifTroisCarteReserveBool() ){
        return std::make_pair(false, "Vous ne pouvez resever la carte avec vous avez deja 3 cartes dans votre reserve");
    }

    return std::make_pair(true, "Vous pouvez reserver cette carte !");
}



std::pair<bool, QString> Controller::verifAchatCarte(std::pair<int, int> coord){

    const Carte* carte = getPyramide().getCarte(coord.first, coord.second);

    if((carte->getCapacite1() == Capacite::AssociationBonus || carte->getCapacite2() == Capacite::AssociationBonus) && joueurCourant->getNbCartes() == 0){
        return std::make_pair(false, "Vous ne pouvez pas acheter une carte avce la capacité Association Bonus tant que vous n'avez pas de carte au bonus défini");
    }
    // recup des points necessaires pour acheter la carte
    int needBlanc =  carte->getPrix().getBlanc() ;
    int needBleu =  carte->getPrix().getBleu();
    int needVert =  carte->getPrix().getVert();
    int needRouge =  carte->getPrix().getRouge();
    int needNoir =  carte->getPrix().getNoir();
    int needPerle = carte->getPrix().getPerle();

    // recup des nb de jetons du joueur

    unsigned int nbBlanc = 0;
    auto itBlanc = joueurCourant->jetons.find(Couleur::BLANC);
    if (itBlanc != joueurCourant->jetons.end()) {
        nbBlanc = itBlanc->second.size();

        auto itBonusBlanc = joueurCourant->bonus.find(Couleur::BLANC);
        if (itBonusBlanc != joueurCourant->bonus.end()) {
            needBlanc -= itBonusBlanc->second;
            if(needBlanc < 0)
                needBlanc=0;
        }
    }

    unsigned int nbBleu = 0;
    auto itBleu = joueurCourant->jetons.find(Couleur::BLEU);
    if (itBleu != joueurCourant->jetons.end()) {
        nbBleu = itBleu->second.size();

        auto itBonusBleu = joueurCourant->bonus.find(Couleur::BLEU);
        if (itBonusBleu != joueurCourant->bonus.end()) {
            needBleu -= itBonusBleu->second;
            if(needBleu < 0)
                needBleu=0;
        }
    }

    unsigned int nbVert = 0;
    auto itVert = joueurCourant->jetons.find(Couleur::VERT);
    if (itVert != joueurCourant->jetons.end()) {
        nbVert = itVert->second.size();

        auto itBonusVert = joueurCourant->bonus.find(Couleur::VERT);
        if (itBonusVert != joueurCourant->bonus.end()) {
            needVert -= itBonusVert->second;
            if(needVert < 0)
                needVert=0;
        }
    }

    unsigned int nbRouge = 0;
    auto itRouge = joueurCourant->jetons.find(Couleur::ROUGE);
    if (itRouge != joueurCourant->jetons.end()) {
        nbRouge = itRouge->second.size();

        auto itBonusRouge = joueurCourant->bonus.find(Couleur::ROUGE);
        if (itBonusRouge != joueurCourant->bonus.end()) {
            needRouge -= itBonusRouge->second;
            if(needRouge < 0)
                needRouge=0;
        }
    }

    unsigned int nbNoir = 0;
    auto itNoir = joueurCourant->jetons.find(Couleur::NOIR);
    if (itNoir != joueurCourant->jetons.end()) {
        nbNoir = itNoir->second.size();

        auto itBonusNoir = joueurCourant->bonus.find(Couleur::NOIR);
        if (itBonusNoir != joueurCourant->bonus.end()) {
            needNoir -= itBonusNoir->second;
            if(needNoir < 0)
                needNoir=0;
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
        return std::make_pair(true, "Vous pouvez acheter la carte");  // Le joueur a suffisamment de jetons pour acheter la carte
    }

    // 5. Si pas assez, essayer avec les jetons or
    unsigned int jetonsOrUtilises = 0;

    // Fonction pour ajouter des jetons or a une couleur donnee
    auto ajouterJetonsOr = [&jetonsOrUtilises, &nbOr](unsigned int& nbCouleur, int& besoin) {
        while (nbOr > 0 && besoin > nbCouleur) {
            // Utiliser un jeton or pour completer le besoin
            nbOr--;
            //nbCouleur++;
            jetonsOrUtilises++;
            besoin--;
        }
        if(besoin < 0)
            besoin = 0;
    };

    ajouterJetonsOr(nbBlanc, needBlanc);
    ajouterJetonsOr(nbBleu, needBleu);
    ajouterJetonsOr(nbVert, needVert);
    ajouterJetonsOr(nbRouge, needRouge);
    ajouterJetonsOr(nbNoir, needNoir);
    ajouterJetonsOr(nbPerle, needPerle);

    // Verifier a nouveau si le joueur a maintenant assez de points pour acheter la carte
    if (needBlanc <= nbBlanc && needBleu <= nbBleu && needVert <= nbVert &&
        needRouge <= nbRouge && needNoir <= nbNoir && needPerle <= nbPerle)
    {
        return std::make_pair(true, "Vous pouvez acheter la carte avec"+QString::number(jetonsOrUtilises)+"jetons Or");
    }
    else
    {
        return std::make_pair(false, "Vous n'avez pas assez de jetons pour acheter cette carte");
    }
    return std::make_pair(false, "Vous n'avez pas assez de jetons pour acheter cette carte");
}




vector<int> Controller::verifActionsOptImpossibles(){
    vector<int> res;
    bool peut_privilege = true;
    bool peut_remplir_plateau = true;
    if(joueurCourant->getNbPrivileges() == 0)
        peut_privilege = false;
    if(getEspaceJeux().getSac().estVide() && joueurCourant->getNbJetons() <= 10)
        peut_remplir_plateau = false;
    if(peut_privilege)
        res.push_back(1);
    if(peut_remplir_plateau)
        res.push_back(2);
    res.push_back(3);
    return res;
}





void  Controller::Tour_ia() {
    bool a_deja_utilise_privilege = false;
    bool a_deja_rempli_plateau = false;
    unsigned int etat_tour = 0;

    while (etat_tour != 10) {
        bool tourEnPlus = false;
        // actions optionelles
        switch (etat_tour) {
        case 0: {
            unsigned int etat_action = 0;
            while (etat_action != 10) {
                switch (etat_action) {
                case 0: {
                    // affichage de l'etat en cours
                    qDebug() << "C'est a " << getJoueurCourant().getPseudo() << " de jouer : \n";
                    qDebug() << "Nous en sommes au tour : " << getPartie().getTour() + 1 << "\n";

                    // appel du menu de choix des actions
                    getJoueurCourant().afficherJoueur();
                    etat_action = choixActionsOptionelles();
                    qDebug() << etat_action;
                    break;
                }
                case 1: {
                    try {
                        // utilisation d'un privilege
                        if (a_deja_utilise_privilege) throw SplendorException("Vous avez deja utilise cette action");
                        utiliserPrivilege(getPartie().getEspaceJeux().getPlateau());
                        a_deja_utilise_privilege = true;
                        etat_action = 0;
                    } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_action = 0; }
                    break;
                }
                case 2: {
                    try {
                        // remplissage du plateau
                        if (a_deja_rempli_plateau) throw SplendorException("Vous avez deja utilise cette action");
                        remplirPlateau(getPartie().getEspaceJeux().getPlateau(), getPartie().getEspaceJeux().getSac());
                        a_deja_rempli_plateau = true;
                        etat_action = 0;
                    } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_action = 0; }
                    break;
                }
                case 3: {
                    etat_tour = 1;
                    etat_action = 10;
                    break;
                }
                case 9: {
                    quitter();
                    return;
                }
                default: {
                    etat_action = 0;
                    qDebug() << "Veuillez faire un choix correct !\n";
                    break;
                }
                }
            }
            break;
        }
        // actions obligatoires :
        case 1: {
            unsigned int etat_action = 0;
            while (etat_action != 10) {
                switch (etat_action) {
                case 0:
                    // menu de choix des actions obligatoires
                    etat_action = choixActionsObligatoires();
                    qDebug() << etat_action;
                    break;
                case 1:
                    try {
                        // recuperation de jetons
                        qDebug() << joueurCourant->getPseudo();
                        recupererJetons(false);
                        etat_action = 10;
                        etat_tour = 2;
                    } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_tour = 0; etat_action = 10; }
                    break;
                case 2:
                    try {
                        // achat carte joaillerie
                        tourEnPlus = acheterCarteJoaillerie(getPartie().getEspaceJeux());
                        if (tourEnPlus) { etat_tour = 0; etat_action = 0; }
                        else { etat_action = 10; etat_tour = 2; }
                    } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_tour = 0; etat_action = 10; }
                    break;
                case 3:
                    try {
                        // reservation carte
                        orReserverCarte(getPartie().getEspaceJeux().getPyramide(), getPartie().getEspaceJeux().getPlateau());
                        etat_action = 10;
                        etat_tour = 2;
                    } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n' << '\n'; etat_tour = 0; etat_action = 10; }
                    break;
                case 9: {
                    quitter();
                    return;
                }
                default:
                    etat_action = 0;
                    qDebug() << "Veuillez faire un choix correct !\n";
                    break;
                }
            }
            break;
        }
        // verification fin de tour d'un joueur
        case 2: {
            // achat obligatoire d'une carte noble si le joueur a 3 pts et 0 cartes nobles ou 6 pts de prestige et 1 carte noble
            while ((getJoueurCourant().getNbCouronnes() >= 3 && getJoueurCourant().getNbCartesNobles() == 0) ||
                   (getJoueurCourant().getNbCouronnes() >= 6 && getJoueurCourant().getNbCartesNobles() == 1)) {
                try { acheterCarteNoble(getPartie().getEspaceJeux().getPyramide()); } catch (SplendorException& e) { qCritical() << "\033[1;31m" << e.getInfo() << "\033[0m" << '\n'; };
            }

            verifJetonSupDix();

            // Conditions victoires :
            if (getJoueurCourant().getNbCouronnes() >= 10) getJoueurCourant().setGagnant();
            if (getJoueurCourant().getptsPrestige() >= 20) getJoueurCourant().setGagnant();
            if (getJoueurCourant().nbPtsPrestigeParCouleurSupDix()) getJoueurCourant().setGagnant();

            //Sauvegarde automatique
            if (getPartie().getTour()==30) {
                sauvegardePartie();
            }

            // Fin de partie :
            if (getJoueurCourant().estGagnant())
                etat_tour = 3;
            else{                //fin du tour du joueur, on passe au joueur suivant
                changerJoueurCourantGraphique();
                etat_tour = 10;
            }
            break;
        }
        case 3: {

            //enregistrement des score
            qDebug() << "Enregistrement des score...\n";
            enregisterScore();
            qDebug() << "DONE\n";

            //std::cout << "Fin de la partie !\n";
            return;
            break;
        }
        default: {
            break;
        }
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
        qCritical() << "Erreur lors de la connexion a la base de donnee\n";

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
        qDebug() << "Sauvegarde joueur : " << i+1 << "...\n" ;
        qDebug() << "Sauvegarde des infos\n";
        // Infos du joueur
        QString sql = "INSERT INTO joueur (id, pseudo, type_joueur, privileges, ptsPrestige, nbCouronnes) VALUES (" +
                      QString::number(i + 1) + ", '" +
                      QString::fromStdString(getPartie().getJoueur(i)->getPseudo()) + "', '" +
                      QString::fromStdString(toStringType(getPartie().getJoueur(i)->getTypeDeJoueur())) + "', " +
                      QString::number(getPartie().getJoueur(i)->getNbPrivileges()) + ", " +
                      QString::number(getPartie().getJoueur(i)->getptsPrestige()) + ", " +
                      QString::number(getPartie().getJoueur(i)->getNbCouronnes()) +
                      ");";
        if (!query.exec(sql)) {
            qCritical() << "Erreur lors de la sauvegarde du joueur \n";

            db.close();
            return;
        }
        qDebug() << "Sauvegarde des jetons\n";
        // Jetons (toutes les couleurs sauf indt)
        for (Couleur c : Couleurs) {
            if (c != Couleur::INDT) {
                for (size_t j = 0; j < getPartie().getJoueur(i)->getNbJetons(c); j++) {
                    QString id_joueur = QString::number(i + 1);
                    QString couleur = QString::fromStdString(toStringCouleur(c));

                    sql = "INSERT INTO jetons_joueur (id_joueur, couleur) VALUES (" + id_joueur + ", '" + couleur + "')";
                    if (!query.exec(sql)) {
                        qCritical() << "Erreur lors de la sauvegarde du jeton \n";

                        db.close();
                        return;
                    }
                }
            }
        }
        qDebug() << "Sauvegarde des cartes\n";
        // Cartes (toutes les couleurs sauf or)
        for (Couleur c : Couleurs) {
            if (c != Couleur::OR) {
                for (size_t j = 0; j < getPartie().getJoueur(i)->getNbCartes(c); j++) {
                    //si la carte est de couleur indt mais rangés dans le vecteur d'une autre couleur -> bonus : AssociationBonus, il faut donc le sauvegarder
                    if (getPartie().getJoueur(i)->getCarte(c, j).getBonus().getCouleur()!=c) {
                        //on push la couleur c de la map dans laquelle la carte est rangés
                        sql = "INSERT INTO cartes_joueur (id_joueur, id_carte, noble, reserve, couleur_associe) VALUES (" + QString::number(i + 1) + ", " + QString::number(getPartie().getJoueur(i)->getCarte(c, j).getId()) + ",0,0," + QString::number(static_cast<int>(c)) + ");";
                    } else {
                        //on push null sinon
                        sql = "INSERT INTO cartes_joueur (id_joueur, id_carte, noble, reserve, couleur_associe) VALUES (" + QString::number(i + 1) + ", " + QString::number(getPartie().getJoueur(i)->getCarte(c, j).getId()) + ",0,0,NULL);";
                    }
                    qDebug() << sql;
                    if (!query.exec(sql)) {
                        qCritical() << "Erreur lors de la sauvegarde de la carte noble \n";

                        db.close();
                        return;
                    }
                }
            }
        }
        qDebug() << "Sauvegarde des cartes nobles\n";
        // Cartes nobles
        for (size_t j = 0; j < getPartie().getJoueur(i)->getNbCartesNobles(); j++) {
            sql = "INSERT INTO cartes_joueur (id_joueur, id_carte, noble, reserve, couleur_associe) VALUES (" + QString::number(i + 1) + ", " + QString::number(getPartie().getJoueur(i)->getCarteNoble(j).getId()) + ",1,0,NULL);";
            qDebug() << sql;
            if (!query.exec(sql)) {
                qCritical() << "Erreur lors de la sauvegarde de la carte noble \n";

                db.close();
                return;
            }
        }
        qDebug() << "Sauvegarde des cartes réservées\n";
        // Cartes reservees (toutes les couleurs sauf et or)
        for (Couleur c : Couleurs) {
            if (c != Couleur::OR) {
                for (size_t j = 0; j < getPartie().getJoueur(i)->getNbCartesReservees(c); j++) {
                    sql = "INSERT INTO cartes_joueur (id_joueur, id_carte, noble, reserve, couleur_associe) VALUES (" + QString::number(i + 1) + ", " + QString::number(getPartie().getJoueur(i)->getCarteReservee(c, j).getId()) + ",0,1,NULL);";
                    qDebug() << sql;
                    if (!query.exec(sql)) {
                        qCritical() << "Erreur lors de la sauvegarde de la carte reservés \n";

                        db.close();
                        return;
                    }
                }
            }
        }
        qDebug()<< "DONE \n";
    }

    qDebug() << "Sauvegarde plateau... \n";

    // Sauvegarde plateau
    Plateau& plateau = getPartie().getEspaceJeux().getPlateau();
    for (size_t i = 0; i < plateau.getLargeurMatrice(); i++) {
        for (size_t j = 0; j < plateau.getLargeurMatrice(); j++) {
            if (plateau.getJeton(i, j) != nullptr) {
                QString sql = "INSERT INTO plateau (i, j, couleur) VALUES (" + QString::number(i) + ", " + QString::number(j) + ", '" + QString::fromStdString(toStringCouleur(plateau.getJeton(i, j)->getCouleur())) + "');";
                if (!query.exec(sql)) {
                    qCritical() << "Erreur lors de la sauvegarde du plateau\n";

                    db.close();
                    return;
                }
            }
        }
    }

    qDebug() << "DONE \n";

    qDebug() << "Sauvegarde pyramide... \n";

   // Sauvegarde de la pyramide
    Pyramide& pyramide = getPartie().getEspaceJeux().getPyramide();
    for (int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < pyramide.getNbCartesNiv(i); j++) {
            const Carte* carte = pyramide.getCarte(i, j);

            if (carte != nullptr) {
                QString sql = "INSERT INTO pyramide (i, j, id) VALUES (" + QString::number(i) + ", " + QString::number(j) + ", " + QString::number(carte->getId()) + ");";
                if (!query.exec(sql)) {
                    qCritical() << "Erreur lors de la sauvegarde de la pyramide\n";

                    db.close();
                    return;
                }
            }
        }
    }

    qDebug() << "DONE \n";

    qDebug() << "Sauvegarde des infos de la partie... \n";

   //Sauvegarde des infos de la partie
    int joueurCourant = 0;
    if (getPartie().getJoueur2() == this->joueurCourant) {
        joueurCourant = 1;
    }
    int tour = getPartie().getTour();
    QString sql = "INSERT INTO infopartie (tour, joueurCourant) VALUES (" + QString::number(tour) + ", " + QString::number(joueurCourant) + ");";
    if (!query.exec(sql)) {
        qCritical() << "Erreur lors de la sauvegarde des infos de la partie\n";

        db.close();
        return;
    }

    qDebug() << "DONE \n";

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
        qCritical() << "Erreur lors de la connexion a la base de donnee\n";

        return;
    }

    QSqlQuery query(db);
    for (int i = 0; i < 2; i++) {
        // On regarde si le joueur existe deja
        QString sql = "SELECT * FROM score WHERE pseudo = '" + QString::fromStdString(getPartie().getJoueur(i)->getPseudo()) + "';";
        if (!query.exec(sql)) {
            qCritical() << "Erreur lors de la recherche du joueur dans la base de donnee\n";

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
            qDebug() << sql.toStdString() << '\n';
            if (!query.exec(sql)) {
                qCritical() << "Erreur lors de la mise a jour du score du joueur\n";

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
            qDebug() << sql.toStdString() << '\n';
            if (!query.exec(sql)) {
                qCritical() << "Erreur lors de l'ajout du joueur dans la base de donnee\n";

                db.close();
            }
        }
    }

    db.close();
}

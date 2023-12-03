#include "controller.hpp"

Controller::Controller() {
    //Choix du type de partie
    //Choix du type de partie
	Director* director = new Director();
	string statut_partie;
	std::cout << "Ancienne ou nouvelle partie ? (New/Old)" << std::endl;
	std::cin >> statut_partie;
    //Si nouvelle partie

    //Si nouvelle partie
	if (statut_partie == "New") {
		NewPartieBuilder* builder = new NewPartieBuilder();
		director->set_builder(builder);
		cout << "Combien de joueur voulez vous jouer ? (0,1,2)" << std::endl;
		int nbJoueur;
		cin >> nbJoueur;
        switch (nbJoueur) {
        case 0:
        {   cout << "IA vs IA" << std::endl;
            director->BuildNewPartie("Alain Telligence", type::IA, "Al Gorythme", type::IA);
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
            director->BuildNewPartie(pseudo, type::HUMAIN, "Al Gorythme", type::IA);
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
    
    //Si ancienne partie :

        //Si ancienne partie :
	} else if (statut_partie == "Old") {
        //Création

        //Création
        LastPartieBuilder* builder = new LastPartieBuilder();
        director->set_builder(builder);
        director->BuildLastPartie();
        Partie* p = builder->GetProduct();
        partie = p;
        delete director;
        
        
        //restitution
        sqlite3* db;
        sqlite3_stmt* stmt;
        //std::string relativePath = "data/save.sqlite";
        //std::filesystem::path absolutePath = projectPath / relativePath;
        //std::string absolutePathStr = absolutePath.string();

        int rc = sqlite3_open("data/save.sqlite", &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Impossible d'ouvrir la base de donnees 8: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        rc = sqlite3_prepare_v2(db, "SELECT * FROM 'infopartie'", -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Erreur de preparation de la requete 9: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int joueur_c = sqlite3_column_int(stmt, 1);
            if (joueur_c == 0) {
                joueurCourant = partie->getJoueur1();
            }
            else if (joueur_c == 1) {
                joueurCourant = partie->getJoueur2();
            }
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    } else {
        throw SplendorException("Veuillez entrer un statut valide (New ou Old)");
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
        cout << "#### c'est " << partie->getJoueur1()->getPseudo() << " qui commence, son adversaire recoit 1 privilege !####\n";
        partie->getJoueur2()->addPrivilege(partie->getEspaceJeux().getPlateau().recupererPrivilege());
        break;
    case 1:
        cout << "#### c'est " << partie->getJoueur2()->getPseudo() << " qui commence, son adversaire recoit 1 privilege !####\n";
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

void Controller::tour_suivant() {
    // verifs
    if (joueurCourant == partie->getJoueur2())
        joueurCourant = partie->getJoueur1();
    else
        joueurCourant = partie->getJoueur2();
    partie->incrementeTour();
}


///////////////////////// Actions d'un joueur /////////////////////////

bool Controller::verifAchatCarte(const Carte& carte, EspaceJeux& espaceJeux) {
    // 1 recuperer les points nécessaires pour acheter la carte
    // 2 voir le nb de jetons par couleur
    // 3 ajouter les bonus
    // 4 voir si le joueur a assez de points pour acheter la carte
    // 5 si pas assez essayer avec les jetons or

    // recup des points nécessaires pour acheter la carte
    unsigned int needBlanc =  carte.getPrix().getBlanc() ;
    unsigned int needBleu =  carte.getPrix().getBleu();
    unsigned int needVert =  carte.getPrix().getVert();
    unsigned int needRouge =  carte.getPrix().getRouge();
    unsigned int needNoir =  carte.getPrix().getNoir();
    unsigned int needPerle = carte.getPrix().getPerle();

    // recup des jetons du joueur
    // Map des bonus associés à chaque couleur

// Map des bonus associés à chaque couleur


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

        // On supprime les jetons utilisés
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

    // Fonction pour ajouter des jetons or à une couleur donnée
    auto ajouterJetonsOr = [&jetonsOrUtilises, &nbOr](unsigned int& nbCouleur, unsigned int besoin) {
        while (nbOr > 0 && besoin > nbCouleur) {
            // Utiliser un jeton or pour compléter le besoin
            nbOr--;
            nbCouleur++;
            jetonsOrUtilises++;
        }
    };

    ajouterJetonsOr(nbBlanc, needBlanc);
    ajouterJetonsOr(nbBleu, needBleu);
    ajouterJetonsOr(nbVert, needVert);
    ajouterJetonsOr(nbRouge, needRouge);
    ajouterJetonsOr(nbNoir, needNoir);
    ajouterJetonsOr(nbPerle, needPerle);

    // Vérifier à nouveau si le joueur a maintenant assez de points pour acheter la carte
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

void Controller::utiliserPrivilege(Plateau& plateau){
    std::cout<<"Utiliser un privilege permet de recup un jeton de couleur ou perle de votre choix (i,j):\n";
    std::cout<<plateau<<endl;
    if (joueurCourant->privileges.empty()) {
        throw SplendorException("Le joueur n'a pas de privilege");
    }
    if (plateau.estVide()){
        throw SplendorException("Le plateau n'a pas de jetons");
    }
    const Privilege& privilege = joueurCourant->supPrivilege(plateau);
    plateau.poserPrivilege(privilege);
    std::pair<unsigned int, unsigned int> coordJetonSelec = strategy_courante->choisirJeton(plateau);
    const Jeton& jetonSelec = plateau.recupererJeton(coordJetonSelec.first, coordJetonSelec.second);
    joueurCourant->addJeton(jetonSelec);

}

void Controller::remplirPlateau(Plateau& plateau, Sac& sac, Joueur& joueurAdverse){
    std::cout<<"Le joueur rempli le plateau :\n"<<plateau<<endl;
    strategy_courante->remplirPlateauStrat(plateau, sac);
    if (joueurCourant->privileges.size() == 3){
        std::cout<< "Vous avez deja 3 privileges. Vous n'en recupererez donc pas plus !" << std::endl;
        return;
    }
    // Verifier s'il reste des privileges sur le plateau
    if (!plateau.pivilegeDisponible()){
        std::cout<< "Il n'y a plus de privileges sur le plateau !\nLe joueur adverse perd donc un privilege..." << std::endl;
        const Privilege& privilege = joueurAdverse.supPrivilege(plateau); // recuperation du privilege du joueur adverse
        joueurCourant->addPrivilege(privilege); // ajout du privilege au joueur
        return;
    }
    // Cas standard
    const Privilege& privilege = plateau.recupererPrivilege();
    joueurCourant->addPrivilege(privilege);
    std::cout<<"Nouveau plateau : \n"<<plateau;
}

void Controller::recupererJetons(Plateau& plateau){
    // Récupération des jetons 1 2 ou 3 jetons en fonction de la strategy
    std::vector<const Jeton*> jetonsRecup = strategy_courante->recupJetonStrat(plateau);

    // ajout des jetons dans la main du joueur
    for (auto & i : jetonsRecup){
        joueurCourant->addJeton(*i);
    }

}

void Controller::orReserverCarte (Pyramide& pyramide, Plateau& plateau){
    unsigned int choix = strategy_courante->choixNiveau();


    if (choix == 0){
        // Reservation de la carte
        std::pair<unsigned int, unsigned int> numNivCarteSelec = strategy_courante->reservationCarte(pyramide);

        const Carte& carte = pyramide.acheterCarte(numNivCarteSelec.first, numNivCarteSelec.second);
        joueurCourant->addCarteReservee(carte);

        // Recuperation d'un jeton or Voir exception mécanique de jeu
        // Recuperation d'un jeton or
        std::pair<unsigned int, unsigned int> coordJetonSelec = strategy_courante->choisirJeton(plateau);
        const Jeton& jeton = plateau.recupererJeton(coordJetonSelec.first, coordJetonSelec.second);
        if(jeton.getCouleur() != Couleur::OR){
            throw SplendorException("Le jeton choisi n'est pas un jeton or");
        }
        joueurCourant->addJeton(jeton);


    }
    else if (choix == 1 || choix == 2 || choix == 3){
        // Reservation de la carte
        const Carte& carte = pyramide.ReserverCartePioche(choix);
        joueurCourant->addCarteReservee(carte);

        // Recuperation d'un jeton or
        std::pair<unsigned int, unsigned int> coordJetonSelec = strategy_courante->choisirJeton(plateau);
        const Jeton& jeton = plateau.recupererJeton(coordJetonSelec.first, coordJetonSelec.second);
        if(jeton.getCouleur() != Couleur::OR){
            throw SplendorException("Le jeton choisi n'est pas un jeton or");
        }
        joueurCourant->addJeton(jeton);
    }


}

void Controller::acheterCarteNoble (Pyramide& pyramide){
    // affichage cartes nobles
    pyramide.afficherPyramide();

    std::pair< unsigned int, unsigned int> carteDescr = strategy_courante->achatNoble(pyramide);

    const Carte& carte = pyramide.acheterCarte(4, carteDescr.second);
    joueurCourant->addCarteNoble(carte);
}

void Controller::acheterCarteJoaillerie (EspaceJeux& espaceJeux){
    unsigned int choix = strategy_courante->choixAchat();


    // Achat carte reservee
    if (choix == 1){
        std::cout << "Voici les cartes reservees : " << std::endl;
        unsigned int i = 0;
        // Affichage de la réserve
        for (auto & cartesReservee : joueurCourant->cartesReservees) {
            std::cout <<"Numero "<<i << " : " << std::endl;
            //std::cout<<cartesReservee;
            i++;
        }

        std::pair< Couleur, unsigned int> carteDescr = strategy_courante->achatReserve(joueurCourant->cartesReservees.size());
        if(carteDescr.second > joueurCourant->cartesReservees[carteDescr.first].size() || joueurCourant->cartesReservees[carteDescr.first].size()==0)
            throw SplendorException("vous n'avez pas cette carte dans votre reserve ou la reserve est vide");
        else{
            const Carte& carte = *(joueurCourant->cartesReservees[carteDescr.first][carteDescr.second]);

            if (!verifAchatCarte(carte, espaceJeux)) {
                throw SplendorException("Vous n'avez pas assez de points pour acheter cette carte...");
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
            throw SplendorException("Vous n'avez pas assez de points pour acheter cette carte");
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


///////////////////////// Sauvegarde /////////////////////////

void Controller::sauvegardePartie() {
   //Cette fonction aura pour objectif de push toutes les données importantes de la partie dans la base de donnée
   //Afin de pouvoir reprendre la partie plus tard
   //Pour cela, il faudra créer une base de donnée avec les tables suivantes :
   // joueur1, joueur2, plateau, infopartie, pyramide

   //on ajoute le chemin relatif au chemin absolue du projet
   //std::string relativePath = "data/save.sqlite";
   //std::filesystem::path absolutePath = projectPath / relativePath;
   //std::string absolutePathStr = absolutePath.string();

   //Connexion à la base de donnée
   sqlite3 *db;
   //int rc = sqlite3_open(absolutePathStr.c_str(), &db);
   int rc = sqlite3_open("data/save.sqlite", &db);
   if (rc != SQLITE_OK) {
       std::cerr << "Erreur lors de la connexion à la base de donnée" << std::endl;
       sqlite3_close(db);
       return;
   }

   //Nettoyage de l'ancienne sauvegarde
   string sql = "DELETE FROM joueur; DELETE FROM plateau; DELETE FROM infopartie; DELETE FROM pyramide;";
   rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
   if (rc != SQLITE_OK) {
       std::cerr << "Erreur lors du nettoyage de la base de donnée" << std::endl;
       sqlite3_close(db);
       return;
   }

   //Sauvegarde joueurs
   for(size_t i = 0; i<2; i++) {
       //infos du joueur
       sql = "INSERT INTO joueur (id, pseudo, type_joueur, privileges) VALUES (" + std::to_string(i+1) + ", '" + getPartie().getJoueur(i)->getPseudo() + "', '" + toStringType(getPartie().getJoueur(i)->getTypeDeJoueur()) + "', " +std::to_string(getPartie().getJoueur(i)->getNbPrivileges()) + ");";
       rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
       if (rc != SQLITE_OK) {
           std::cerr << "Erreur lors de la sauvegarde du joueur " << std::endl;
           sqlite3_close(db);
           return;
       }
       
       //jetons (toutes les couleurs sauf indt)
       for (Couleur c : Couleurs){
            if (c!=Couleur::INDT) {
                for (size_t j = 0; j<getPartie().getJoueur(i)->getNbJetons(c); j++) {
                    sql = "INSERT INTO jeton (id_joueur, couleur) VALUES (" + std::to_string(i+1) + ", '" + toStringCouleur(c) + "');";
                    rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
                    if (rc != SQLITE_OK) {
                        std::cerr << "Erreur lors de la sauvegarde du jeton " << std::endl;
                        sqlite3_close(db);
                        return;
                    }
                }
            }
       }

       //cartes (toutes les couleurs sauf ind et or)
         for (Couleur c : Couleurs){
                if (c!=Couleur::INDT && c!=Couleur::OR) {
                 for (size_t j = 0; j<getPartie().getJoueur(i)->getNbCartes(c); j++) {
                      sql = "INSERT INTO carte (id_joueur, id_carte, noble, reservee) VALUES (" + std::to_string(i+1) + ", " + std::to_string(getPartie().getJoueur(i)->getCarte(c,j).getId()) + ",0,0);";
                      rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
                      if (rc != SQLITE_OK) {
                            std::cerr << "Erreur lors de la sauvegarde de la carte " << std::endl;
                            sqlite3_close(db);
                            return;
                      }
                 }
                }
         }

         //cartes nobles
            for (size_t j = 0; j<getPartie().getJoueur(i)->getNbCartesNobles(); j++) {
                sql = "INSERT INTO carte (id_joueur, id_carte, noble, reservee) VALUES (" + std::to_string(i+1) + ", " + std::to_string(getPartie().getJoueur(i)->getCarteNoble(j).getId()) + ",1,0);";
                rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
                if (rc != SQLITE_OK) {
                    std::cerr << "Erreur lors de la sauvegarde de la carte" << std::endl;
                    sqlite3_close(db);
                    return;
                }
            }

         //cartes reservees (toutes les couleurs sauf ind et or)
         for (Couleur c : Couleurs){
                if (c!=Couleur::INDT && c!=Couleur::OR) {
                 for (size_t j = 0; j<getPartie().getJoueur(i)->getNbCartesReservees(c); j++) {
                      sql = "INSERT INTO carte (id_joueur, id_carte, noble, reservee) VALUES (" + std::to_string(i+1) + ", " + std::to_string(getPartie().getJoueur(i)->getCarteReservee(c,j).getId()) + ", " + TypeCartetoString(getPartie().getJoueur(i)->getCarteReservee(c,j).getType()) + ",1);";
                      rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
                      if (rc != SQLITE_OK) {
                            std::cerr << "Erreur lors de la sauvegarde de la carte " << std::endl;
                            sqlite3_close(db);
                            return;
                      }
                 }
                }
         }
   }

   //Sauvegarde plateau
   Plateau& plateau = getPartie().getEspaceJeux().getPlateau();
   for (size_t i =0; i<plateau.getLargeurMatrice(); i++) {
       for (size_t j =0; j<plateau.getLargeurMatrice(); j++) {
           if (plateau.getJeton(i,j) != nullptr) {
               sql = "INSERT INTO plateau (i, j, couleur) VALUES (" + std::to_string(i) + ", " + std::to_string(j) + ", '" + toStringCouleur(plateau.getJeton(i,j)->getCouleur()) + "');";
               rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
               if (rc != SQLITE_OK) {
                   std::cerr << "Erreur lors de la sauvegarde du plateau" << std::endl;
                   sqlite3_close(db);
                   return;
               }
           }
       }
   }

   //Sauvegarde de la pyramide
   Pyramide& pyramide = getPartie().getEspaceJeux().getPyramide();
   for (int i =0; i<4; i++) {
       for (int j =0; j<pyramide.getNbCartesNiv(i); j++) {
           const Carte* carte = pyramide.getCarte(i,j);
           sql= "INSERT INTO pyramide (i, j, id) VALUES (" + std::to_string(i) + ", " + std::to_string(j) + ", " + std::to_string(carte->getId()) + ");";
           rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
           if (rc != SQLITE_OK) {
               std::cerr << "Erreur lors de la sauvegarde de la pyramide" << std::endl;
               sqlite3_close(db);
               return;
           }
       }
   }

   //Sauvegarde des infos de la partie
   //recuperation du joueur courant :
    int joueurCourant = 0;
    if (getPartie().getJoueur2() == this->joueurCourant ){
        joueurCourant = 1;
    }
    int tour = getPartie().getTour();
   sql = "INSERT INTO infopartie (tour, joueurCourant) VALUES (" + std::to_string(tour) + ", " + std::to_string(joueurCourant) + ");";
   rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
   if (rc != SQLITE_OK) {
       std::cerr << "Erreur lors de la sauvegarde des infos de la partie" << std::endl;
       sqlite3_close(db);
       return;
   } 

   //Fermeture de la base de donnée
   sqlite3_close(db);
}

//sauvegarde du score des joueurs à la fin de la partie
void Controller::enregisterScore() {
   //a la fin d'une partie il faut enregistrer le score des joueurs dans la base de donnée
   //on regarde si il existe déjà et on lui ajoute une victoire ou une défaite
   //sinon on le crée et on lui ajoute une victoire ou une défaite

   //on ajoute le chemin relatif au chemin absolue du projet
   //std::string relativePath = "data/score.sqlite";
   //std::filesystem::path absolutePath = projectPath / relativePath;
   //std::string absolutePathStr = absolutePath.string();

   //Connexion à la base de donnée
   sqlite3 *db;
   int rc = sqlite3_open("data/score.sqlite", &db);
   if (rc != SQLITE_OK) {
       std::cerr << "Erreur lors de la connexion à la base de donnée" << std::endl;
       sqlite3_close(db);
       return;
   }

   for (int i = 0; i<2; i++) {
       //on regarde si le joueur existe déjà
       string sql = "SELECT * FROM score WHERE pseudo = '" + getPartie().getJoueur(i)->getPseudo() + "';";
       sqlite3_stmt *stmt;
       rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
       if (rc != SQLITE_OK) {
           std::cerr << "Erreur lors de la recherche du joueur dans la base de donnée" << std::endl;
           sqlite3_close(db);
           return;
       }

       rc = sqlite3_step(stmt);
       if (rc == SQLITE_ROW) {
           //le joueur existe déjà
           //on récupère son nombre de victoire et de défaite
           int nbVictoire = sqlite3_column_int(stmt, 2);
           int nbDefaite = sqlite3_column_int(stmt, 3);
           //on met à jour son nombre de victoire ou de défaite
           if (getPartie().getJoueur(i)->estGagnant()) {
               nbVictoire++;
           }
           else {
               nbDefaite++;
           }
           //on met à jour le score du joueur
           sql = "UPDATE score SET nbVictoire = " + std::to_string(nbVictoire) + ", nbDefaite = " + std::to_string(nbDefaite) + " WHERE pseudo = '" + getPartie().getJoueur(i)->getPseudo() + "';";
           std::cout<<sql<<std::endl;
           rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
           if (rc != SQLITE_OK) {
               std::cerr << "Erreur lors de la mise à jour du score du joueur" << std::endl;
                sqlite3_close(db);
           }
       } else {
        //sinon on ajoute le joueur dans la base de donnée avec le bon score
        int nbVictoire = 0;
        int nbDefaite = 0;
        if (getPartie().getJoueur(i)->estGagnant()) {
            nbVictoire++;
        }
        else {
            nbDefaite++;
        }

        sql = "INSERT INTO score (pseudo, nbVictoire, nbDefaite) VALUES ('" + getPartie().getJoueur(i)->getPseudo() + "', " + std::to_string(nbVictoire) + ", " + std::to_string(nbDefaite) + ");";
        std::cout<<sql<<std::endl;
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
        if (rc != SQLITE_OK) {
            std::cerr << "Erreur lors de l'ajout du joueur dans la base de donnée" << std::endl;
            sqlite3_close(db);
            }
       }
   }

   //Fermeture de la base de donnée
   sqlite3_close(db);
}

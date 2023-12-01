#include "partie.hpp"

Partie::Partie(): espaceJeux(new EspaceJeux()) {
    joueurs[0] = nullptr;
    joueurs[1] = nullptr;
}

// ###########   LastPartieBuilder   #############

void LastPartieBuilder::setJoueurs() const {
    sqlite3 * db;
    sqlite3_stmt * stmt;
    int i = 0;

    //Connexion et ouverte de la base de données
    int rc = sqlite3_open("data/save.sqlite", & db);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees 1: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'joueur'", -1, & stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete joueur: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    //On instancie les 2 anciens joueurs avec leurs privilèges
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string pseudo = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int nb_privileges = sqlite3_column_int(stmt, 3);
        if (type == "IA")
            this -> partie -> joueurs[i] = new Joueur(pseudo, type::IA);
        else
            this -> partie -> joueurs[i] = new Joueur(pseudo, type::HUMAIN);

        for (int j = 0; j < nb_privileges; j++) {
            const Privilege & p = this -> partie -> getEspaceJeux().getPlateau().recupererPrivilege();
            if (i == 0)
                this -> partie -> getJoueur1() -> addPrivilege(p);
            else
                this -> partie -> getJoueur2() -> addPrivilege(p);
        }
        i++;
    }

    //Fermeture de la base de données
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void LastPartieBuilder::setCartesJoueurs() const {
    sqlite3 * db;
    sqlite3_stmt * stmt;
    int i = 0;
    size_t nb_cartes_nv1 = partie -> espaceJeux -> getPyramide().getPioche1().getNbCartes();
    size_t nb_cartes_nv2 = partie -> espaceJeux -> getPyramide().getPioche2().getNbCartes();
    size_t nb_cartes_nv3 = partie -> espaceJeux -> getPyramide().getPioche3().getNbCartes();
    size_t nb_cartes_noble = partie -> espaceJeux -> getPyramide().getPiocheNoble().getNbCartes();

    //Connexion aux bases de données
    int rc = sqlite3_open("data/save.sqlite", & db);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees 2: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    rc = sqlite3_prepare_v2(db, "SELECT id FROM 'joueur'", -1, & stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete  joueur 2: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    //Restitution des cartes des joueurs
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        //Récupération des cartes
        int id_joueur = sqlite3_column_int(stmt, 0);
        string sql = "SELECT cartes_joueur.* FROM 'joueur' JOIN 'cartes_joueur' ON joueur.id = cartes_joueur.id_joueur WHERE joueur.id = '" + to_string(id_joueur) + "';";
        sqlite3_stmt * stmt2;

        int rc2 = sqlite3_prepare_v2(db, sql.c_str(), -1, & stmt2, nullptr);
        if (rc2 != SQLITE_OK) {
            std::cerr << "Erreur de préparation de la requête joueur 3 : " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        //Affectation des cartes aux joueurs
        while (sqlite3_step(stmt2) == SQLITE_ROW) {
            int id_carte = sqlite3_column_int(stmt2, 1);
            int noble = sqlite3_column_int(stmt2, 2);
            int reserve = sqlite3_column_int(stmt2, 3);

            //Nobles
            if (noble == 1) {
                const Carte & carte = this -> partie -> espaceJeux -> getPyramide().getPiocheNoble().piocher(id_carte);
                this -> partie -> joueurs[i] -> addCarteNoble(carte);
            }
            //Niveau 1
            else if (1 <= id_carte <= nb_cartes_nv1) {
                const Carte & carte = this -> partie -> espaceJeux -> getPyramide().getPioche1().piocher(id_carte);
                Couleur c = carte.getBonus().getCouleur();
                if (reserve == 0)
                    this -> partie -> joueurs[i] -> addCarte(carte);
                else
                    this -> partie -> joueurs[i] -> addCarteReservee(carte);
            }
            //Niveau 2
            else if (nb_cartes_nv1 < id_carte <= nb_cartes_nv1 + nb_cartes_nv2) {
                const Carte & carte = this -> partie -> espaceJeux -> getPyramide().getPioche2().piocher(id_carte);
                Couleur c = carte.getBonus().getCouleur();
                if (reserve == 0)
                    this -> partie -> joueurs[i] -> addCarte(carte);
                else
                    this -> partie -> joueurs[i] -> addCarteReservee(carte);
            }
            //Niveau 3
            else if (nb_cartes_nv1 + nb_cartes_nv2 < id_carte <= nb_cartes_nv1 + nb_cartes_nv2 + nb_cartes_nv3) {
                const Carte & carte = this -> partie -> espaceJeux -> getPyramide().getPioche3().piocher(id_carte);
                Couleur c = carte.getBonus().getCouleur();
                if (reserve == 0)
                    this -> partie -> joueurs[i] -> addCarte(carte);
                else
                    this -> partie -> joueurs[i] -> addCarteReservee(carte);
            }
        }
        sqlite3_finalize(stmt2);
        i++;
    }

    //Fermeture de la base de données
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void LastPartieBuilder::setJetonsJoueurs() const {
    sqlite3 * db;
    sqlite3_stmt * stmt;
    sqlite3_stmt * stmt2;

    //Connexion aux bases de données
    int rc = sqlite3_open("data/save.sqlite", & db);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees 3: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    //Joueur 1 : recuperation des jetons
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'jetons_joueur' WHERE id_joueur = 1", -1, & stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete jeton 1: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    //Joueur 1 : restitution des jetons
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string couleur = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        const Jeton & j = this -> partie -> espaceJeux -> getSac().piocherJeton(StringToCouleur(couleur));
        this -> partie -> getJoueur1() -> addJeton(j);
    }

    //Joueur 2 : recuperation des jetons
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'jetons_joueur' WHERE id_joueur = 2", -1, & stmt2, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete jeton 4: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    //Joueur 2 : restitution des jetons
    while (sqlite3_step(stmt2) == SQLITE_ROW) {
        string couleur = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 1));
        const Jeton & j = this -> partie -> espaceJeux -> getSac().piocherJeton(StringToCouleur(couleur));
        this -> partie -> getJoueur2() -> addJeton(j);
    }

    //Fermeture de la base de données
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void LastPartieBuilder::updateEspaceJeu() const {
    sqlite3 * db;
    sqlite3_stmt * stmt;
    sqlite3_stmt * stmt2;

    //Connexion aux bases de données
    int rc = sqlite3_open("data/save.sqlite", & db);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees 6: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'pyramide'", -1, & stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete pyr: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Cartes sur la pyramide
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int i = sqlite3_column_int(stmt, 0);
        int j = sqlite3_column_int(stmt, 1);
        int id_carte = sqlite3_column_int(stmt, 2);
        if (i == 0) {
            const Carte & carte = this -> partie -> espaceJeux -> getPyramide().getPioche1().piocher(id_carte);
            partie -> espaceJeux -> getPyramide().definitCarte(i, j, carte);
        } else if (i == 1) {
            const Carte & carte = this -> partie -> espaceJeux -> getPyramide().getPioche2().piocher(id_carte);
            partie -> espaceJeux -> getPyramide().definitCarte(i, j, carte);
        } else if (i == 2) {
            const Carte & carte = this -> partie -> espaceJeux -> getPyramide().getPioche3().piocher(id_carte);
            partie -> espaceJeux -> getPyramide().definitCarte(i, j, carte);
        }
    }

    // Jetons sur le plateau : recuperation
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'plateau'", -1, & stmt2, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete 7 : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Jetons sur le plateau : restitution
    while (sqlite3_step(stmt2) == SQLITE_ROW) {
        int i = sqlite3_column_int(stmt2, 0);
        int j = sqlite3_column_int(stmt2, 1);
        string couleur = reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 2));

        partie -> getEspaceJeux().getPlateau().positionerJeton(partie -> getEspaceJeux().getSac().piocherJeton(StringToCouleur(couleur)), i, j);
    }

    //Fermeture de la base de données
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void LastPartieBuilder::setInfosPartie() const {
    sqlite3 * db;
    sqlite3_stmt * stmt;

    //Connexion aux bases de données
    int rc = sqlite3_open("data/save.sqlite", & db);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees 8: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    //Recuperation des infos de la partie
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'infopartie'", -1, & stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete 9: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    //Restitution des infos de la partie
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int tours = sqlite3_column_int(stmt, 0);
        partie -> tour = tours;
    }

    //Fermeture de la base de données
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}





// ###########   fin des méthodes Builder   #############

// choses a eclaircir : 
// - gestion des cartes nobles
// - gestion des cartes reservees
// - la question des jetons et privileges : un id finalement...?


/*
void Partie::setJoueur1(Joueur& j){
    joueurs[0] = &j;
}


void Partie::setJoueur2(Joueur &j){
    joueurs[1] = &j;
}
*/


// ##### Methodes pour le singleton #####
/*
Partie& Partie::getInstance() {
    if (instance == nullptr) {
        instance = new Partie();
    }
    return *instance;
}

Partie& Partie::getInstance(std::string nomJoueur1, std::string prenomJoueur1) {
    if (instance == nullptr) {
        instance = new Partie(nomJoueur1, prenomJoueur1);
    }
    return *instance;
}
Partie& Partie::getInstance(std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2) {
    if (instance == nullptr) {
        instance = new Partie(nomJoueur1, prenomJoueur1, nomJoueur2, prenomJoueur2);
    }
    return *instance;
}

void Partie::libererInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}   
*/




// ##### Implementation des constructeur mais il y a Builder mtn #####
// 
//Partie::Partie() : espaceJeux(new EspaceJeux()), tour(0), joueurCourant(0) {
//    // création et affectation de nouveaux joueurs 
//    joueurs[0] = new Joueur("Alain", "telligence", type::IA);
//    joueurs[1] = new Joueur("AL", "Gorythme", type::IA);
//}
//
//Partie::Partie(std::string nomJoueur1, std::string prenomJoueur1) : espaceJeux(new EspaceJeux()), tour(0), joueurCourant(0) {
//    // création et affectation de nouveaux joueurs 
//    joueurs[0] = new Joueur(nomJoueur1, prenomJoueur1, type::HUMAIN);
//    joueurs[1] = new Joueur("AL", "Gorythme", type::IA);
//}
//
//Partie::Partie(std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2) : espaceJeux(new EspaceJeux()), tour(0), joueurCourant(0) {
//    // création et affectation de nouveaux joueurs 
//    joueurs[0] = new Joueur(nomJoueur1, prenomJoueur1, type::HUMAIN);
//    joueurs[1] = new Joueur(nomJoueur2, prenomJoueur2, type::HUMAIN);
//}


// ##### Methodes pour la sauvegarde #####

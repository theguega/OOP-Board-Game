#include "partie.hpp"

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


Partie::Partie(){
    joueurs[0] = nullptr;
    joueurs[1] = nullptr;
}

void Partie::setJoueur1(Joueur& j){
    joueurs[0] = &j;
}


void Partie::setJoueur2(Joueur &j){
    joueurs[1] = &j;
}


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


// ##### Methodes pour la sauvegarde #####


// ###########   Debut des méthodes LastPartieBuilder   #############

//void LastPartieBuilder::setJoueurs(){
//    sqlite3* db;
//    sqlite3_stmt* stmt;
//    std::string relativePath = "data/save.sqlite";
//    std::filesystem::path absolutePath = projectPath / relativePath;
//    std::string absolutePathStr = absolutePath.string();
//    int i = 0;
//    int priv_tmp = 0;
//
//    int rc = sqlite3_open(absolutePathStr.c_str(), &db);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Impossible d'ouvrir la base de donnees: " << sqlite3_errmsg(db) << std::endl;
//        return;
//    }
//    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'joueur'", -1, &stmt, nullptr);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
//        sqlite3_close(db);
//        return;
//    }
//    while (sqlite3_step(stmt) == SQLITE_ROW) {
//        std::string nom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
//        std::string prenom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
//        std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
//        int nb_privileges = sqlite3_column_int(stmt, 4);
//        if (type == "IA")
//            this->partie->joueurs[i] = new Joueur(nom, prenom, type::IA);
//        else
//            this->partie->joueurs[i] = new Joueur(nom, prenom, type::HUMAIN);
//
//        for (int j = 0; j < nb_privileges; j++, priv_tmp++) {
//            const Privilege& p = this->partie->espaceJeux.lotPrivileges.getPrivilege(priv_tmp);
//            if (i == 0)
//                this->partie->getJoueur1().addPrivilege(p);
//            else
//                this->partie->getJoueur2().addPrivilege(p);
//        }
//        i++;
//    }
//    sqlite3_finalize(stmt);
//    sqlite3_close(db);
//}
//
//
//void LastPartieBuilder::setCartesJoueurs() const {
//    sqlite3* db;
//    sqlite3_stmt* stmt;
//    std::string relativePath = "data/save.sqlite";
//    std::filesystem::path absolutePath = projectPath / relativePath;
//    std::string absolutePathStr = absolutePath.string();
//    int i = 0;
//    int nb_cartes_nv1 = partie->espaceJeux->getPyramide().getPioche1().getNbCartes();
//    int nb_cartes_nv2 = partie->espaceJeux->getPyramide().getPioche2().getNbCartes();
//    int nb_cartes_nv3 = partie->espaceJeux->getPyramide().getPioche3().getNbCartes();
//    int nb_cartes_noble = partie->espaceJeux->getPyramide().getPiocheNoble().getNbCartes();
//
//    int rc = sqlite3_open(absolutePathStr.c_str(), &db);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Impossible d'ouvrir la base de donnees: " << sqlite3_errmsg(db) << std::endl;
//        return;
//    }
//    rc = sqlite3_prepare_v2(db, "SELECT id FROM 'joueur'", -1, &stmt, nullptr);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
//        sqlite3_close(db);
//        return;
//    }
//
//    while (sqlite3_step(stmt) == SQLITE_ROW) {
//        int id_joueur = sqlite3_column_int(stmt, 0);
//        string sql = "SELECT cartes_joueur.* FROM 'joueur' JOIN 'cartes_joueur' ON joueur.id = cartes_joueur.id_joueur WHERE joueur.id = '" + to_string(id_joueur) + "';";
//        sqlite3_stmt * stmt2;
//
//        int rc2 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt2, nullptr);
//        if (rc2 != SQLITE_OK) {
//            std::cerr << "Erreur de préparation de la requête : " << sqlite3_errmsg(db) << std::endl;
//            sqlite3_close(db);
//            return;
//        }
//
//        while (sqlite3_step(stmt2) == SQLITE_ROW) {
//            int id_carte = sqlite3_column_int(stmt2, 1);
//            int reserve = sqlite3_column_int(stmt2, 2);
//            if (1 <= id_carte <= nb_cartes_nv1) {
//                const Carte& carte = this->partie->espaceJeux->getPyramide().getPioche1().piocher(id_carte);
//                CouleurCarte c = carte.getBonus().getCouleur();
//                if (reserve == 0)
//                    this->partie->joueurs[i]->addCarte(carte);
//                else
//                    this->partie->joueurs[i]->addCarteReservee(carte);
//            }
//            else if (nb_cartes_nv1 < id_carte <= nb_cartes_nv1+nb_cartes_nv2) {
//                const Carte& carte = this->partie->espaceJeux->getPyramide().getPioche2().piocher(id_carte);
//                CouleurCarte c = carte.getBonus().getCouleur();
//                if (reserve == 0)
//                    this->partie->joueurs[i]->addCarte(carte);
//                else
//                    this->partie->joueurs[i]->addCarteReservee(carte);
//            }
//            else if (nb_cartes_nv1 + nb_cartes_nv2 < id_carte <= nb_cartes_nv1 + nb_cartes_nv2 + nb_cartes_nv3) {
//                const Carte& carte = this->partie->espaceJeux->getPyramide().getPioche3().piocher(id_carte);
//                CouleurCarte c = carte.getBonus().getCouleur();
//                if (reserve == 0)
//                    this->partie->joueurs[i]->addCarte(carte);
//                else
//                    this->partie->joueurs[i]->addCarteReservee(carte);
//            }
//        }
//        sqlite3_finalize(stmt2);
//        // TODO : On boucle sur toute les cartes nobles qu'avait le joueur 
//        i++;
//    }
//    sqlite3_finalize(stmt);
//    sqlite3_close(db);
//}
//
//
//void LastPartieBuilder::setJetonsJoueurs() const{
//    sqlite3* db;
//    sqlite3_stmt* stmt;
//    sqlite3_stmt* stmt2;
//    std::string relativePath = "data/save.sqlite";
//    std::filesystem::path absolutePath = projectPath / relativePath;
//    std::string absolutePathStr = absolutePath.string();
//
//    int rc = sqlite3_open(absolutePathStr.c_str(), &db);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Impossible d'ouvrir la base de donnees: " << sqlite3_errmsg(db) << std::endl;
//        return;
//    }
//
//    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'jetons_joueurs WHERE id_joueur = '1'", -1, &stmt, nullptr);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
//        sqlite3_close(db);
//        return;
//    }
//
//    while (sqlite3_step(stmt) == SQLITE_ROW) {
//        string couleur = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
//        const Jeton& j = this->partie->espaceJeux.lotJetons.getJeton(toStringCouleur(couleur));
//        this->partie->getJoueur1().addJeton(j);
//    }
//
//    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'jetons_joueurs WHERE id_joueur = '2'", -1, &stmt2, nullptr);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
//        sqlite3_close(db);
//        return;
//    }
//
//    while (sqlite3_step(stmt2) == SQLITE_ROW) {
//        string couleur = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 1));
//        const Jeton& j = this->partie->espaceJeux.lotJetons.getJeton(toStringCouleur(couleur));
//        this->partie->getJoueur2().addJeton(j);
//    }
//
//    sqlite3_finalize(stmt);
//    sqlite3_close(db);
//}
//
//
//void LastPartieBuilder::updateEspaceJeu() const{
//    sqlite3* db;
//    sqlite3_stmt* stmt;
//    int rc = sqlite3_open("save.sqlite", &db);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Impossible d'ouvrir la base de donnees: " << sqlite3_errmsg(db) << std::endl;
//        return;
//    }
//    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'pyramide'", -1, &stmt, nullptr);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
//        sqlite3_close(db);
//        return;
//    }
//    while (sqlite3_step(stmt) == SQLITE_ROW) {
//        int id_carte = sqlite3_column_int(stmt, 3);
//        int i = sqlite3_column_int(stmt, 0);
//        int j = sqlite3_column_int(stmt, 1);
//
//        if (i == 0) {
//            const Carte& carte = this->partie->espaceJeux->getPyramide().getPioche1().piocher(id_carte);
//            partie->espaceJeux->getPyramide().definitCarte(i, j, carte);
//        }
//        else if (i == 1) {
//            const Carte& carte = this->partie->espaceJeux->getPyramide().getPioche2().piocher(id_carte);
//            partie->espaceJeux->getPyramide().definitCarte(i, j, carte);
//        }
//        else if (i == 2) {
//            const Carte& carte = this->partie->espaceJeux->getPyramide().getPioche3().piocher(id_carte);
//            partie->espaceJeux->getPyramide().definitCarte(i, j, carte);
//        }
//    }
//    //TODO : maintenant qu'on a enlevé des pioches les cartes des joueurs, il faut les disposer sur le plateau. 
//    sqlite3_finalize(stmt);
//    sqlite3_close(db);
//}
//
//
//void LastPartieBuilder::setInfosPartie() const {
//    sqlite3* db;
//    sqlite3_stmt* stmt;
//    std::string relativePath = "data/save.sqlite";
//    std::filesystem::path absolutePath = projectPath / relativePath;
//    std::string absolutePathStr = absolutePath.string();
//
//    int rc = sqlite3_open(absolutePathStr.c_str(), &db);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Impossible d'ouvrir la base de donnees: " << sqlite3_errmsg(db) << std::endl;
//        return;
//    }
//    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'infopartie'", -1, &stmt, nullptr);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
//        sqlite3_close(db);
//        return;
//    }
//    if (sqlite3_step(stmt) == SQLITE_ROW) {
//        int tours = sqlite3_column_int(stmt, 0);
//        int joueur_c = sqlite3_column_int(stmt, 1);
//        partie->tour = tours;
//        partie->joueurCourant = joueur_c;
//    }
//    sqlite3_finalize(stmt);
//    sqlite3_close(db);
//}


// ###########   fin des méthodes Builder   #############

// choses a eclaircir : 
// - gestion des cartes nobles
// - gestion des cartes reservees
// - la question des jetons et privileges : un id finalement...?
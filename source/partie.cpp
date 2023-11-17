#include "partie.hpp"

EspaceJeux* Partie::espaceJeux = new EspaceJeux();

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

void Partie::setJoueurCourant(int n) {
    if (n != 0 || n != 1)
        throw PartieException("Il n'y a que deux joueurs");
    else
        joueurCourant = n;
}

void Partie::setJoueur1(Joueur& j){
    joueurs[0] = &j;
}


void Partie::setJoueur2(Joueur &j){
    joueurs[1] = &j;
}


void Partie::changerJoueurCourant() {
    switch (joueurCourant) {
        case 0:
            joueurCourant = 1;
            break;
        case 1:
            joueurCourant = 0;
            break;
        default:
            break;
    }
}
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
//Sauvegarde de la partie dans save.sqlite
void Partie::sauvegardePartie() {
    //Cette fonction aura pour objectif de push toutes les données importantes de la partie dans la base de donnée
    //Afin de pouvoir reprendre la partie plus tard
    //Pour cela, il faudra créer une base de donnée avec les tables suivantes :
    // joueur1, joueur2, plateau, infopartie, pyramide

    //on ajoute le chemin relatif au chemin absolue du projet
    std::string relativePath = "data/save.sqlite";
    std::filesystem::path absolutePath = projectPath / relativePath;
    std::string absolutePathStr = absolutePath.string();

    //Connexion à la base de donnée
    sqlite3 *db;
    int rc = sqlite3_open(absolutePathStr.c_str(), &db);
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
        sql = "INSERT INTO joueur (id, nom, prenom, type) VALUES (" + std::to_string(i+1) + ", '" + joueurs[i]->getNom() + "', '" + joueurs[i]->getPrenom() + "', '" + toStringType(joueurs[i]->getTypeDeJoueur()) + "');";
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
        if (rc != SQLITE_OK) {
            std::cerr << "Erreur lors de la sauvegarde du joueur " << i+1 << std::endl;
            sqlite3_close(db);
            return;
        }
    }

        //jetons
        //cartes

    //Sauvegarde plateau
    Plateau& plateau = espaceJeux->getPlateau();
    for (size_t i =0; i<plateau.getTaille(); i++) {
        for (size_t j =0; j<plateau.getTaille(); j++) {
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
    Pyramide& pyramide = espaceJeux->getPyramide();
    for (size_t i =0; i<4; i++) {
        for (size_t j =0; j<pyramide.array_cartes[i].size(); j++) {
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

void Partie::enregisterScore() {
    //a la fin d'une partie il faut enregistrer le score des joueurs dans la base de donnée
    //on regarde si il existe déjà et on lui ajoute une victoire ou une défaite
    //sinon on le crée et on lui ajoute une victoire ou une défaite

    //Connexion à la base de donnée
    sqlite3 *db;
    int rc = sqlite3_open("score.sqlite", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la connexion à la base de donnée" << std::endl;
        sqlite3_close(db);
        return;
    }

    for (size_t i = 0; i < 2; i++) {
        //Recherche du joueur 
        string sql = "SELECT * FROM score WHERE nom = '" + joueurs[i]->getNom() + "' AND prenom = '" + joueurs[i]->getPrenom() + "';";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            std::cerr << "Erreur lors de la recherche du joueur 1" << std::endl;
            sqlite3_close(db);
            return;
        }
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            //Le joueur existe déjà
            //On récupère son nombre de victoire et de défaite
            int nbVictoire = sqlite3_column_int(stmt, 2);
            int nbDefaite = sqlite3_column_int(stmt, 3);
            //On incrémente le nombre de victoire ou de défaite
            if (joueurs[i]->estGagnant()) {
                nbVictoire++;
            } else {
                nbDefaite++;
            }
            //On met à jour le joueur
            sql = "UPDATE score SET nbVictoire = " + std::to_string(nbVictoire) + ", nbDefaite = " + std::to_string(nbDefaite) + " WHERE nom = '" + joueurs[i]->getNom() + "' AND prenom = '" + joueurs[i]->getPrenom() + "';";
            rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
            if (rc != SQLITE_OK) {
                std::cerr << "Erreur lors de la mise à jour du joueur 1" << std::endl;
                sqlite3_close(db);
                return;
            }
        } else {
            //Le joueur n'existe pas
            //On l'ajoute donc en lui attribuant une victoire ou une défaite
            if (joueurs[i]->estGagnant()) {
                sql = "INSERT INTO score (nom, prenom, nbVictoire, nbDefaite) VALUES ('" + joueurs[0]->getNom() + "', '" + joueurs[i]->getPrenom() + "', 1, 0);";
            } else {
                sql = "INSERT INTO score (nom, prenom, nbVictoire, nbDefaite) VALUES ('" + joueurs[0]->getNom() + "', '" + joueurs[i]->getPrenom() + "', 0, 1);";
            }
        }
    }

    //Fermeture de la base de donnée
    sqlite3_close(db);
}


// ###########   Debut des méthodes Builder   #############

void NewPartieBuilder::setJoueurs(string nomJoueur1, string prenomJoueur1, string nomJoueur2, string prenomJoueur2) const {
    partie->joueurs[0] = new Joueur(nomJoueur1, prenomJoueur1, type::HUMAIN);
    partie->joueurs[1] = new Joueur(nomJoueur2, prenomJoueur2, type::HUMAIN);
}

void NewPartieBuilder::setTours_and_current() const {
    partie->tour = 0;
    partie->joueurCourant = 0;
}

void Director::BuildNewPartie() {
    this->builder->setEspaceJeu();
    this->builder->setJoueurs();
    this->builder->setTours();
    this->builder->setJoueurCourant();
}

void LastPartieBuilder::setEspaceJeu() const {
    this->partie.espaceJeux = new EspaceJeux();
}

void LastPartieBuilder::setJoueurs() const {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string relativePath = "data/save.sqlite";
    std::filesystem::path absolutePath = projectPath / relativePath;
    std::string absolutePathStr = absolutePath.string();
    int i = 0;

    int rc = sqlite3_open(absolutePathStr.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'joueur'", -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_joueur = sqlite3_column_int(stmt, 0);
        string nom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string prenom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        this->partie.joueurs[i] = Joueur(nom, prenom, type);
        sqlite3_stmt* stmt2;

        int sql = sqlite3_prepare_v2(db, "SELECT cartes_joueur.* FROM 'joueur' JOIN 'cartes_joueur' ON joueur.id = cartes_joueur.id_joueur WHERE joueur.id = ?", -1, &stmt2, nullptr);
        if (sql != SQLITE_OK) {
            std::cerr << "Erreur de préparation de la requête : " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        sql = sqlite3_bind_int(stmt2, 1, id_joueur);
        if (sql != SQLITE_OK) {
            std::cerr << "Erreur de liaison de paramètre : " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt2);
            sqlite3_close(db);
            return;
        }
        while (sqlite3_step(stmt2) == SQLITE_ROW) {
            int id_carte = sqlite3_column_int(stmt2, 1);
            if (1 <= id <= 30) {
                Carte* carte = this->partie.EspaceJeu.piocheNv1.piocher(i);
                CouleurCarte c = carte->getBonus().getCouleur();
                this->partie.joueurs[i].cartes[c].pushback(carte);
            }
            else if () {

            }
            else if () {

            }
            // TODO 
            // chaque passage dans la boucle on recupere un nouvel ID de carte
            // on la récupère dans une picohe et on la met dans les dicos du joueur
        }
        i++
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void LastPartieBuilder::updateEspaceJeu() {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("save.sqlite", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void LastPartieBuilder::setTours_and_current() const {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string relativePath = "data/save.sqlite";
    std::filesystem::path absolutePath = projectPath / relativePath;
    std::string absolutePathStr = absolutePath.string();

    int rc = sqlite3_open(absolutePathStr.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'infopartie'", -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int tours = sqlite3_column_int(stmt, 0);
        int joueur_c = sqlite3_column_int(stmt, 1);
        this->partie.tour = tours;
        this->partie.joueurCourant = joueur_c;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Director::BuildLastPartie() {
    this->builder->setEspaceJeu();
    this->builder->setJoueurs();
    this->builder->updateEspaceJeu();
    this->builder->setTours();
    this->builder->setJoueurCourant();
}


// ###########   fin des méthodes Builder   #############

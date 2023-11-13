#include "partie.hpp"
#include "joueur.hpp"
#include "jetons.hpp"
#include "carte.h"
#include "espacejeux.hpp"
#include "sqlite3.h"

Partie::Partie() {
    // création et affectation de nouveaux joueurs 
    joueurs[0] = new Joueur("Alain", "telligence", type::IA);
    joueurs[1] = new Joueur("AL", "Gorythme", type::IA);
    tour = 0;
    joueurCourant = 0;
}

Partie::Partie(std::string nomJoueur1, std::string prenomJoueur1) {
    // création et affectation de nouveaux joueurs 
    joueurs[0] = new Joueur(nomJoueur1, prenomJoueur1, type::HUMAIN);
    joueurs[1] = new Joueur("AL", "Gorythme", type::IA);
    tour = 0;
    joueurCourant = 0;
}

Partie::Partie(std::string nomJoueur1, std::string prenomJoueur1, std::string nomJoueur2, std::string prenomJoueur2) {
    // création et affectation de nouveaux joueurs 
    joueurs[0] = new Joueur(nomJoueur1, prenomJoueur1, type::HUMAIN);
    joueurs[1] = new Joueur(nomJoueur2, prenomJoueur2, type::HUMAIN);
    tour = 0;
    joueurCourant = 0;
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

//Sauvegarde de la partie dans save.sqlite
void Partie::sauvegardePartie() {
    //Cette fonction aura pour objectif de push toutes les données importantes de la partie dans la base de donnée
    //Afin de pouvoir reprendre la partie plus tard
    //Pour cela, il faudra créer une base de donnée avec les tables suivantes :
    // joueur1, joueur2, plateau, infopartie, pyramide

    //Connexion à la base de donnée
    sqlite3 *db;
    int rc = sqlite3_open("save.sqlite", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la connexion à la base de donnée" << std::endl;
        sqlite3_close(db);
        return;
    }

    //Nettoyage de l'ancienne sauvegarde
    string sql = "TRUNCATE TABLE joueur1; TRUNCATE TABLE joueur2; TRUNCATE TABLE plateau; TRUNCATE TABLE infopartie; TRUNCATE TABLE pyramide;";
    rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors du nettoyage de la base de donnée" << std::endl;
        sqlite3_close(db);
        return;
    }

    //Sauvegarde joueur1
    sql = "INSERT INTO joueur1 (nom, prenom, type) VALUES ('" + joueurs[0]->getNom() + "', '" + joueurs[0]->getPrenom() + "', '" + toStringType(joueurs[0]->getTypeDeJoueur()) + "');";
    rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la sauvegarde du joueur 1" << std::endl;
        sqlite3_close(db);
        return;
    }

    //Sauvegarde joueur2
    sql = "INSERT INTO joueur2 (nom, prenom, type) VALUES ('" + joueurs[1]->getNom() + "', '" + joueurs[1]->getPrenom() + "', '" + toStringType(joueurs[1]->getTypeDeJoueur()) + "');";
    rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la sauvegarde du joueur 2" << std::endl;
        sqlite3_close(db);
        return;
    }

    //Sauvegarde plateau
    Plateau& plateau = espaceJeux->getPlateau();
    for (size_t i =0; i<plateau.getTaille(); i++) {
        for (size_t j =0; i<plateau.getTaille(); i++) {
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
        for (size_t j =0; i<4; i++) {
            const Carte* carte = pyramide.getCarte(i,j);
            sql= "INSERT INTO pyramide (i, j, type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES (" + std::to_string(i) + ", " + std::to_string(j) + ", '" + TypeCartetoString(carte->getType()) + "', " + std::to_string(carte->getPrix().getBlanc()) + ", " + std::to_string(carte->getPrix().getBleu()) + ", " + std::to_string(carte->getPrix().getVert()) + ", " + std::to_string(carte->getPrix().getRouge()) + ", " + std::to_string(carte->getPrix().getNoir()) + ", " + std::to_string(carte->getPrix().getPerle()) + ", '" + CapacitetoString(carte->getCapacite1()) + "', '" + CapacitetoString(carte->getCapacite2()) + "', '" + CouleurCartetoString(carte->getBonus().getCouleur()) + "', " + std::to_string(carte->getBonus().getNbBonus()) + ", " + std::to_string(carte->getNbCouronnes()) + ", " + std::to_string(carte->getNbPtsPrivilege()) + ");";
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
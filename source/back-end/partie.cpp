#include "partie.hpp"

Partie::Partie(): espaceJeux(new EspaceJeux()) {
    joueurs[0] = nullptr;
    joueurs[1] = nullptr;
}

// ###########   LastPartieBuilder   #############

void LastPartieBuilder::setJoueurs() const {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn5");
    db.setDatabaseName("data/save.sqlite");

    if (!db.open()) {
        std::cerr << "Impossible d'ouvrir la base de donnees 1: " << db.lastError().text().toStdString() << std::endl;
        return;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM 'joueur';")) {
        std::cerr << "Erreur de preparation de la requete joueur: " << query.lastError().text().toStdString() << std::endl;
        db.close();
        return;
    }

    int i = 0;
    while (query.next()) {
        string pseudo = query.value(1).toString().toStdString();
        string type = query.value(2).toString().toStdString();
        int nb_privileges = query.value(3).toInt();
        if (type == "IA")
            this->partie->joueurs[i] = new Joueur(pseudo, type::IA);
        else
            this->partie->joueurs[i] = new Joueur(pseudo, type::HUMAIN);

        for (int j = 0; j < nb_privileges; j++) {
            const Privilege &p = this->partie->getEspaceJeux().getPlateau().recupererPrivilege();
            if (i == 0)
                this->partie->getJoueur1()->addPrivilege(p);
            else
                this->partie->getJoueur2()->addPrivilege(p);
        }
        i++;
    }

    db.close();
}


void LastPartieBuilder::setCartesJoueurs() const {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn6");
    db.setDatabaseName("data/save.sqlite");
    if (!db.open()) {
        std::cerr << "Impossible d'ouvrir la base de donnees 2: " << db.lastError().text().toStdString() << std::endl;
        return;
    }
    size_t nb_cartes_nv1 = partie -> espaceJeux -> getPyramide().getPioche1().getNbCartes();
    size_t nb_cartes_nv2 = partie -> espaceJeux -> getPyramide().getPioche2().getNbCartes();
    size_t nb_cartes_nv3 = partie -> espaceJeux -> getPyramide().getPioche3().getNbCartes();
    size_t nb_cartes_noble = partie -> espaceJeux -> getPyramide().getPiocheNoble().getNbCartes();
    QSqlQuery query(db);
    if (!query.exec("SELECT id FROM 'joueur';")) {
        std::cerr << "Erreur de preparation de la requete joueur 2: " << query.lastError().text().toStdString() << std::endl;
        db.close();
        return;
    }

    int i = 0;
    while (query.next()) {
        int id_joueur = query.value(0).toInt();
        QString sql2 = "SELECT cartes_joueur.* FROM 'joueur' JOIN 'cartes_joueur' ON joueur.id = cartes_joueur.id_joueur WHERE joueur.id = " + QString::number(id_joueur) + ";";
        QSqlQuery query2(db);
        if (!query2.exec(sql2)) {
            std::cerr << "Erreur de preparation de la requête joueur 3 : " << query2.lastError().text().toStdString() << std::endl;
            db.close();
            return;
        }

        while (query2.next()) {
            int id_carte = query2.value(1).toInt();
            int noble = query2.value(2).toInt();
            int reserve = query2.value(3).toInt();

            // Nobles
            if (noble == 1) {
                const Carte &carte = this->partie->espaceJeux->getPyramide().getPiocheNoble().piocher(id_carte);
                this->partie->joueurs[i]->addCarteNoble(carte);
            }
            // Niveau 1
            else if (1 <= id_carte && id_carte <= nb_cartes_nv1) {
                const Carte &carte = this->partie->espaceJeux->getPyramide().getPioche1().piocher(id_carte);
                Couleur c = carte.getBonus().getCouleur();
                if (reserve == 0)
                    this->partie->joueurs[i]->addCarte(carte);
                else
                    this->partie->joueurs[i]->addCarteReservee(carte);
            }
            // Niveau 2
            else if (nb_cartes_nv1 < id_carte && id_carte <= nb_cartes_nv1 + nb_cartes_nv2) {
                const Carte &carte = this->partie->espaceJeux->getPyramide().getPioche2().piocher(id_carte);
                Couleur c = carte.getBonus().getCouleur();
                if (reserve == 0)
                    this->partie->joueurs[i]->addCarte(carte);
                else
                    this->partie->joueurs[i]->addCarteReservee(carte);
            }
            // Niveau 3
            else if (nb_cartes_nv1 + nb_cartes_nv2 < id_carte && id_carte <= nb_cartes_nv1 + nb_cartes_nv2 + nb_cartes_nv3) {
                const Carte &carte = this->partie->espaceJeux->getPyramide().getPioche3().piocher(id_carte);
                Couleur c = carte.getBonus().getCouleur();
                if (reserve == 0)
                    this->partie->joueurs[i]->addCarte(carte);
                else
                    this->partie->joueurs[i]->addCarteReservee(carte);
            }
        }
        i++;
    }

    db.close();
}


void LastPartieBuilder::setJetonsJoueurs() const {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn7");
    db.setDatabaseName("data/save.sqlite");
    if (!db.open()) {
        std::cerr << "Impossible d'ouvrir la base de donnees 3: " << db.lastError().text().toStdString() << std::endl;
        return;
    }

    // Joueur 1 : recuperation des jetons
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM 'jetons_joueur' WHERE id_joueur = 1")) {
        std::cerr << "Erreur de preparation de la requete jeton 1: " << query.lastError().text().toStdString() << std::endl;
        db.close();
        return;
    }

    // Joueur 1 : restitution des jetons
    while (query.next()) {
        string couleur = query.value(1).toString().toStdString();
        const Jeton &j = this->partie->espaceJeux->getSac().piocherJeton(StringToCouleur(couleur));
        this->partie->getJoueur1()->addJeton(j);
    }

    // Joueur 2 : recuperation des jetons
    if (!query.exec("SELECT * FROM 'jetons_joueur' WHERE id_joueur = 2")) {
        std::cerr << "Erreur de preparation de la requete jeton 4: " << query.lastError().text().toStdString() << std::endl;
        db.close();
        return;
    }

    // Joueur 2 : restitution des jetons
    while (query.next()) {
        string couleur = query.value(1).toString().toStdString();
        const Jeton &j = this->partie->espaceJeux->getSac().piocherJeton(StringToCouleur(couleur));
        this->partie->getJoueur2()->addJeton(j);
    }

    db.close();
}


void LastPartieBuilder::updateEspaceJeu() const {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn8");
    db.setDatabaseName("data/save.sqlite");
    if (!db.open()) {
        std::cerr << "Impossible d'ouvrir la base de donnees 6: " << db.lastError().text().toStdString() << std::endl;
        return;
    }

    // Cartes sur la pyramide
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM 'pyramide'")) {
        std::cerr << "Erreur de preparation de la requete pyr: " << query.lastError().text().toStdString() << std::endl;
        db.close();
        return;
    }

    // Cartes sur la pyramide : restitution
    while (query.next()) {
        int i = query.value(0).toInt();
        int j = query.value(1).toInt();
        int id_carte = query.value(2).toInt();
        if (i == 0) {
            const Carte &carte = this->partie->espaceJeux->getPyramide().getPioche1().piocher(id_carte);
            partie->espaceJeux->getPyramide().definitCarte(i, j, carte);
        } else if (i == 1) {
            const Carte &carte = this->partie->espaceJeux->getPyramide().getPioche2().piocher(id_carte);
            partie->espaceJeux->getPyramide().definitCarte(i, j, carte);
        } else if (i == 2) {
            const Carte &carte = this->partie->espaceJeux->getPyramide().getPioche3().piocher(id_carte);
            partie->espaceJeux->getPyramide().definitCarte(i, j, carte);
        } else if (i == 3){
            const Carte &carte = this->partie->espaceJeux->getPyramide().getPiocheNoble().piocher(id_carte);
            partie->espaceJeux->getPyramide().definitCarte(i, j, carte);
        }
    }

    // Jetons sur le plateau : recuperation
    if (!query.exec("SELECT * FROM 'plateau'")) {
        std::cerr << "Erreur de preparation de la requete 7 : " << query.lastError().text().toStdString() << std::endl;
        db.close();
        return;
    }

    // Jetons sur le plateau : restitution
    while (query.next()) {
        int i = query.value(0).toInt();
        int j = query.value(1).toInt();
        string couleur = query.value(2).toString().toStdString();
        partie->getEspaceJeux().getPlateau().positionerJeton(partie->getEspaceJeux().getSac().piocherJeton(StringToCouleur(couleur)), i, j);
    }

    db.close();
}

void LastPartieBuilder::setInfosPartie() const {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn9");
    db.setDatabaseName("data/save.sqlite");
    if (!db.open()) {
        std::cerr << "Impossible d'ouvrir la base de donnees 8: " << db.lastError().text().toStdString() << std::endl;
        return;
    }

    // Recuperation des infos de la partie
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM 'infopartie'")) {
        std::cerr << "Erreur de preparation de la requete 9: " << query.lastError().text().toStdString() << std::endl;
        db.close();
        return;
    }

    // Restitution des infos de la partie
    if (query.next()) {
        int tours = query.value(0).toInt();
        partie->tour = tours;
    }

    db.close();
}


// ###########   fin des methodes Builder   #############



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
}*/


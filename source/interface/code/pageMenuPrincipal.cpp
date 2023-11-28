#include "pageMenuPrincipal.h"

pageMenuPrincipal::pageMenuPrincipal(QWidget *parent) : QWidget(parent) {
    boutonDemarrer = new QPushButton("Commencer une nouvelle partie");
    boutonSauvegarde = new QPushButton("Démarrer une partie sauvegardée");
    boutonQuitter = new QPushButton("Quitter");

    coucheMP = new QVBoxLayout(this);
    coucheMP->addWidget(boutonDemarrer);
    coucheMP->addWidget(boutonSauvegarde);
    coucheMP->addWidget(boutonQuitter);

    setLayout(coucheMP);
}

pageMenuPrincipal::~pageMenuPrincipal() {
    delete boutonDemarrer;
    delete boutonSauvegarde;
    delete boutonQuitter;
    delete coucheMP;
}


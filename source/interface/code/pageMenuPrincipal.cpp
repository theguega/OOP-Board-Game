#include "pageMenuPrincipal.h"

pageMenuPrincipal::pageMenuPrincipal(QWidget *parent) : QWidget(parent) {
    boutonDemarrer = new QPushButton("Commencer une nouvelle partie");
    boutonSauvegarde = new QPushButton("Démarrer une partie sauvegardée");
    boutonBibli = new QPushButton("Scores");
    boutonQuitter = new QPushButton("Quitter");

    coucheMP = new QVBoxLayout(this);
    coucheMP->addWidget(boutonDemarrer);
    coucheMP->addWidget(boutonSauvegarde);
    coucheMP->addWidget(boutonBibli);
    coucheMP->addWidget(boutonQuitter);

    setLayout(coucheMP);
}

pageMenuPrincipal::~pageMenuPrincipal() {
    delete boutonDemarrer;
    delete boutonSauvegarde;
    delete boutonBibli;
    delete boutonQuitter;
    delete coucheMP;
}


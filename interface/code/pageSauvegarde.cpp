#include "pageSauvegarde.h"

pageSauvegarde::pageSauvegarde(QWidget *parent) : QScrollArea(parent), nSauvegardes(20) {
    boutons = new QWidget(this);
    layoutSauvegardes = new QVBoxLayout(boutons);

    for (int i = 0; i < nSauvegardes; ++i) {
        QPushButton *bouton = new QPushButton("Sauvegarde " + QString::number(i + 1));
        layoutSauvegardes->addWidget(bouton);
    }

    retourMenuSauv = new QPushButton("Retour Menu Principal", this);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    setWidget(boutons);
    layoutPrincipal->addWidget(retourMenuSauv);
}

pageSauvegarde::~pageSauvegarde() {
    delete retourMenuSauv;
    delete layoutSauvegardes;
    delete boutons;
}

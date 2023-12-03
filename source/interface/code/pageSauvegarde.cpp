#include "pageSauvegarde.h"

pageSauvegarde::pageSauvegarde(QWidget *parent) : QScrollArea(parent), nSauvegardes(50) {
    boutons = new QWidget(this);
    layoutSauvegardes = new QVBoxLayout(boutons);

    retourMenuSauv = new QPushButton("Retour Menu Principal", this);
    layoutSauvegardes->addWidget(retourMenuSauv);

    for (int i = 0; i < nSauvegardes; ++i) {
        QPushButton *bouton = new QPushButton("Sauvegarde " + QString::number(i + 1) + " // nom:");
        layoutSauvegardes->addWidget(bouton);
        connect(bouton, &QPushButton::clicked, this, [=]() {demarrerSauvegarde(i);} );
    }

    setWidget(boutons);
}

pageSauvegarde::~pageSauvegarde() {
    delete retourMenuSauv;
    delete layoutSauvegardes;
    delete boutons;
}

void pageSauvegarde::demarrerSauvegarde(int idBouton){
    qDebug()<<"Le bouton clique est "<<idBouton;
    return;
}

#include "pageBibliotheque.h"

pageBibliotheque::pageBibliotheque(QWidget *parent) : QScrollArea(parent){
    boutons = new QWidget(this);
    layoutBibli = new QVBoxLayout(boutons);

    retourMenuSauv = new QPushButton("Retour Menu Principal", this);
    layoutBibli->addWidget(retourMenuSauv);
}

pageBibliotheque::~pageBibliotheque() {
    delete retourMenuSauv;
    delete layoutBibli;
    delete boutons;
}


#include "pageJeu.h"

pageJeu::pageJeu(QWidget *parent) : QWidget(parent) {
    retourMenu = new QPushButton("Retour Menu Principal", this);
    coucheJ = new QVBoxLayout(this);
    coucheJ->addWidget(retourMenu);
}

void pageJeu::ajoutWidget(QWidget *objet) {
    // Ajoutez ici le code pour gérer l'ajout d'autres widgets à votre page
    coucheJ->addWidget(objet);
}

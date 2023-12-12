#include "back-end/controller.hpp"

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QtSql>

#include "back-end/exception.hpp"

#include "interface/code/vueCarte.h"
#include "interface/code/pageCreation.h"
#include "interface/code/vueJeton.h"
#include "interface/code/vuePlateau.h"
#include "interface/code/toutesPages.h"
#include <iostream>



//#########################################
//###### Partie avec l'application Qt #####
//#########################################


int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
//    vueCarte carte = vueCarte(nullptr);
//    carte.show();

//    pageCreation page = pageCreation(nullptr);
//    page.show();

//    QWidget* widget = new QWidget;

//    vueJeton* jeton = new vueJeton(nullptr);

//    QHBoxLayout* layout = new QHBoxLayout;
//    layout->addWidget(jeton);

//    widget -> setLayout(layout);

//    widget->show();

//    vuePlateau* plateau = new vuePlateau(nullptr, 500, 500);
//    plateau -> show();

    toutesPages* page = new toutesPages(nullptr, &app);
    page->show();

    return app.exec();
}












//####################################
//###### Partie en mode Terminal #####
//####################################

/*
int main(int argc, char * argv[]) {
    Controller control;
    control.lancerPartie();
    control.jouer();
    return 0;
}*/

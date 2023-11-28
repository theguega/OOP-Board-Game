#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QApplication>
#include "toutesPages.h"
#include "pageMenuPrincipal.h"
#include "pageJeu.h"
#include "pageSauvegarde.h"

toutesPages::toutesPages(pageMenuPrincipal* menuPrincipal, pageJeu* jeu, pageSauvegarde* scrollSauvegardes, QApplication* app){
    addWidget(menuPrincipal);
    addWidget(jeu);
    addWidget(scrollSauvegardes);

    QObject::connect(menuPrincipal->getBoutonQuitter(), &QPushButton::clicked, app, &QCoreApplication::quit);
    QObject::connect(menuPrincipal->getBoutonDemarrer(), &QPushButton::clicked, [this]() {
        setCurrentIndex(1);
    });
    QObject::connect(jeu->getRetourMenu(), &QPushButton::clicked, [this](){
        setCurrentIndex(0);
    });
    QObject::connect(scrollSauvegardes->getRetourMenuSauv(), &QPushButton::clicked, [this](){
        setCurrentIndex(0);
    });
    QObject::connect(menuPrincipal->getBoutonSauvegarde(), &QPushButton::clicked, [this](){
        setCurrentIndex(2);
    });
}

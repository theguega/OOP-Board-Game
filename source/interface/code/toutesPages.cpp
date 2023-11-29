#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QScreen>
#include <QSize>
#include "toutesPages.h"
#include "pageMenuPrincipal.h"
#include "pageJeu.h"
#include "pageSauvegarde.h"
#include "pageCreation.h"

toutesPages::toutesPages(QWidget* parent, QApplication* app) {
    pageMenuPrincipal* menuPrincipal = new pageMenuPrincipal; //Ajoute la page menuPrincipal
    //pageJeu* jeu = new pageJeu; //Ajoute la page jeu (sert surement à rien car sera dans pageCreation)
    pageSauvegarde* scrollSauvegardes = new pageSauvegarde; //Ajoute la page scrollSauvegardes (à termes, changera por historique des joueurs)
    pageCreation* crea = new pageCreation; //Ajoute la page création (qui sert à créer la page de Jeu)
    pageBibliotheque* bibli = new pageBibliotheque;


    addWidget(menuPrincipal); //Le addWidget dans ce cas permet de mettre menuPrincipal comme l'index 0
    addWidget(crea); //Crea devient l'index 1
    addWidget(scrollSauvegardes); // scrollSauvegardes devient l'index 2
    addWidget(bibli);

    QObject::connect(menuPrincipal->getBoutonQuitter(), &QPushButton::clicked, app, &QCoreApplication::quit); //On connecte le bouton quitter du menu avec le fait de quitter l'application
    connect(menuPrincipal->getBoutonDemarrer(), &QPushButton::clicked, [this]() {
        setCurrentIndex(1); //En appuyer sur démarrer, on va sur la page de création de Jeu
    });
    connect(crea->getRetourMenu(), &QPushButton::clicked, [this](){
        setCurrentIndex(0); //Permet de retourner au menu principal
    });
    connect(scrollSauvegardes->getRetourMenuSauv(), &QPushButton::clicked, [this](){
        setCurrentIndex(0); //Permet de retourner au menu principal depuis scrollSauvegardes
    });
    connect(menuPrincipal->getBoutonSauvegarde(), &QPushButton::clicked, [this](){
        setCurrentIndex(2); //Permet d'accéder à Scrool sauvegarde
    });
    connect(menuPrincipal->getBoutonBibli(), &QPushButton::clicked, [this] (){
        setCurrentIndex(3);
    });
    connect(bibli->getRetourMenuSauv(), &QPushButton::clicked, [this](){
        setCurrentIndex(0); //Permet de retourner au menu principal depuis scrollSauvegardes
    });
    connect(crea, &pageCreation::fermerToutesPages, this, &toutesPages::fermerFenetre); //Connecte le signal fermerToutesPages (émit lors de la validation dans création page) vec la méthode fermer fenêtre afin de tout fermer au moment de la mise en route du jeu
}

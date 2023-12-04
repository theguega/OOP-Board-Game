#include "pageJoueur.h"

pageJoueur::pageJoueur(QWidget* parent) : QWidget(parent){
    cartesReserveesLayout = new QHBoxLayout;
    cartesPossedeesLayout = new QHBoxLayout;
    jetonsPossedesLayout = new QHBoxLayout;
    layout = new QVBoxLayout;

    cartesReserveesWidget = new QWidget;
    cartesPossedeesWidget = new QWidget;
    jetonsPossedesWidget = new QWidget;

    cartesReserveesWidget->setLayout(cartesReserveesLayout);
    cartesPossedeesWidget->setLayout(cartesPossedeesLayout);
    jetonsPossedesWidget->setLayout(jetonsPossedesLayout);

    layout->addWidget(cartesReserveesWidget);
    layout->addWidget(cartesPossedeesWidget);
    layout->addWidget(jetonsPossedesWidget);

    setLayout(layout);
}

void pageJoueur::ajouterCarteReservee(vueCarte* carte){
    cartesReservees.push_back(carte);
    cartesReserveesLayout -> addWidget(carte);
}

void pageJoueur::ajouterCartePossedee(vueCarte* carte){
    cartesPossedees.push_back(carte);
    cartesPossedeesLayout -> addWidget(carte);
}

void pageJoueur::ajouterJeton(vueJeton* jeton){
    jetonsPossedes.push_back(jeton);
    jetonsPossedesLayout -> addWidget(jeton);
}

void pageJoueur::retirerJeton(vueJeton* jeton){
    //A faire
}

void pageJoueur::afficher(bool tourJoueur){
    if(tourJoueur){
        this -> show();
        cartesReserveesWidget -> show();
    }
    else{
        this -> show();
        cartesReserveesWidget -> hide();
    }
}

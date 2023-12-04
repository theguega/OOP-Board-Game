#include <QWidget>
#include <array>
#include <QVBoxLayout>
#include <QPushButton>
#include "vuePlateau.h"
#include "vueJeton.h"

vuePlateau::vuePlateau(QWidget* parent, int hauteur, int largeur) : QWidget(parent){
    h = hauteur; //Def la hateur du plateau
    l = largeur; //Def la largeur du plateau

    nbJetons = 25; //Nombre de jetons sur la plateau (sera recuperer depuis le back apres)
    setFixedSize(l, h); //Fixe la taille du plateau
    //sac = plateau->getSac();
    for(int i = 0; i < nbJetons; i++){
        //Creer un getteur pour les Jetons
        listeJetons[i] = new vueJeton(nullptr, (h - 100)/(2*sqrt(nbJetons)));
        layoutJetons -> addWidget(listeJetons[i], i / 5, i % 5);
        QObject::connect(listeJetons[i], &vueJeton::clicked, [this, i]() {
            boutonClique(i); //Permet d'appeler la fonction boutonClique(int i) lorsque le bouton i est clique
        });
    }
    for(int i = 0; i < 3; i++){
        jetonSelection[i] = nullptr; //Initialise jetonSelection avec nullptr
    }

    boutonValider = new QPushButton("Valider le choix des jetons"); //Creer le bouton valider (pour la selection des jetons)

    layout = new QVBoxLayout; //Layout pour mettre le Grid + les boutons en dessous

    layout -> addLayout(layoutJetons); //Ajoute layoutJetons au layout vertical
    layout -> addWidget(boutonValider); //Ajoute layoutJetons au layout vertical (faire un QHBoxLayout pour ajouter aussi un bouton desselctionner)

    setLayout(layout); //Set le layout

    connect(boutonValider, &QPushButton::clicked, this, &vuePlateau::validerJetons); //connect boutonValider avec valliderJetons

    info = new popUpInfo(nullptr, "Vos jetons ont bien ete ajoute");
}

void vuePlateau::boutonClique(int i){
    int j = 0;
    qDebug() << nbJetonSelection;
    if(estSelectionne(listeJetons[i])){
        for(j = 0; j < 3; j++){
            if(jetonSelection[j] == listeJetons[i]){
                jetonSelection[j] = nullptr;
                listeJetons[i] -> changeAfficherCroix();
                nbJetonSelection -= 1;
            }
        }
    }
    else{
        if(nbJetonSelection < 3){
            listeJetons[i] -> changeAfficherCroix();
            while(jetonSelection[j] != nullptr){
                j++;
            }
            jetonSelection[j] = listeJetons[i];
            nbJetonSelection += 1;
        }
    }
}

void vuePlateau::deselectionner(){
    for(int i = 0; i < nbJetons; i++){
        listeJetons[i] -> enleverCroix();
    }
    for(int i = 0; i < 3; i++){
        jetonSelection[i] = nullptr;
    }
}

bool vuePlateau::estSelectionne(vueJeton* jeton){
    for(int j = 0; j < 3; j++){
        if(jetonSelection[j] == jeton){
            return true;
        }
    }
    return false;
}

void vuePlateau::validerJetons(){
    info -> show();
}

void vuePlateau::cacherElements(){
    info -> close();
}

/*vueJeton* vuePlateau::recupererBouton(Jeton* jeton){
    for(int i = 0; i < 25; i++){
        if(listeJetons[i]->getJeton() == jeton){
            return listeJetons[i];
        }
    }
    return nullptr;
}*/

/*void vuePlateau::remplirPlateau(){
    vueJeton* temp;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 25; j++){
            //faire un getteur pour le plateau
            temp = recupererBouton(plateau.getJeton(i, j));
            temp->apparaitre(position(i, j));
        }
    }
}*/

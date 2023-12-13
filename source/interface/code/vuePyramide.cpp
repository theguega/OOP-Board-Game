#include "vuePyramide.h"
#include "vueCarte.h"
#include "vueJeton.h"
#include "back-end/carte.hpp"

vuePyramide::vuePyramide(QWidget* parent, int hauteur, int largeur, Pyramide& pyr) :
    QWidget(parent), h(hauteur), l(largeur), pyramide(pyr) {
    layoutPyrVer = new QVBoxLayout;
    layoutPrincipal = new QVBoxLayout;
    layoutAllCartes = new QHBoxLayout;
    layoutPaquets = new QVBoxLayout;

    placerCartes();

    // initialisation des paquets
    layoutPaquets->addWidget(new vuePaquet(pyr.getPioche1(), h/(this->hauteur + 1), l/(this->hauteur + 4)));
    layoutPaquets->addWidget(new vuePaquet(pyr.getPioche2(), h/(this->hauteur + 1), l/(this->hauteur + 4)));
    layoutPaquets->addWidget(new vuePaquet(pyr.getPioche3(), h/(this->hauteur + 1), l/(this->hauteur + 4)));


    layoutAllCartes->addLayout(layoutPaquets);
    layoutAllCartes->addLayout(layoutPyrVer);

    boutonAfficherInfo = new QPushButton("Cacher les informations des cartes");
    connect(boutonAfficherInfo, &QPushButton::clicked, this, &vuePyramide::boutonAfficherInfoClique);

    layoutPrincipal->addLayout(layoutAllCartes);
    layoutPrincipal->addWidget(boutonAfficherInfo);
    setLayout(layoutPrincipal);
}

void vuePyramide::boutonAfficherInfoClique(){
    if(infoAffichee){
        for(size_t i = 0; i < cartesPyramide.size(); i++){
            cartesPyramide[i]->cacherInfo();
        }
        infoAffichee = false;
        boutonAfficherInfo->setText("Afficher les informations des cartes");
    }
    else{
        for(size_t i = 0; i < cartesPyramide.size(); i++){
            cartesPyramide[i]->afficherInfo();
        }
        infoAffichee = true;
        boutonAfficherInfo->setText("Cacher les informations des cartes");
    }
}

void vuePyramide::placerCartes(){
    for (auto pt : cartesPyramide) {
        delete pt;
    }
    for (int i = 0; i < hauteur; ++i) {
        QLayout *layoutToRemove = layoutPyrVer->takeAt(0)->layout();
        if (layoutToRemove != nullptr) {
            delete layoutToRemove;
        }
    }
    cartesPyramide.clear();
    for(int i = 0; i < hauteur; i++){
        QHBoxLayout* layoutPyrHor = new QHBoxLayout;
        for(int j = 0; j < pyramide.getNbCartesNiv(i); j++){
            vueCarte* temp = new vueCarte(nullptr, h/(this->hauteur + 1), l/(this->hauteur + 4), pyramide.getCarte(i, j));
            temp->setPosition(new position(i, j));
            cartesPyramide.push_back(temp);
            layoutPyrHor->addWidget(temp);
        }
        layoutPyrVer->addLayout(layoutPyrHor);
    }
}

/*void vuePyramide::insererCarte(position* pos){

}*/

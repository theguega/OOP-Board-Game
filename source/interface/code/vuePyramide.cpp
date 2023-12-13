#include "vuePyramide.h"
#include "vueCarte.h"
#include "vueJeton.h"
#include "back-end/carte.hpp"

vuePyramide::vuePyramide(QWidget* parent, int hauteur, int largeur, Pyramide& pyr) :
    QWidget(parent), h(hauteur), l(largeur) {
    layoutPyrVer = new QVBoxLayout;
    layoutPrincipal = new QVBoxLayout;
    layoutAllCartes = new QHBoxLayout;
    layoutPaquets = new QVBoxLayout;
    Bonus bonus(Couleur::BLEU, 3);
    Prix prix(0, 1, 2, 3, 1, 0);
    Carte* carte = new Carte(TypeCarte::Niv1, prix, Capacite::None, Capacite::None, bonus, 2, 1, 5);

    for(int i = 0; i < this->hauteur; i++){
        QHBoxLayout* layoutPyrHor = new QHBoxLayout;
        for(int j = i; j < 5; j++){
            vueCarte* temp = new vueCarte(nullptr, h/(this->hauteur + 1), l/(1.6*(this->hauteur + 1)), carte);
            layoutPyrHor->addWidget(temp);
            cartesPyramide.push_back(temp);
        }
        layoutPyrHor->setAlignment(Qt::AlignCenter);
        layoutPyrVer->addLayout(layoutPyrHor);
    }

    // initialisation des paquets
    layoutPaquets->addWidget(new vuePaquet(pyr.getPioche1(), h/(this->hauteur + 1), l/(1.6*(this->hauteur + 1))));
    layoutPaquets->addWidget(new vuePaquet(pyr.getPioche2(), h/(this->hauteur + 1), l/(1.6*(this->hauteur + 1))));
    layoutPaquets->addWidget(new vuePaquet(pyr.getPioche3(), h/(this->hauteur + 1), l/(1.6*(this->hauteur + 1))));


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

/*void vuePyramide::insererCarte(position* pos){

}*/

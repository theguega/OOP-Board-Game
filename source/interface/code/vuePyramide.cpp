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

    for (vueCarte* carte : cartesPyramide)
    {
        // Connect the cardClicked signal of each VueCarte to the cardClicked signal of VuePyramide.
        connect(carte, &vueCarte::carteAchetee, this, &vuePyramide::cardClicked);

        connect(carte, &vueCarte::carteReservee, this, &vuePyramide::cardClickedResa);

    }

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
    for(int i = 0; i < hauteur; i++){
        QHBoxLayout* layoutPyrHor = new QHBoxLayout;
        for(unsigned int j = 0; j < pyramide.getNbCartesNiv(i); j++){
            vueCarte* temp = new vueCarte(nullptr, h/(this->hauteur + 1), l/(this->hauteur + 4), pyramide.getCarte(i, j));
            temp->setPosition(new position(i, j));
            cartesPyramide.push_back(temp);
            layoutPyrHor->addWidget(temp);
        }
        layoutPyrHor->setAlignment(Qt::AlignCenter);
        layoutPyrVer->addLayout(layoutPyrHor);
    }
}

vueCarte* vuePyramide::getCartePosition(int i, int j){
    for (vueCarte* carte : cartesPyramide) {
        position* pos = carte->getPosition();
        if (pos != nullptr && pos->getx() == i && pos->gety() == j) {
            return carte; // Retourne la carte correspondant à la position spécifiée
        }
    }
    return nullptr; // Retourne nullptr si aucune carte correspondante n'est trouvée
}

void vuePyramide::changerPointeurs(){
    for(unsigned int i = 0; i < hauteur; i++){
        for(unsigned int j = 0; j < pyramide.getNbCartesNiv(i); j++){
            vueCarte* temp = getCartePosition(i, j);
            temp->setCarte(pyramide.getCarte(i, j));
        }
    }
    update();
}

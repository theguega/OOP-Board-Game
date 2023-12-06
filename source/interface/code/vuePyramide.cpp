#include "vuePyramide.h"
#include "vueCarte.h"
#include "vueJeton.h"

vuePyramide::vuePyramide(QWidget* parent, int hauteur, int largeur) : QWidget(parent), h(hauteur), l(largeur) {
    layoutPyrVer = new QVBoxLayout;
    layoutPrincipal = new QVBoxLayout;

    for(int i = 0; i < this->hauteur; i++){
        QHBoxLayout* layoutPyrHor = new QHBoxLayout;
        for(int j = i; j < 5; j++){
            vueCarte* temp = new vueCarte(nullptr, h/(this->hauteur + 1), l/(1.6*(this->hauteur + 1)));
            layoutPyrHor->addWidget(temp);
            cartesPyramide.push_back(temp);
        }
        layoutPyrHor->setAlignment(Qt::AlignCenter);
        layoutPyrVer->addLayout(layoutPyrHor);
    }

    boutonAfficherInfo = new QPushButton("Cacher les informations des cartes");
    connect(boutonAfficherInfo, &QPushButton::clicked, this, &vuePyramide::boutonAfficherInfoClique);

    layoutPrincipal->addLayout(layoutPyrVer);
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

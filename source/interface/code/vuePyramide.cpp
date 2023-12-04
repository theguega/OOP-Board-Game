#include "vuePyramide.h"
#include "vueCarte.h"
#include "vueJeton.h"

vuePyramide::vuePyramide(QWidget* parent, int hauteur, int largeur) : QWidget(parent), h(hauteur), l(largeur) {
    layoutPyrVer = new QVBoxLayout;
    layoutPrincipal = new QVBoxLayout;
    for(int i = 0; i < this->hauteur; i++){
        QHBoxLayout* layoutPyrHor = new QHBoxLayout;
        for(int j = i; j < this->hauteur; j++){
            layoutPyrHor->addWidget(new vueCarte(nullptr, h/this->hauteur, l/(1.6*this->hauteur)));
        }
        layoutPyrHor->setAlignment(Qt::AlignCenter);
        layoutPyrVer->addLayout(layoutPyrHor);
    }
    layoutPrincipal->addLayout(layoutPyrVer);
    setLayout(layoutPrincipal);
}

/*void vuePyramide::insererCarte(position* pos){

}*/

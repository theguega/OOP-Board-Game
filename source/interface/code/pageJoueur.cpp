#include "pageJoueur.h"

pageJoueur::pageJoueur(QWidget* parent, Joueur* joueur, int hP, int lP, int hC, int lC) :
    QWidget(parent), hP(hP), lP(lP), hC(hC), lC(lC), joueur(joueur){
    cartesReserveesLayout = new QVBoxLayout;
    cartesPossedeesLayout = new QVBoxLayout;
    jetonsPossedesLayout = new QVBoxLayout;
    informations = new QHBoxLayout;
    layoutBas = new QHBoxLayout;
    layout = new QVBoxLayout;

    afficheCouronnes = new QLabel;
    affichePtPrestiges = new QLabel;

    for(int i = 0; i < 3; i++){
        listePrivileges.push_back(new vuePrivilege(hP, lP));
        informations->addWidget(listePrivileges[i]);
    }

    for(int i = 0; i < 3; i++){
        cartesReservees.push_back(new vueCarteJoueur(nullptr, hC, lC, nullptr));
        cartesReserveesLayout->addWidget(cartesReservees[i]);
    }

    informations->addWidget(afficheCouronnes);
    informations->addWidget(affichePtPrestiges);

    layoutBas->addLayout(cartesReserveesLayout);
    layoutBas->addLayout(cartesPossedeesLayout);
    layoutBas->addLayout(jetonsPossedesLayout);

    layout->addLayout(informations);
    layout->addLayout(layoutBas);

    setLayout(layout);
}

void pageJoueur::refreshJoueur(Joueur* joueurCourant){

    if(joueur->getNbPrivileges() != 0){
        for(size_t i = 0; i < joueur->getNbPrivileges(); i++){
            listePrivileges[i]->show();
        }
    }
    for(size_t i = joueur->getNbPrivileges(); i < 3; i++){
        listePrivileges[i]->hide();
    }

    setAfficherCouronnes();
    setAfficherPtPrestiges();

    for(const auto& couleur : Couleurs){
        if(couleur != Couleur::OR){
            for(size_t i = 0; i < joueur->getNbCartes(couleur); i++){
                const Carte* temp = &joueur->getCarte(couleur, i);
                if(!estDansCartes(temp)){
                    vueCarteJoueur* vcj = new vueCarteJoueur(nullptr, hC, lC, temp);
                    vcj->setPasReserver();
                    vcj->setComplete();
                    cartesPossedees.push_back(vcj);
                    cartesPossedeesLayout->addWidget(vcj);
                }
            }
        }
    }
    for(size_t i = 0; i < cartesPossedees.size(); i++){
        if(i == cartesPossedees.size() - 1){
            cartesPossedees[i]->setComplete();
        }
        else{
            cartesPossedees[i]->setIncomplete();
        }
    }

    int k = 0;
    for(const auto& couleur : Couleurs){
        if(couleur != Couleur::OR){
            for(size_t i = 0; i < joueur->getNbCartesReservees(couleur); i++){
                const Carte* temp = &joueur->getCarteReservee(couleur, i);
                cartesReservees[k]->setCarte(temp);
                k++;
            }
        }
    }
    for(int i = k; i < 3; i++){
        cartesReservees[i]->setCarte(nullptr);
    }

    update();
}

bool pageJoueur::estDansCartes(const Carte* c){
    for(size_t i = 0; i < cartesPossedees.size(); i++){
        if(cartesPossedees[i]->getCarte() == c){
            return true;
        }
    }
    return false;
}

void vuePrivilege::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QPolygon triangleSup;
    QPolygon triangleInf;

    triangleSup << QPoint(0, 0) << QPoint(l, 0) << QPoint(l/2, h/2);
    triangleInf << QPoint(l, h) << QPoint(0, h) << QPoint(l/2, h/2);

    painter.setBrush(QColor("#B4B4B3"));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawPolygon(triangleSup);
    painter.drawPolygon(triangleInf);
    painter.setBrush(QColor("#FF9AC7"));
    painter.drawEllipse(QPoint(l/2, h/2), l/4, l/4);
}

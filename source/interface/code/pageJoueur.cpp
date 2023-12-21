#include "pageJoueur.h"

pageJoueur::pageJoueur(QWidget* parent, Joueur* joueur, int hP, int lP, int hC, int lC, int tj) :
    QWidget(parent), hP(hP), lP(lP), hC(hC), lC(lC), tailleJeton(tj), joueur(joueur){
    cartesReserveesLayout = new QVBoxLayout;
    cartesReserveesLayout->setAlignment(Qt::AlignTop);
    cartesPossedeesLayout = new QVBoxLayout;
    cartesPossedeesLayout->setAlignment(Qt::AlignTop);
    cartesPossedeesLayout->setSpacing(0);
    jetonsPossedesLayout = new QVBoxLayout;
    jetonsPossedesLayout->setAlignment(Qt::AlignTop);
    informations = new QHBoxLayout;
    layoutBas = new QHBoxLayout;
    layout = new QVBoxLayout;

    afficheCouronnes = new QLabel;
    affichePtPrestiges = new QLabel;
    affichePseudo = new QLabel(QString::fromStdString("Joueur : " + joueur->getPseudo()));
    affichePseudo->setAlignment(Qt::AlignCenter);

    for(int i = 0; i < 3; i++){
        listePrivileges.push_back(new vuePrivilege(hP, lP));
        informations->addWidget(listePrivileges[i]);
    }

    for(int i = 0; i < 3; i++){
        cartesReservees.push_back(new vueCarteJoueur(nullptr, hC, lC, nullptr));
        cartesReserveesLayout->addWidget(cartesReservees[i]);
        connect(cartesReservees[i], &vueCarteJoueur::carteAchetee, this, &pageJoueur::acheterCarteReservee);
    }

    for(const auto& couleur : Couleurs){
        if(couleur != Couleur::INDT){
            vueJetonJoueur* temp = new vueJetonJoueur(nullptr, new Jeton(couleur), tailleJeton, 0);
            jetonsPossedes[couleur] = temp;
            jetonsPossedesLayout->addWidget(temp);
        }
    }

    informations->addWidget(afficheCouronnes);
    informations->addWidget(affichePtPrestiges);

    layoutBas->addLayout(cartesReserveesLayout);
    layoutBas->addLayout(cartesPossedeesLayout);
    layoutBas->addLayout(jetonsPossedesLayout);

    informations->setAlignment(Qt::AlignCenter);
    layoutBas->setAlignment(Qt::AlignCenter);

    layout->addWidget(affichePseudo);
    layout->addLayout(informations);
    layout->addLayout(layoutBas);
    layout->setAlignment(Qt::AlignCenter);

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
                    vcj->setEstReservee(false);
                    vcj->setEstRetournee(true);
                    vcj->setEstComplete(true);
                    cartesPossedees.push_back(vcj);
                    cartesPossedeesLayout->addWidget(vcj);
                }
            }
        }
    }
    for(size_t i = 0; i < cartesPossedees.size(); i++){
        if(i == cartesPossedees.size() - 1){
            cartesPossedees[i]->setEstComplete(true);
        }
        else{
            cartesPossedees[i]->setEstComplete(false);
        }
    }

    int k = 0;
    for(const auto& couleur : Couleurs){
        if(couleur != Couleur::OR){
            for(size_t i = 0; i < joueur->getNbCartesReservees(couleur); i++){
                const Carte* temp = &joueur->getCarteReservee(couleur, i);
                cartesReservees[k]->setCarte(temp);
                cartesReservees[k]->show();
                cartesReservees[k]->setEstComplete(true);
                cartesReservees[k]->setEstReservee(true);
                if(joueurCourant == joueur){
                    cartesReservees[k]->setEstRetournee(true);
                }
                else{
                    cartesReservees[k]->setEstRetournee(false);
                }
                k++;
            }
        }
    }

    for(int i = k; i < 3; i++){
        cartesReservees[i]->setCarte(nullptr);
    }

    for(const auto& couleur : Couleurs){
        if(couleur != Couleur::INDT){
            jetonsPossedes[couleur]->setN(joueur->getNbJetons(couleur));
        }
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

int pageJoueur::positionDansMap(const Carte* carte){
    Couleur c = carte->getBonus().getCouleur();
    int nb = 0;
    for(size_t i = 0; i < cartesReservees.size(); i++){
        if(carte == cartesReservees[i]->getCarte()){
            return nb;
        }
        else if(cartesReservees[i]->getCarte()->getBonus().getCouleur() == c){
            nb += 1;
        }
    }
    return -1;
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

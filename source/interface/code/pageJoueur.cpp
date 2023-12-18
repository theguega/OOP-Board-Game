#include "pageJoueur.h"

pageJoueur::pageJoueur(QWidget* parent, Joueur* joueur, int h, int l) : QWidget(parent), hP(h), lP(l){
    cartesReserveesLayout = new QVBoxLayout;
    cartesPossedeesLayout = new QVBoxLayout;
    jetonsPossedesLayout = new QVBoxLayout;
    informations = new QHBoxLayout;
    layout = new QHBoxLayout;

    layout->addLayout(cartesReserveesLayout);
    layout->addLayout(cartesPossedeesLayout);
    layout->addLayout(jetonsPossedesLayout);

    for(int i = 0; i < 3; i++){
        listePrivileges.push_back(new vuePrivilege(h, l));
        informations->addWidget(listePrivileges[i]);
    }

    setLayout(layout);
}

void pageJoueur::refreshJoueur(Joueur* joueurCourant){
    for(int i = 0; i < joueur->getNbPrivileges(); i++){
        listePrivileges[i]->show();
    }
    for(int i = joueur->getNbPrivileges(); i < 3; i++){
        listePrivileges[i]->hide();
    }
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

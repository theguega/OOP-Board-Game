#include <QWidget>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QLabel>
#include <QDebug>
#include <QEvent>
#include <QStackedWidget>
#include <QTimer>
#include "vueCarte.h"

carteVisuel::carteVisuel(QWidget *parent, int hauteur, int largeur, QColor couleur) : QWidget(parent){ //CarteVisuel sera la partie visuel de la carte
    h = hauteur; //Def la hauteur des cartes
    l = largeur; //Def la largeur des cartes
    triangleColor = couleur; //Def la couleur des cartes (sera gerer par un swithc apres avec la connection au back
    setFixedSize(l, h); //Fixe la taille de la carte
}

void carteVisuel::paintEvent(QPaintEvent *) { //Permet de faire les dessins vectoriels sur la carte
    QPainter painter(this);

    QPolygonF rectangle; //Creer un Polygone Qt en y mettant des points
    rectangle << QPointF(0, 0) << QPointF(l, 0) << QPointF(l, h) << QPointF(0, h); //On ajoute les points du rectangles
    painter.setBrush(Qt::white); //On definie la couleur du pinceau en blanc
    painter.drawPolygon(rectangle); //On colorie le polygone

    painter.setPen(QPen(Qt::black, 2)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
    painter.drawRect(0, 0, width(), height()); //On peind ce rectangle (permet de fair eun contour de la carte)

    QPolygonF triangle; //Creer un polygone Qt
    triangle << QPointF(0, 0) << QPointF(l, 0) << QPointF(0, h/3); //Ajoute les points du triangle
    painter.setBrush(triangleColor); //Prend la couleur definit
    painter.drawPolygon(triangle); //Colorie le triangle

    QPolygonF cercle;

    int numPoints = 50;
    double radius = h/10 - 1;
    double centerX = h/10;
    double centerY = h / 5 * 4 + h/10;
    //Definit les cercles avec un Polygone de plusieurs points

    for (int i = 0; i < numPoints; ++i) {
        double angle = 2 * M_PI * i / numPoints;
        double x = centerX + radius * cos(angle);
        double y = centerY + radius * sin(angle);
        cercle << QPointF(x, y);
    }

    painter.setBrush(Qt::blue); //Change la couleur du pinceau
    painter.drawPolygon(cercle); //Dessine le polygone

    //A terme, for avec changement de couleur pour mettre les plusieurs jetons de couleurs differents

    painter.setPen(Qt::black); //Ajout le numero dans le triangle
    painter.setFont(QFont("Arial", 12));
    painter.drawText(l/10, h/6, QString::number(numero));
}

carteInfo::carteInfo(QWidget* parent, int hauteur, int largeur, std::string texte) : QLabel(parent){ //Carte info sera la partie avec les infos de la carte
    l = largeur; //Def la hauteur des cartes
    h = hauteur; //Def la largeur des cartes

    setText(QString::fromStdString(texte)); //Def le texte du QLabel
    setFixedSize(l, h); //Fixe la taille

}

vueCarte::vueCarte(QWidget* parent) : QStackedWidget(parent){ //C'est un QStackedWidget afin de gerer plus facilement le changement entre les infos et le visu
    setFixedSize(l, h); //Fixe la taille
    /*switch(carte->getCouleur())*/

    visu = new carteVisuel(nullptr, h,l, triangleColor); //Ajoute le visuel de la carte
    info = new carteInfo(nullptr, h, l, texteInfo); //Ajoute les infos de la carte

    addWidget(visu); //visu devient l'index 0
    addWidget(info); //visu devient l'index 1

    setMouseTracking(true); //Autorise le tracking de la souris pour les enterEvent et leaveEvent
    //setAttribute(Qt::WA_Hover, true);
}

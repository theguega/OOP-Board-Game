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

void carteVisuel::paintEvent(QPaintEvent *event) { //Permet de faire les dessins vectoriels sur la carte
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(Qt::white); //On definie la couleur du pinceau en blanc
    painter.drawPolygon(rect()); //On colorie le polygone

    painter.setPen(QPen(Qt::black, 2)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
    painter.drawRect(rect()); //On peind ce rectangle (permet de fair eun contour de la carte)

    QPolygonF triangle; //Creer un polygone Qt
    triangle << QPointF(0, 0) << QPointF(l - 2, 0) << QPointF(0, (h-2)/3); //Ajoute les points du triangle
    painter.setBrush(triangleColor); //Prend la couleur definit
    painter.drawPolygon(triangle); //Colorie le triangle

    QPolygonF cercle;

    int numPoints = 50;
    double radius = h/10 - 2;
    double centerX = h/10 + 1;
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

carteInfo::carteInfo(QWidget* parent, int hauteur, int largeur, std::string texte) : QWidget(parent){ //Carte info sera la partie avec les infos de la carte
    l = largeur; //Def la hauteur des cartes
    h = hauteur; //Def la largeur des cartes
    setFixedSize(l, h); //Fixe la taille

    labelInfo = new QLabel;
    labelInfo->setText(QString::fromStdString(texte)); //Def le texte du QLabel

    layout = new QVBoxLayout;
    layout->addWidget(labelInfo);
    setLayout(layout);

}

void carteInfo::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(Qt::white); //On definie la couleur du pinceau en blanc
    painter.drawPolygon(rect()); //On colorie le polygone

    painter.setPen(QPen(Qt::black, 2)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
    painter.drawRect(rect()); //On peind ce rectangle (permet de fair eun contour de la carte)
}

vueCarte::vueCarte(QWidget* parent, int hauteur, int largeur, Carte* carte) : QStackedWidget(parent), h(hauteur), l(largeur){ //C'est un QStackedWidget afin de gerer plus facilement le changement entre les infos et le visu
    setFixedSize(l, h); //Fixe la taille
    /*switch(carte->getCouleur())*/

    visu = new carteVisuel(nullptr, h,l, triangleColor); //Ajoute le visuel de la carte
    info = new carteInfo(nullptr, h, l, texteInfo); //Ajoute les infos de la carte

    addWidget(visu); //visu devient l'index 0
    addWidget(info); //visu devient l'index 1

    setMouseTracking(true); //Autorise le tracking de la souris pour les enterEvent et leaveEvent
    //setAttribute(Qt::WA_Hover, true);
}

bool vueCarte::event(QEvent *event){
    if(affichageInfo){
        if (event->type() == QEvent::Enter) {
            qDebug() << "C'est un evenement d'entree (Enter Event).";
            setCurrentIndex(1);
            return true; // evenement traite
        }
        else if (event->type() == QEvent::Leave){
            qDebug() << "C'est un evenement de sorti (Leave Event).";
            setCurrentIndex(0);
            return true; // evenement traite
        }
    }

    // Appel a la methode parent pour gerer d'autres types d'evenements
    return QWidget::event(event);
}

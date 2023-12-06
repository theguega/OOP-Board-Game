#include <QWidget>
#include <QPushButton>
#include <interface/code/vueJeton.h>

vueJeton::vueJeton(QWidget* parent, int rad, Jeton* jeton) : QPushButton(parent){
    this->jeton = jeton;
    switch(jeton->getCouleur()){
    case Couleur::BLANC:
        Qcouleur = QColor("white");
        QcouleurClair = QColor("white");
        couleurContour = QColor("black");
        break;

    case Couleur::BLEU:
        Qcouleur = QColor("blue");
        QcouleurClair = QColor("lightblue");
        couleurContour = QColor("black");
        break;

    case Couleur::VERT:
        Qcouleur = QColor("green");
        QcouleurClair = QColor("lightgreen");
        couleurContour = QColor("black");
        break;

    case Couleur::ROUGE:
        Qcouleur = QColor("red");
        QcouleurClair = QColor("#CD5C5C");
        couleurContour = QColor("black");
        break;

    case Couleur::NOIR:
        Qcouleur = QColor("black");
        QcouleurClair = QColor("black");
        couleurContour = QColor("white");
        break;

    case Couleur::PERLE:
        Qcouleur = QColor("#FF69B4");
        QcouleurClair = QColor("#FFB6C1");
        couleurContour = QColor("black");
        break;

    case Couleur::OR:
        Qcouleur = QColor("yellow");
        QcouleurClair = QColor("lightyellow");
        couleurContour = QColor("black");
        break;
    }

    this->rad = rad;

    setFixedSize(rad*2, rad*2); //Fixe la taille et qui permet d'avoir une taille de 2x le rad pour avoir pile la taille du bouton

    afficherCroix = false; //afficherCroix est un booleen pour savoir si on montre la croix de selection (false d'origine)
    setFlat(true);
    setStyleSheet("QPushButton:pressed { border: none; }"); // Annule le style du contour quand le bouton est presse

}

void vueJeton::apparaitre(){ //Fait apparaitre le jeton (utile quand on voudra les remettre sur le plateau)
    show();
}

void vueJeton::disparaitre(){ //Fait dispparaitre le jeton (utile quand on voudra les enelevr du plateau)
    hide();
}

bool vueJeton::getEstVisible(){ //Je sais plus a quoi ca sert (surement inutile)
    return estVisible;
}

void vueJeton::changeAfficherCroix(){ //Change l'affichage de la croix par son inverse
    afficherCroix = !afficherCroix;
    update();
}

void vueJeton::enleverCroix(){ //Enleve la croix du jeton (utilse quand on voudra faire une deselection depuis le plateau)
    afficherCroix = false;
    update();
}

void vueJeton::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event); // Appel a la methode paintEvent de la classe de base

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Pour des bords plus lisses

    int side = qMin(width(), height()); // Taille minimale entre largeur et hauteur pour un carre
    QPoint center = rect().center(); // Centre du bouton

    if(afficherCroix){
        painter.setPen(QPen(Qt::red, 2)); // Contours noirs de largeur 1 pixel

    }
    else{
        painter.setPen(QPen(couleurContour, 3)); // Contours noirs de largeur 1 pixel
    }

    // Dessin du cercle au centre du bouton
    int circleRadius = side / 2; // Rayon du cercle pour qu'il soit centre
    painter.setBrush(QBrush(QcouleurClair)); // Utilisation de la couleur definie
    painter.drawEllipse(center, circleRadius - 3, circleRadius - 3);

    // Definition des points pour creer le grand losange
    QVector<QPoint> bigDiamondShape;
    const int bigWidth = side * 2 / 3;
    const int bigHeight = side * 3 / 4;

    bigDiamondShape << QPoint(center.x(), center.y() - bigHeight / 2); // Point superieur
    bigDiamondShape << QPoint(center.x() + bigWidth / 2, center.y()); // Point droit
    bigDiamondShape << QPoint(center.x(), center.y() + bigHeight / 2); // Point inferieur
    bigDiamondShape << QPoint(center.x() - bigWidth / 2, center.y()); // Point gauche

    // Dessin du grand losange
    painter.setPen(QPen(couleurContour, 2)); // Contours noirs de largeur 2 pixels
    painter.setBrush(Qcouleur); // Couleur bleue pour le grand losange
    painter.drawPolygon(bigDiamondShape);

    // Definition des points pour creer le petit losange (effet 3D)
    QVector<QPoint> smallDiamondShape;
    const int smallWidth = side / 4;
    const int smallHeight = side / 3;

    smallDiamondShape << QPoint(center.x(), center.y() - smallHeight / 2); // Point superieur
    smallDiamondShape << QPoint(center.x() + smallWidth / 2, center.y()); // Point droit
    smallDiamondShape << QPoint(center.x(), center.y() + smallHeight / 2); // Point inferieur
    smallDiamondShape << QPoint(center.x() - smallWidth / 2, center.y()); // Point gauche

    // Dessin du petit losange (effet 3D)
    QRadialGradient gradient(center, side / 4, center); // Gradient radial pour l'effet 3D
    gradient.setColorAt(0, QColor(255, 255, 255, 0)); // Couleur transparente au centre
    gradient.setColorAt(0.5, QColor(255, 255, 255, 60)); // Couleur semi-opaque au milieu
    gradient.setColorAt(1, QColor(255, 255, 255, 120)); // Couleur plus opaque a l'exterieur

    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(smallDiamondShape);

    // Dessin des lignes reliant les coins des deux losanges (plus fins)
    painter.setPen(QPen(couleurContour, 1)); // Lignes noires plus fines
    painter.drawLine(bigDiamondShape[0], smallDiamondShape[0]);
    painter.drawLine(bigDiamondShape[1], smallDiamondShape[1]);
    painter.drawLine(bigDiamondShape[2], smallDiamondShape[2]);
    painter.drawLine(bigDiamondShape[3], smallDiamondShape[3]);

    // Dessin des contours du losange central en noir
    painter.setPen(QPen(couleurContour, 2)); // Contours noirs de largeur 2 pixels
    painter.drawPolygon(smallDiamondShape);

    // Effet lorsqu'on clique sur le bouton (pressed)
    if (this->isDown()) {
        painter.setBrush(QColor(0, 0, 0, 30)); // Couleur sombre pour simuler un effet enfonce
        painter.setPen(Qt::NoPen);
        painter.drawPolygon(bigDiamondShape);
        painter.drawEllipse(center, circleRadius, circleRadius);
    }
}

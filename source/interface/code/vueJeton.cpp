#include <QWidget>
#include <QPushButton>
#include <interface/code/vueJeton.h>

vueJeton::vueJeton(QWidget* parent, int rad, Couleur couleur) : QPushButton(parent){
    switch(couleur){
    case Couleur::BLANC:
        this->couleur = couleur;
        Qcouleur = QColor("white");
        QcouleurClair = QColor("white");
        couleurContour = QColor("black");
        break;

    case Couleur::BLEU:
        this->couleur = couleur;
        Qcouleur = QColor("blue");
        QcouleurClair = QColor("lightblue");
        couleurContour = QColor("black");
        break;

    case Couleur::VERT:
        this->couleur = couleur;
        Qcouleur = QColor("green");
        QcouleurClair = QColor("lightgreen");
        couleurContour = QColor("black");
        break;

    case Couleur::ROUGE:
        this->couleur = couleur;
        Qcouleur = QColor("red");
        QcouleurClair = QColor("#CD5C5C");
        couleurContour = QColor("black");
        break;

    case Couleur::NOIR:
        this->couleur = couleur;
        Qcouleur = QColor("black");
        QcouleurClair = QColor("black");
        couleurContour = QColor("white");
        break;

    case Couleur::PERLE:
        this->couleur = couleur;
        Qcouleur = QColor("#FF69B4");
        QcouleurClair = QColor("#FFB6C1");
        couleurContour = QColor("black");
        break;

    case Couleur::OR:
        this->couleur = couleur;
        Qcouleur = QColor("yellow");
        QcouleurClair = QColor("lightyellow");
        couleurContour = QColor("black");
        break;
    }

    this->rad = rad;

    setFixedSize(rad*2, rad*2); //Fixe la taille et qui permet d'avoir une taille de 2x le rad pour avoir pile la taille du bouton

    afficherCroix = false; //afficherCroix est un booléen pour savoir si on montre la croix de sélection (false d'origine)
    setFlat(true);
    setStyleSheet("QPushButton:pressed { border: none; }"); // Annule le style du contour quand le bouton est pressé

}

void vueJeton::apparaitre(){ //Fait apparaitre le jeton (utile quand on voudra les remettre sur le plateau)
    show();
}

void vueJeton::disparaitre(){ //Fait dispparaitre le jeton (utile quand on voudra les enelevr du plateau)
    hide();
}

bool vueJeton::getEstVisible(){ //Je sais plus à quoi ça sert (surement inutile)
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
    QPushButton::paintEvent(event); // Appel à la méthode paintEvent de la classe de base

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Pour des bords plus lisses

    int side = qMin(width(), height()); // Taille minimale entre largeur et hauteur pour un carré
    QPoint center = rect().center(); // Centre du bouton

    if(afficherCroix){
        painter.setPen(QPen(Qt::red, 2)); // Contours noirs de largeur 1 pixel

    }
    else{
        painter.setPen(QPen(couleurContour, 3)); // Contours noirs de largeur 1 pixel
    }

    // Dessin du cercle au centre du bouton
    int circleRadius = side / 2; // Rayon du cercle pour qu'il soit centré
    painter.setBrush(QBrush(QcouleurClair)); // Utilisation de la couleur définie
    painter.drawEllipse(center, circleRadius - 3, circleRadius - 3);

    // Définition des points pour créer le grand losange
    QVector<QPoint> bigDiamondShape;
    const int bigWidth = side * 2 / 3;
    const int bigHeight = side * 3 / 4;

    bigDiamondShape << QPoint(center.x(), center.y() - bigHeight / 2); // Point supérieur
    bigDiamondShape << QPoint(center.x() + bigWidth / 2, center.y()); // Point droit
    bigDiamondShape << QPoint(center.x(), center.y() + bigHeight / 2); // Point inférieur
    bigDiamondShape << QPoint(center.x() - bigWidth / 2, center.y()); // Point gauche

    // Dessin du grand losange
    painter.setPen(QPen(couleurContour, 2)); // Contours noirs de largeur 2 pixels
    painter.setBrush(Qcouleur); // Couleur bleue pour le grand losange
    painter.drawPolygon(bigDiamondShape);

    // Définition des points pour créer le petit losange (effet 3D)
    QVector<QPoint> smallDiamondShape;
    const int smallWidth = side / 4;
    const int smallHeight = side / 3;

    smallDiamondShape << QPoint(center.x(), center.y() - smallHeight / 2); // Point supérieur
    smallDiamondShape << QPoint(center.x() + smallWidth / 2, center.y()); // Point droit
    smallDiamondShape << QPoint(center.x(), center.y() + smallHeight / 2); // Point inférieur
    smallDiamondShape << QPoint(center.x() - smallWidth / 2, center.y()); // Point gauche

    // Dessin du petit losange (effet 3D)
    QRadialGradient gradient(center, side / 4, center); // Gradient radial pour l'effet 3D
    gradient.setColorAt(0, QColor(255, 255, 255, 0)); // Couleur transparente au centre
    gradient.setColorAt(0.5, QColor(255, 255, 255, 60)); // Couleur semi-opaque au milieu
    gradient.setColorAt(1, QColor(255, 255, 255, 120)); // Couleur plus opaque à l'extérieur

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
        painter.setBrush(QColor(0, 0, 0, 30)); // Couleur sombre pour simuler un effet enfoncé
        painter.setPen(Qt::NoPen);
        painter.drawPolygon(bigDiamondShape);
        painter.drawEllipse(center, circleRadius, circleRadius);
    }

    /*if (afficherCroix) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        if(couleur != Couleur::BLANC){
            painter.setPen(Qt::white);
        }
        else{
            painter.setPen(Qt::black);
        }

        // Dessiner une croix qui prend tout le cercle et est centrée avec une rotation de 45 degrés
        painter.save(); // Sauvegarder l'état actuel du QPainter
        painter.translate(width() / 2, height() / 2); // Translation pour le centre du bouton
        painter.rotate(45); // Rotation de 45 degrés
        painter.drawLine(-width() / 2, 0, width() / 2, 0); // Horizontal
        painter.drawLine(0, -height() / 2, 0, height() / 2); // Vertical
        painter.restore(); // Restaurer l'état précédent du QPainter
    }*/
}

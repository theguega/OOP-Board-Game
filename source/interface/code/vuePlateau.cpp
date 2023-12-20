#include <QWidget>
#include <array>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRandomGenerator>
#include <QPainterPath>
#include <QHBoxLayout>
#include <unistd.h>
#include "vuePlateau.h"
#include "vueJeton.h"

grilleJetons::grilleJetons(QWidget* parent, int hauteur, int largeur, int nbJ, int tJ, std::vector<vueJeton*>* pt) :
    QWidget(parent), ptListeJetons(pt), nbJetons(nbJ), h(hauteur), l(largeur), tailleJeton(tJ){

    rnbJetons = static_cast<int>(sqrt(nbJetons));
    for(int i = 0; i < rnbJetons; i++){
        for(int j = 0; j < rnbJetons; j++){
            listeRectangles.push_back(new QRect(2 * i * (tailleJeton+5) + (l-(2*(tailleJeton+5))*rnbJetons)/2, 2 * j * (tailleJeton+5), 2*(tailleJeton+5), 2*(tailleJeton+5)));
        }
    }
    setFixedSize(l, h);
}

void grilleJetons::placerJeton(const Jeton* jeton, int i, int j){
    vueJeton* newJeton = new vueJeton(this, tailleJeton, jeton, new position((i), (j)));
    int k = i + j * rnbJetons;
    int newX = listeRectangles[k]->center().x() - tailleJeton + 2.5;
    int newY = listeRectangles[k]->center().y() - tailleJeton + 2.5;
    newJeton->move(newX,  newY);
    ptListeJetons->push_back(newJeton);
    update();
}

void grilleJetons::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dessiner le plateau avec les emplacements carrés
    painter.setPen(QPen(QColor("#A0522D"), 4)); // Couleur des bordures
    painter.setBrush(QColor("#DEB887")); // Couleur de fond des emplacements

    for (int i = 0; i < nbJetons; ++i) {
        painter.drawRect(*listeRectangles[i]);
    }

    int cx = 5 * (tailleJeton+5) + (l-(2*(tailleJeton+5))*rnbJetons)/2; // Coordonnée X du centre
    int cy = 5 * (tailleJeton+5); // Coordonnée Y du centre

    painter.setPen(QPen(Qt::black, 2)); // Couleur et épaisseur des flèches

    int dx = 0;
    int dy = 0;

    int currentX = cx; // Coordonnée X actuelle
    int currentY = cy; // Coordonnée Y actuelle

    size_t h = 1, d = 1, b = 2, g = 2;
    size_t direction = 0, avancement = 0;
    for(int step = 0; step < nbJetons - 1; step++) {
        switch (direction) {
        case 0:  // Vers le haut
            avancement++;
            if (avancement == h){
                avancement = 0;
                direction = 1;
                h += 2;
            }
            dx = 0;
            dy = -1;
            break;
        case 1:  // Vers la droite
            avancement++;
            if (avancement == d){
                avancement = 0;
                direction = 2;
                d += 2;
            }
            dx = 1;
            dy = 0;
            break;
        case 2:  // Vers le bas
            avancement++;
            if (avancement == b){
                avancement = 0;
                direction = 3;
                b += 2;
            }
            dx = 0;
            dy = 1;
            break;
        case 3:  // Vers la gauche
            avancement++;
            if (avancement == g){
                avancement = 0;
                direction = 0;
                g += 2;
            }
            dx = -1;
            dy = 0;
            break;
        }
        int nextX = currentX + dx * 2*(tailleJeton+5);
        int nextY = currentY + dy * 2*(tailleJeton+5);

        painter.drawLine(currentX, currentY, nextX, nextY);

        int triangleSize = 10; // Taille du triangle (base/hauteur)
        int midX = (currentX + nextX) / 2; // Coordonnée X du milieu de la ligne
        int midY = (currentY + nextY) / 2; // Coordonnée Y du milieu de la ligne

        QPolygon triangle;

        // Dessiner un triangle dans la direction spécifiée
        if(currentY == nextY){ // Ligne horizontale
            if(currentX < nextX){ // Vers la droite
                triangle << QPoint(midX + triangleSize / 2, midY);
                triangle << QPoint(midX - triangleSize / 2, midY + triangleSize / 2);
                triangle << QPoint(midX - triangleSize / 2, midY - triangleSize / 2);
            }
            else{ // Vers la gauche
                triangle << QPoint(midX - triangleSize / 2, midY);
                triangle << QPoint(midX + triangleSize / 2, midY + triangleSize / 2);
                triangle << QPoint(midX + triangleSize / 2, midY - triangleSize / 2);
            }
        }
        else{ // Ligne verticale
            if(currentY < nextY){ // Vers le bas
                triangle << QPoint(midX, midY + triangleSize / 2);
                triangle << QPoint(midX + triangleSize / 2, midY - triangleSize / 2);
                triangle << QPoint(midX - triangleSize / 2, midY - triangleSize / 2);
            }
            else{ // Vers le haut
                triangle << QPoint(midX, midY - triangleSize / 2);
                triangle << QPoint(midX + triangleSize / 2, midY + triangleSize / 2);
                triangle << QPoint(midX - triangleSize / 2, midY + triangleSize / 2);
            }
        }

        QPainterPath path;
        path.addPolygon(triangle);

        painter.fillPath(path, Qt::black);

        currentX = nextX;
        currentY = nextY;
    }
}

vuePlateau::vuePlateau(QWidget* parent, int hauteur, int largeur, Plateau& plat) : QWidget(parent), plateau(plat){
    h = hauteur; //Def la hateur du plateau
    l = largeur; //Def la largeur du plateau

    std::vector<Couleur> listeCouleur = { Couleur::BLANC, Couleur::BLEU, Couleur::VERT, Couleur::ROUGE, Couleur::NOIR, Couleur::PERLE, Couleur::OR};
    std::vector<int> indices;
    for (int i = 0; i < 25; ++i) {
        indices.push_back(i % 7); // Utilisez l'operation modulo pour obtenir des indices entre 0 et n-1
    }

    // Melangez les indices pour les rendre aleatoires
    std::mt19937 generateur(static_cast<unsigned int>(std::time(0)));
    std::shuffle(indices.begin(), indices.end(), generateur);

    nbJetons = 25; //Nombre de jetons sur la plateau (sera recuperer depuis le back apres)
    rnbJetons = static_cast<int>(sqrt(nbJetons));
    setFixedSize(l, h); //Fixe la taille du plateau
    //sac = plateau->getSac();

    tailleJeton = (h - 100)/(2*rnbJetons) - 5;
    grille = new grilleJetons(nullptr, h-100, l, nbJetons, tailleJeton, &listeJetons);

    placerJetons();

    boutonValider = new QPushButton("Valider le choix des jetons"); //Creer le bouton valider (pour la selection des jetons)
    boutonValider->setStyleSheet("color blue;");

    layout = new QVBoxLayout; //Layout pour mettre le Grid + les boutons en dessous

    layout -> addWidget(grille); //Ajoute layoutJetons au layout vertical
    layout -> addWidget(boutonValider); //Ajoute layoutJetons au layout vertical (faire un QHBoxLayout pour ajouter aussi un bouton desselctionner)

    setLayout(layout); //Set le layout

    //connect(boutonValider, &QPushButton::clicked, this, &vuePlateau::validerJetons); //connect boutonValider avec valliderJetons
    connect(boutonValider, &QPushButton::clicked, this, &vuePlateau::signalValiderAppuye);
    info = new popUpInfo(nullptr, "Vos jetons ont bien ete ajoute");
}

void vuePlateau::placerJetons(){
    for(unsigned int i = 0; i < rnbJetons; i++){
        for(int j = 0; j < rnbJetons; j++){
            grille->placerJeton(plateau.getJeton(i,j), i , j);
        }
    }
    for(unsigned int i = 0; i < listeJetons.size(); i++){
        QObject::connect(listeJetons[i], &vueJeton::clicked, [this, i]() {
            boutonClique(i); //Permet d'appeler la fonction boutonClique(int i) lorsque le bouton i est clique
        });
    }
    for(unsigned int i = 0; i < 3; i++){
        jetonSelection[i] = nullptr; //Initialise jetonSelection avec nullptr
    }
    update();
}

void vuePlateau::changerPointeurs(){
    for(int i = 0; i < rnbJetons; i++){
        for(int j = 0; j < rnbJetons; j++){
            int k = i  * rnbJetons + j;
            listeJetons[k]->show();
            listeJetons[k]->enleverCroix();
            listeJetons[k]->setJeton(plateau.getJeton(i,j));
        }
    }
    for(int i = 0; i < 3; i++){
        jetonSelection[i] = nullptr;
    }
    nbJetonSelection = 0;
}

void vuePlateau::boutonClique(int i){
    int j = 0;
    if(estSelectionne(listeJetons[i])){
        for(j = 0; j < 3; j++){
            if(jetonSelection[j] == listeJetons[i]){
                jetonSelection[j] = nullptr;
                listeJetons[i] -> changeAfficherCroix();
                nbJetonSelection -= 1;
            }
        }
    }
    else{
        if(nbJetonSelection < 3){
            listeJetons[i] -> changeAfficherCroix();
            while(jetonSelection[j] != nullptr){
                j++;
            }
            jetonSelection[j] = listeJetons[i];
            nbJetonSelection += 1;
        }
    }
    qDebug() << nbJetonSelection;
}

void vuePlateau::deselectionner(){
    for(int i = 0; i < nbJetons; i++){
        listeJetons[i] -> enleverCroix();
    }
    for(int i = 0; i < 3; i++){
        jetonSelection[i] = nullptr;
    }
}

bool vuePlateau::estSelectionne(vueJeton* jeton){
    for(int j = 0; j < 3; j++){
        if(jetonSelection[j] == jeton){
            return true;
        }
    }
    return false;
}

void vuePlateau::validerJetons(){
    info -> show();
    for(int j = 0; j < 3; j++){
        if(jetonSelection[j] != nullptr){
            jetonSelection[j] -> enleverCroix();
        }
    }
}

void vuePlateau::cacherElements(){
    info -> close();
}

/*void vuePlateau::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event); // Appel a la methode paintEvent de la classe de base

    QPainter painter(boutonValider);

    painter.setRenderHint(QPainter::Antialiasing); // Pour des bords plus lisses
    painter.setBrush(Qt::red);
    painter.drawRect(boutonValider->rect());

}*/


std::vector<std::pair<int, int>> vuePlateau::getSelectionJetons() const {
    std::vector<std::pair<int, int>> tmp;
    for (int i = 0; i < 3; i++){
        if(jetonSelection[i] != nullptr){
            auto pair = std::make_pair(jetonSelection[i]->getPosition()->getx(), jetonSelection[i]->getPosition()->gety());
            tmp.push_back(pair);
        }
    }
    return tmp;
}

void boutonSac::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event); // Appel a la methode paintEvent de la classe de base

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Pour des bords plus lisses

    // Choix de la couleur du sac en fonction de l'état de fondu
    QColor couleurSac = isDown() ? QColor("#654321") : QColor("#8B4513"); // Couleur marron foncé en fondu

    painter.setBrush(QBrush(couleurSac));
    QPolygonF triangle;
    triangle << QPointF(l * 0.5, h * 0.5) << QPointF(l * 0.65, 0)
             << QPointF(l * 0.35, 0); // Points pour former un triangle
    painter.drawPolygon(triangle); // Triangle isocèle

    // Fond du sac : cercle avec un rectangle isocèle
    painter.drawEllipse(l / 10, h / 10, l * 0.8, h * 0.5); // Cercle

    // Corde
    painter.setPen(QPen(Qt::black, 3)); // Couleur noire pour la corde
    painter.drawLine(l * 0.65, h * 0.1, l * -1.2, h * 0.25); // Corde gauche
    painter.drawLine(l * 0.65, h * 0.1, l * 1.1, h * 0.25); // Corde droite

}

position* vuePlateau::selecteOr(){
    int nbOr = 0;
    for(int i = 0; i < 3; i++){
        if(jetonSelection[i] != nullptr){
            if(jetonSelection[i]->getJeton()->getCouleur() == Couleur::OR){
                nbOr += 1;
            }
            else{
                return nullptr;
            }
        }
    }
    if(nbOr != 1){
        return nullptr;
    }
    else{
        for(int i = 0; i < 3; i++){
            if(jetonSelection[i] != nullptr){
                return jetonSelection[i]->getPosition();
            }
        }
    }
    return nullptr;
}

#include <QWidget>
#include <array>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRandomGenerator>
#include <QPainterPath>
#include <QHBoxLayout>
#include "vuePlateau.h"
#include "vueJeton.h"

grilleJetons::grilleJetons(QWidget* parent, int hauteur, int largeur, int nbJ, int tJ, std::vector<vueJeton*>* pt) :
    QWidget(parent), h(hauteur), l(largeur), nbJetons(nbJ), tailleJeton(tJ), ptListeJetons(pt){

    rnbJetons = static_cast<int>(sqrt(nbJetons));
    int lRectangle = l / rnbJetons;
    int hRectangle = h / rnbJetons;
    for(int i = 0; i < rnbJetons; i++){
        for(int j = 0; j < rnbJetons; j++){
            listeRectangles.push_back(new QRect(2 * i * (tailleJeton+5) + (l-(2*(tailleJeton+5))*rnbJetons)/2, 2 * j * (tailleJeton+5), 2*(tailleJeton+5), 2*(tailleJeton+5)));
        }
    }
    setFixedSize(l, h);
}

void grilleJetons::placerJetons(){
    for (auto it = ptListeJetons->begin(); it != ptListeJetons->end(); ++it) {
        int j = (*it)->getPosition()->getx() + (*it)->getPosition()->gety() * rnbJetons;
        int newX = listeRectangles[j]->center().x() - ((*it)->width() / 2) + 2.5;
        int newY = listeRectangles[j]->center().y() - ((*it)->height() / 2) + 2.5;
        (*it)->move(newX,  newY);
    }
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

vuePlateau::vuePlateau(QWidget* parent, int hauteur, int largeur) : QWidget(parent){
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

    int tailleJeton = (h - 100)/(2*rnbJetons) - 5;

    grille = new grilleJetons(nullptr, h-100, l, nbJetons, tailleJeton, &listeJetons);

    for(int i = 0; i < nbJetons; i++){
        //Creer un getteur pour les Jetons
        listeJetons.push_back(new vueJeton(grille, tailleJeton, new Jeton(listeCouleur[indices[i]]), new position((i/rnbJetons), (i%rnbJetons))));
        QObject::connect(listeJetons[i], &vueJeton::clicked, [this, i]() {
            boutonClique(i); //Permet d'appeler la fonction boutonClique(int i) lorsque le bouton i est clique
        });
    }
    for(int i = 0; i < 3; i++){
        jetonSelection[i] = nullptr; //Initialise jetonSelection avec nullptr
    }

    grille->placerJetons();

    boutonValider = new QPushButton("Valider le choix des jetons"); //Creer le bouton valider (pour la selection des jetons)
    boutonValider->setStyleSheet("color blue;");

    layout = new QVBoxLayout; //Layout pour mettre le Grid + les boutons en dessous

    layout -> addWidget(grille); //Ajoute layoutJetons au layout vertical
    layout -> addWidget(boutonValider); //Ajoute layoutJetons au layout vertical (faire un QHBoxLayout pour ajouter aussi un bouton desselctionner)

    setLayout(layout); //Set le layout

    connect(boutonValider, &QPushButton::clicked, this, &vuePlateau::validerJetons); //connect boutonValider avec valliderJetons

    info = new popUpInfo(nullptr, "Vos jetons ont bien ete ajoute");
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

/*vueJeton* vuePlateau::recupererBouton(Jeton* jeton){
    for(int i = 0; i < 25; i++){
        if(listeJetons[i]->getJeton() == jeton){
            return listeJetons[i];
        }
    }
    return nullptr;
}*/

/*void vuePlateau::remplirPlateau(){
    vueJeton* temp;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 25; j++){
            //faire un getteur pour le plateau
            temp = recupererBouton(plateau.getJeton(i, j));
            temp->apparaitre(position(i, j));
        }
    }
}*/

/*void vuePlateau::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int horizontalSpacing = layoutJetons->spacing();
    int verticalSpacing = layoutJetons->spacing();

    // Taille du côté d'une cellule (emplacement)
    int tailleCelluleH = (h - 100)/sqrt(nbJetons) + horizontalSpacing * 3.2;
    int tailleCelluleV = (h - 100)/sqrt(nbJetons) + verticalSpacing;

    // Coordonnées de départ pour positionner le plateau
    int startX = xBoutonHG/3.5; // Coordonnée X de départ
    int startY = yBoutonHG/3.5; // Coordonnée Y de départ

    // Dessiner le plateau avec les emplacements carrés
    painter.setPen(QPen(QColor("#A0522D"), 4)); // Couleur des bordures
    painter.setBrush(QColor("#DEB887")); // Couleur de fond des emplacements

    for (int i = 0; i < sqrt(nbJetons); ++i) {
        for (int j = 0; j < sqrt(nbJetons); ++j) {
            int x = startX + i * (tailleCelluleH);
            int y = startY + j * (tailleCelluleV);

            painter.drawRect(x, y, tailleCelluleH, tailleCelluleV);
        }
    }

    int cx = startX + (tailleCelluleH * sqrt(nbJetons)) / 2; // Coordonnée X du centre
    int cy = startY + (tailleCelluleV * sqrt(nbJetons)) / 2; // Coordonnée Y du centre

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
        int nextX = currentX + dx * tailleCelluleH;
        int nextY = currentY + dy * tailleCelluleV;

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
}*/

#include <QWidget>
#include <array>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRandomGenerator>
#include <QPainterPath>
#include "vuePlateau.h"
#include "vueJeton.h"

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
    setFixedSize(l, h); //Fixe la taille du plateau
    //sac = plateau->getSac();

    vueJeton* temp = new vueJeton(nullptr, (h - 100)/(2*sqrt(nbJetons)), new Jeton(listeCouleur[indices[0]]));
    listeJetons[0] = temp;
    layoutJetons -> addWidget(listeJetons[0], 0, 0);
    QObject::connect(listeJetons[0], &vueJeton::clicked, [this]() {
        boutonClique(0); //Permet d'appeler la fonction boutonClique(int i) lorsque le bouton i est clique
    });

    for(int i = 1; i < nbJetons; i++){
        //Creer un getteur pour les Jetons
        listeJetons[i] = new vueJeton(nullptr, (h - 100)/(2*sqrt(nbJetons)), new Jeton(listeCouleur[indices[i]]));
        layoutJetons -> addWidget(listeJetons[i], i / 5, i % 5);
        QObject::connect(listeJetons[i], &vueJeton::clicked, [this, i]() {
            boutonClique(i); //Permet d'appeler la fonction boutonClique(int i) lorsque le bouton i est clique
        });
    }
    for(int i = 0; i < 3; i++){
        jetonSelection[i] = nullptr; //Initialise jetonSelection avec nullptr
    }

    boutonValider = new QPushButton("Valider le choix des jetons"); //Creer le bouton valider (pour la selection des jetons)

    layout = new QVBoxLayout; //Layout pour mettre le Grid + les boutons en dessous

    layout -> addLayout(layoutJetons); //Ajoute layoutJetons au layout vertical
    layout -> addWidget(boutonValider); //Ajoute layoutJetons au layout vertical (faire un QHBoxLayout pour ajouter aussi un bouton desselctionner)

    setLayout(layout); //Set le layout

    connect(boutonValider, &QPushButton::clicked, this, &vuePlateau::validerJetons); //connect boutonValider avec valliderJetons

    info = new popUpInfo(nullptr, "Vos jetons ont bien ete ajoute");

    xBoutonHG = temp->pos().x();
    yBoutonHG = temp->pos().y();
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

void vuePlateau::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int horizontalSpacing = layoutJetons->spacing();
    int verticalSpacing = layoutJetons->spacing();

    // Taille du côté d'une cellule (emplacement)
    int tailleCelluleH = (h - 100)/sqrt(nbJetons) + horizontalSpacing * 3.2;
    int tailleCelluleV = (h - 100)/sqrt(nbJetons) + verticalSpacing;

    // Coordonnées de départ pour positionner le plateau
    int startX = xBoutonHG + horizontalSpacing * 2; // Coordonnée X de départ
    int startY = yBoutonHG + verticalSpacing * 2.4; // Coordonnée Y de départ

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
}

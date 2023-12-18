#include <QScreen>
#include <QSize>
#include <QApplication>
#include "pageCreation.h"
#include "toutesPages.h"
#include "pageJeu.h"

pageJeu::pageJeu(QString statut_partie, QString pseudo_j_1, type type_j_1, QString pseudo_j_2, type type_j_2, QWidget *parent) : QWidget(parent) {
    control = new Controller(statut_partie, pseudo_j_1, type_j_1, pseudo_j_2, type_j_2);
    control->lancerPartie();
    ecran = QGuiApplication::primaryScreen();
    tailleEcran = ecran->availableGeometry().size();

    tailleLargeur = tailleEcran.width();
    tailleHauteur = tailleEcran.height();

    vPlateau = new vuePlateau(nullptr, tailleHauteur - 100, (tailleLargeur-30) / 2, control->getPlateau());
    joueur1 = new pageJoueur(nullptr);
    joueur2 = new pageJoueur(nullptr);
    vPyramide = new vuePyramide(nullptr, tailleHauteur - 100, (tailleLargeur-30) / 2, control->getPyramide());

    afficherJ1 = new QPushButton("Afficher Joueur 1");
    afficherJ2 = new QPushButton("Afficher Joueur 1");

    connect(afficherJ1, &QPushButton::clicked, this, [this]() {
        this->joueur1->afficher(true);
    });
    connect(afficherJ2, &QPushButton::clicked, this, [this]() {
        this->joueur2->afficher(true);
    });

    partieHaute = new QHBoxLayout;
    partieMoyenne = new QHBoxLayout;
    partieBasse = new QHBoxLayout;
    layout = new QVBoxLayout;
    layoutPrivileges = new QVBoxLayout;

    for(int i = 0; i < 3; i++){
        layoutPrivileges->addWidget(new vuePrivilege((vPlateau->height() - 130)/3, 30));
    }

    labelJC = new QLabel;
    partieHaute -> addWidget(labelJC);
    partieHaute -> setAlignment(Qt::AlignCenter);
    setLabelJC();

    partieMoyenne -> addLayout(layoutPrivileges);
    partieMoyenne -> addWidget(vPlateau);
    partieMoyenne -> addWidget(vPyramide);
    partieMoyenne -> setAlignment(Qt::AlignVCenter);

    partieBasse -> addWidget(afficherJ1);
    partieBasse -> addWidget(afficherJ2);

    layout -> addLayout(partieHaute);
    layout -> addLayout(partieMoyenne);
    layout -> addLayout(partieBasse);
    setLayout(layout);

    aSauvegarde = new popUpValider(nullptr, "quitter sans sauvegarder");
    connect(aSauvegarde -> getBoutonOui(), &QPushButton::clicked, this, &pageJeu::quitter);
    connect(aSauvegarde -> getBoutonNon(), &QPushButton::clicked, this, &pageJeu::rester);
    connect(vPlateau, &vuePlateau::signalValiderAppuye, this, &pageJeu::validerSelectionJeton);
}

void pageJeu::validerSelectionJeton()
{
    // Appeler la méthode verifJetons avec la sélection actuelle de la vue
    std::pair<bool, QString> validationResult = control->verifJetons(vPlateau->getSelectionJetons());

    // Traiter le résultat de la validation
    handleValidationResult(validationResult.first, validationResult.second);
}


void pageJeu::handleValidationResult(bool isValid, const QString &message)
{
    if(isValid){
        control->recupererJetons(vPlateau->getSelectionJetons());
        vPlateau->changerPointeurs();
        control->changerJoueurCourant();
        setLabelJC();
        update();
    }
    else{
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        infos->show();
    }
}


void pageJeu::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(Qt::white); //On definie la couleur du pinceau en blanc
    painter.drawPolygon(rect()); //On colorie le polygone

    painter.setPen(QPen(Qt::black, 5)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
    painter.drawRect(rect()); //On peind ce rectangle (permet de fair eun contour de la carte)
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

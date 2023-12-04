#include <QScreen>
#include <QSize>
#include <QApplication>
#include "pageCreation.h"
#include "toutesPages.h"
#include "pageJeu.h"

pageJeu::pageJeu(QWidget *parent) : QWidget(parent) {
    ecran = QGuiApplication::primaryScreen();
    tailleEcran = ecran->availableGeometry().size();

    tailleLargeur = tailleEcran.width();
    tailleHauteur = tailleEcran.height();

    vPlateau = new vuePlateau(nullptr, tailleHauteur - 100, tailleLargeur / 2);
    joueur1 = new pageJoueur(nullptr);
    joueur2 = new pageJoueur(nullptr);
    vPyramide = new vuePyramide(nullptr, tailleHauteur - 100, tailleLargeur / 2);

    afficherJ1 = new QPushButton("Afficher Joueur 1");
    afficherJ2 = new QPushButton("Afficher Joueur 1");

    connect(afficherJ1, &QPushButton::clicked, this, [this]() {
        this->joueur1->afficher(true);
    });
    connect(afficherJ2, &QPushButton::clicked, this, [this]() {
        this->joueur2->afficher(true);
    });

    partieHaute = new QHBoxLayout;
    partieBasse = new QHBoxLayout;
    layout = new QVBoxLayout;

    partieHaute -> addWidget(vPlateau);
    partieHaute -> addWidget(vPyramide);

    partieBasse -> addWidget(afficherJ1);
    partieBasse -> addWidget(afficherJ2);

    layout -> addLayout(partieHaute);
    layout -> addLayout(partieBasse);
    setLayout(layout);

    aSauvegarde = new popUpValider(nullptr, "quitter sans sauvegarder");
    connect(aSauvegarde -> getBoutonOui(), &QPushButton::clicked, this, &pageJeu::quitter);
    connect(aSauvegarde -> getBoutonNon(), &QPushButton::clicked, this, &pageJeu::rester);
}


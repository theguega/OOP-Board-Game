#ifndef VUEPYRAMIDE_H
#define VUEPYRAMIDE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <vector>
#include "vueCarte.h"
#include "back-end/espacejeux.hpp"

class vuePyramide : public QWidget{
    Q_OBJECT
private:
    int hauteur = 3;
    QVBoxLayout* layoutPyrVer;
    QVBoxLayout* layoutPaquets;
    QHBoxLayout* layoutAllCartes;
    QVBoxLayout* layoutPrincipal;
    QPushButton* boutonAfficherInfo;
    bool infoAffichee = true;
    int h;
    int l;
    std::vector<vueCarte*> cartesPyramide;
    Pyramide& pyramide;
public:
    vuePyramide(QWidget* parent, int hauteur, int largeur, Pyramide& pyr);
    void afficherCartes();
    void boutonAfficherInfoClique();
    void placerCartes();
    vueCarte* getCartePosition(int i, int j);
    void changerPointeurs();
signals:
    void cardClicked(position* pos);
};

#endif // VUEPYRAMIDE_H

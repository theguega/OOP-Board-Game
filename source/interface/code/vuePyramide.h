#ifndef VUEPYRAMIDE_H
#define VUEPYRAMIDE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <vector>
#include "vueCarte.h"

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
public:
    vuePyramide(QWidget* parent, int hauteur, int largeur);
    void afficherCartes();
    void boutonAfficherInfoClique();
};

#endif // VUEPYRAMIDE_H

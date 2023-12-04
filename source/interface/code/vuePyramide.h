#ifndef VUEPYRAMIDE_H
#define VUEPYRAMIDE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class vuePyramide : public QWidget{
    Q_OBJECT
private:
    int hauteur = 4;
    QVBoxLayout* layoutPyrVer;
    QVBoxLayout* layoutPrincipal;
    QPushButton* boutonAfficherInfo;
    int h;
    int l;
public:
    vuePyramide(QWidget* parent, int hauteur, int largeur);
    void afficherCartes();
};

#endif // VUEPYRAMIDE_H

#ifndef VUEPLATEAU_H
#define VUEPLATEAU_H

#include <QWidget>
#include <QGridLayout>
#include <array>
#include <vector>
#include <QCloseEvent>
#include <QPushButton>
#include "popUp.h"
#include "vueJeton.h"
//#include <jetons.hpp>

class grilleJetons : public QWidget{
    Q_OBJECT
private:
    std::vector<vueJeton*>* ptListeJetons;
    std::vector<QRect*> listeRectangles;
    int nbJetons;
    int rnbJetons;
    int h;
    int l;
    int tailleJeton;
public:
    grilleJetons(QWidget* parent = nullptr, int hauteur = 0, int largeur = 0, int nbJ = 0, int tJ = 0, std::vector<vueJeton*>* pt = nullptr);
    void placerJetons();
    void paintEvent(QPaintEvent *event);
};

class vuePlateau : public QWidget{
    Q_OBJECT
private:
    //Choix entre pointeur et reference ?
    //Sac* sac;
    //Plateau* plateau;
    grilleJetons* grille;
    std::vector<vueJeton*> listeJetons;
    int nbJetons;
    int rnbJetons;

    std::array<vueJeton*, 3> jetonSelection;
    int nbJetonSelection = 0;

    int h;
    int l;

    int xBoutonHG;
    int yBoutonHG;

    QPushButton* boutonValider;
    popUpInfo* info;

    QVBoxLayout* layout;
public:
    vuePlateau(QWidget* parent, int hateur, int largeur);
    //void paintEvent(QPaintEvent *event);
    void boutonClique(int i);
    void deselectionner();
    bool estSelectionne(vueJeton* jeton);
    void validerJetons();
    void cacherElements();
    void afficherJetons(){for(int i = 0; i < nbJetons; i++){listeJetons[i]->show();}update();}
    //vueJeton* recupererBouton(Jeton* jeton);
    //void remplirPlateau();
};

#endif // VUEPLATEAU_H

#ifndef VUEPLATEAU_H
#define VUEPLATEAU_H

#include <QWidget>
#include <QGridLayout>
//#include <jetons.hpp>
#include <array>
#include <QCloseEvent>
#include <QPushButton>
#include "popUp.h"
#include "vueJeton.h"

class vuePlateau : public QWidget{
    Q_OBJECT
private:
    //Choix entre pointeur et référence ?
    //Sac* sac;
    //Plateau* plateau;
    std::array<vueJeton*, 25> listeJetons;
    QGridLayout* layoutJetons = new QGridLayout;
    int nbJetons;
    std::array<vueJeton*, 3> jetonSelection;
    int nbJetonSelection = 0;

    int h;
    int l;

    QPushButton* boutonValider;
    popUpInfo* info;

    QVBoxLayout* layout;
public:
    vuePlateau(QWidget* parent, int hateur, int largeur);
    void boutonClique(int i);
    void deselectionner();
    bool estSelectionne(vueJeton* jeton);
    void validerJetons();
    void cacherElements();
    //vueJeton* recupererBouton(Jeton* jeton);
    //void remplirPlateau();
};

#endif // VUEPLATEAU_H

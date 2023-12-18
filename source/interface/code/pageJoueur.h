#ifndef PAGEJOUEUR_H
#define PAGEJOUEUR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vector>
#include "vuePlateau.h"
#include "vueJeton.h"
#include "vueCarte.h"
#include "back-end/joueur.hpp"


class vuePrivilege : public QWidget{
    Q_OBJECT
private:
    int h;
    int l;
protected:
    void paintEvent(QPaintEvent *event);
public:
    vuePrivilege(int hauteur, int largeur) : h(hauteur), l(largeur){setFixedSize(l, h);}
};

class pageJoueur : public QWidget{
    Q_OBJECT
private:
    QVBoxLayout* cartesReserveesLayout; //Layout avec les cartes reservees
    QVBoxLayout* cartesPossedeesLayout; //Layout avec les cartes possedees
    QVBoxLayout* jetonsPossedesLayout; //Layout avec les jeton possedes
    QHBoxLayout* informations;
    QHBoxLayout* layout; //Layout principal

    Joueur* joueur;

    int hP, lP; //hauteur et largeur des privilèges;
    std::vector<vuePrivilege*> listePrivileges;

    std::vector<vueCarte*> cartesReservees; //Vecteur avec les cartes reservees
    std::vector<vueCarte*> cartesPossedees; //Vecteur avec les cartes possedees
    std::vector<vueJeton*> jetonsPossedes; //Vecteur avec les jeton possedes
public:
    pageJoueur(QWidget* parent, Joueur* joueur, int hP, int lP);
    void refreshJoueur(Joueur* joueurCourant);
};

#endif // PAGEJOUEUR_H

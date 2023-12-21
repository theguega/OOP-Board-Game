#ifndef PAGEJOUEUR_H
#define PAGEJOUEUR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vector>
#include <unordered_map>
#include "vuePlateau.h"
#include "vueJeton.h"
#include "vueCarte.h"
#include "back-end/joueur.hpp"
#include "back-end/carte.hpp"
#include "back-end/jetons.hpp"


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
    QHBoxLayout* layoutBas;
    QVBoxLayout* layout; //Layout principal

    QLabel* afficheCouronnes;
    QLabel* affichePtPrestiges;
    QLabel* affichePseudo;

    Joueur* joueur;

    int hP, lP, hC, lC, tailleJeton; //hauteur et largeur des privilèges, cartes et jeton;
    std::vector<vuePrivilege*> listePrivileges;

    std::vector<vueCarteJoueur*> cartesReservees; //Vecteur avec les cartes reservees
    std::vector<vueCarteJoueur*> cartesPossedees; //Vecteur avec les cartes possedees
    std::unordered_map<Couleur, vueJetonJoueur*> jetonsPossedes; //Vecteur avec les jeton possedes
public:
    pageJoueur(QWidget* parent, Joueur* joueur, int hP, int lP, int hC, int lC, int tj);
    void refreshJoueur(Joueur* joueurCourant);
    void setAfficherCouronnes(){afficheCouronnes->setText("Couronnes : " + QString::number(joueur->getNbCouronnes()));}
    void setAfficherPtPrestiges(){affichePtPrestiges->setText("Prestiges : " + QString::number(joueur->getptsPrestige()));}
    bool estDansCartes(const Carte* c);
    int positionDansMap(const Carte* carte);
    Joueur* getJoueur(){return joueur;}
signals:
    void acheterCarteReservee(const Carte* c);
};

#endif // PAGEJOUEUR_H

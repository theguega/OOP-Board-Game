#ifndef PAGEJOUEUR_H
#define PAGEJOUEUR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vector>
#include "vuePlateau.h"
#include "vueJeton.h"
#include "vueCarte.h"

class pageJoueur : public QWidget{
    Q_OBJECT
private:
    QHBoxLayout* cartesReserveesLayout; //Layout avec les cartes reservees
    QHBoxLayout* cartesPossedeesLayout; //Layout avec les cartes possedees
    QHBoxLayout* jetonsPossedesLayout; //Layout avec les jeton possedes
    QVBoxLayout* layout; //Layout principal

    QWidget* cartesReserveesWidget;
    QWidget* cartesPossedeesWidget;
    QWidget* jetonsPossedesWidget;

    std::vector<vueCarte*> cartesReservees; //Vecteur avec les cartes reservees
    std::vector<vueCarte*> cartesPossedees; //Vecteur avec les cartes possedees
    std::vector<vueJeton*> jetonsPossedes; //Vecteur avec les jeton possedes
public:
    pageJoueur(QWidget* parent);
    void ajouterCarteReservee(vueCarte* carte);
    void ajouterCartePossedee(vueCarte* carte);
    void ajouterJeton(vueJeton* jeton);
    void retirerJeton(vueJeton* jeton);
    void afficher(bool tourJoueur);
};

#endif // PAGEJOUEUR_H

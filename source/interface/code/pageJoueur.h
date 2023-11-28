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
    QHBoxLayout* cartesReserveesLayout;
    QHBoxLayout* cartesPossedeesLayout;
    QHBoxLayout* jetonsPossedesLayout;
    QVBoxLayout* layout;

    QWidget* cartesReserveesWidget;
    QWidget* cartesPossedeesWidget;
    QWidget* jetonsPossedesWidget;

    std::vector<vueCarte*> cartesReservees;
    std::vector<vueCarte*> cartesPossedees;
    std::vector<vueJeton*> jetonsPossedes;
public:
    pageJoueur(QWidget* parent);
    void ajouterCarteReservee(vueCarte* carte);
    void ajouterCartePossedee(vueCarte* carte);
    void ajouterJeton(vueJeton* jeton);
    void retirerJeton(vueJeton* jeton);
    void afficher(bool tourJoueur);
};

#endif // PAGEJOUEUR_H

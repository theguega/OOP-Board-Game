#ifndef PAGEJEU_H
#define PAGEJEU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScreen>
#include <QSize>
#include <interface/code/vuePlateau.h>
#include "interface/code/vuePlateau.h"
#include "interface/code/pageJoueur.h"
#include "interface/code/popUp.h"
#include "interface/code/vuePyramide.h"

class pageJeu : public QWidget {
    Q_OBJECT
private:
    vuePlateau* vPlateau; //Plateau de jetons
    pageJoueur* joueur1; //Page du joueur1
    pageJoueur* joueur2; //Page du joueur2
    vuePyramide* vPyramide; //Pyramide de carte

    QPushButton* afficherJ1; //Bouton pour afficher la page du joueur1
    QPushButton* afficherJ2; //Bouton pour afficher la page du joueur2

    QHBoxLayout* partieHaute; //Partie Haute à ranger (pyramide et plateau)
    QHBoxLayout* partieBasse; //Partie Basse à ranger (boutons)
    QVBoxLayout* layout;//Layout principal

    QScreen* ecran; //Récupère l'écran de l'utilisateur
    QSize tailleEcran; //Récupère la taille de l'écran

    int tailleLargeur; //Utile pour définir les tailles de sous objets
    int tailleHauteur; //Utile pour définir les tailles de sous objets

    popUpValider* aSauvegarde; //PopUp pour sauvegarder la partie
    bool quitterPage = false; //Utile pour la redéfinission de closeEvent
protected:
    void closeEvent(QCloseEvent *event) override { //Redéfinition de la méthode closeEvent
        if(!quitterPage){
            aSauvegarde -> show();
            event -> ignore();
        }
    }
    void quitter(){ //Permet de quitter la page
        quitterPage = true;
        aSauvegarde -> close();
        this -> close();
    }
    void rester(){ //Permet de restetr sur la page
        aSauvegarde -> close();
    }
public:
    pageJeu(QWidget *parent = nullptr);
    ~pageJeu() = default;
    void mousePressEvent(QMouseEvent* event) override { //Permet de cacher tous les elements quand on cique sur la page de Jeu
        joueur1 -> hide();
        joueur2 -> hide();
        vPlateau -> cacherElements();
        aSauvegarde -> hide();
        QWidget::mousePressEvent(event);
    }
};

#endif // PAGEJEU_H


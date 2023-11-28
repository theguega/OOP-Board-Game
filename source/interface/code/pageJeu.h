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

class pageJeu : public QWidget {
    Q_OBJECT
private:
    vuePlateau* vPlateau;
    pageJoueur* joueur1;
    pageJoueur* joueur2;

    QPushButton* afficherJ1;
    QPushButton* afficherJ2;

    QHBoxLayout* partieHaute;
    QHBoxLayout* partieBasse;
    QVBoxLayout* layout;

    QScreen* ecran;
    QSize tailleEcran;

    int tailleLargeur;
    int tailleHauteur;

    popUpValider* aSauvegarde;
    bool quitterPage = false;
protected:
    void closeEvent(QCloseEvent *event) override {
        if(!quitterPage){
            aSauvegarde -> show();
            event -> ignore();
        }
    }
    void quitter(){
        quitterPage = true;
        aSauvegarde -> close();
        this -> close();
    }
    void rester(){
        aSauvegarde -> close();
    }
public:
    pageJeu(QWidget *parent = nullptr);
    ~pageJeu() = default;
    void mousePressEvent(QMouseEvent* event) override {
        joueur1 -> hide();
        joueur2 -> hide();
        vPlateau -> cacherElements();
        aSauvegarde -> hide();
        QWidget::mousePressEvent(event);
    }
};

#endif // PAGEJEU_H


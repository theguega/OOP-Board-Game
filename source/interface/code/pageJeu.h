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
#include "back-end/controller.hpp"
#include "interface/code/popUp.h"
#include "back-end/joueur.hpp"




class pageJeu : public QWidget {
    Q_OBJECT
private:
    Controller* control;
    vuePlateau* vPlateau;            // Plateau de jetons
    pageJoueur* joueur1;             // Page du joueur1
    pageJoueur* joueur2;             // Page du joueur2
    vuePyramide* vPyramide;          // Pyramide de carte

    QPushButton* afficherJ1;         // Bouton pour afficher la page du joueur1
    QPushButton* afficherJ2;         // Bouton pour afficher la page du joueur2
    QPushButton* boutonSauvegarder;

    std::vector<vuePrivilege*> listePrivileges;
    boutonSac* bSac;

    QHBoxLayout* partieHaute;
    QHBoxLayout* partieMoyenne;      // Partie Haute a ranger (pyramide et plateau)
    QHBoxLayout* partieBasse;        // Partie Basse a ranger (boutons)
    QVBoxLayout* layout;             // Layout principal
    QVBoxLayout* layoutPrivileges;

    QLabel* labelJC;

    QScreen* ecran;                  // Recupere l'ecran de l'utilisateur
    QSize tailleEcran;               // Recupere la taille de l'ecran

    int tailleLargeur;               // Utile pour definir les tailles de sous objets
    int tailleHauteur;               // Utile pour definir les tailles de sous objets

    popUpValider* aSauvegarde;       // PopUp pour sauvegarder la partie
    popUpVictoire* victoire;
    bool quitterPage = false;        // Utile pour la redefinission de closeEvent
    std::pair<bool, Couleur> capa_en_cours = std::make_pair(false, Couleur::INDT);
    bool resa_en_cours = false;
    bool sauvegardeFait = false;
    bool partiefinie = false;

    std::vector<vueCarteNoble*> cartesNoble;
    QHBoxLayout* layoutNoble;
    QWidget* widgetNoble;
    std::vector<vueCarteNoble*> listeWidgetsNoble;
protected:
    void closeEvent(QCloseEvent *event) override {
        aSauvegarde -> hide();
        if(!quitterPage && !sauvegardeFait && !partiefinie){
            aSauvegarde -> show();
            event -> ignore();
        }
        else if (!partiefinie)
            emit fermerPopUp();
    }

    //quitter splendor
    void quitter(){
        quitterPage = true;
        aSauvegarde -> close();
        victoire->close();
        this -> close();
    }

    //rester sur splendor duel
    void rester(){
        aSauvegarde -> close();
    }

    //graphisme de l'espace de jeux
    void paintEvent(QPaintEvent *event) override;
public:
    //constructeur - destructeur
    pageJeu(QString statut_partie, QString pseudo_j_1 = "", type type_j_1 = type::HUMAIN, QString pseudo_j_2 = "", type type_j_2 = type::HUMAIN, QWidget *parent = nullptr);
    ~pageJeu() = default;

    void mousePressEvent(QMouseEvent* event) override {
        joueur1 -> hide();
        joueur2 -> hide();
        vPlateau -> cacherElements();
        aSauvegarde -> hide();
        QWidget::mousePressEvent(event);
    }

    void setLabelJC(){labelJC->setText(QString::fromStdString("C'est au tour de " + control->getJoueurCourant().getPseudo()));}

    void refresh();
    void verifNobles();
public slots:
    void checkVictoire();
    void verifJetons() ;

    //achat de carte
    void validerSelectionCarte(position* p);
    void handleValidationCarte(position* p, std::array<int, 7> prix);
    //achat carte reservee
    void validerAchatCarteReservee(const Carte* carte);
    void handleAchatCarteReservee(const Carte* carte, std::array<int, 7> prix);
    //reserver carte pyramide
    void validerResaCarte(position* p);
    void handleReservationCarte(position* p, position* pJ = nullptr);
    //reserver carte pioche
    void validerResaCartePioche(int nivPioche);
    void handleReservationCartePioche(int nivPioche);
    //remplir le plateau
    void remplirPlateau();
    //selection des jetons
    void validerSelectionJeton();
    void validerSelectionJetonPrivi();
    //gestiond e l'achat des cartes nobles
    void handleCartesNoble(size_t i, int niv = 3);

    void afficherPrivileges();
signals:
    void fermerPopUp();
};

#endif // PAGEJEU_H


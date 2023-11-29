#include "back-end/controller.hpp"
#include <filesystem>
#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QtSql>
#include "interface/code/vueCarte.h"
#include "interface/code/pageCreation.h"
#include "interface/code/vueJeton.h"
#include "interface/code/vuePlateau.h"
#include "interface/code/toutesPages.h"
#include <iostream>

//Mettez ici le chemin absolue vers le projet
//Theo
//std::filesystem::path projectPath = string("/Users/theoguegan/Documents/UTC/GI01/LO21/Projet_LO21");
//Samuel B
std::filesystem::path projectPath = string("\\Users\\Beziat\\Documents\\Projet_LO21\\source");
//Robert
//std::filesystem::path projectPath = string("/Users/robertantaluca/Desktop/Projet_LO21");
//Samuel M
//std::filesystem::path projectPath = string("C:/Users/samma/Documents/Programmation/LO21/Projet_LO21");
//Maxime





















//####################################
//###### Partie en mode Terminal #####
//####################################


/*int main(void) {
    Controller control;
    control.lancerPartie();
    control.getJoueurCourant().afficherJoueur();

    // simulation victoire d'un joueur
    int i = 0;
    if (i == 5)
        control.getJoueurCourant().updatePtsPrestige(16);
    control.getJoueurCourant().afficherJoueur();
    i++;
    control.tour_suivant();

    if (control.getPartie().getJoueur1()->estGagnant())
        cout << control.getPartie().getJoueur1()->getPseudo() << " est gagnant;"<<std::endl;
    else if (control.getPartie().getJoueur2()->estGagnant())
        cout << control.getPartie().getJoueur2()->getPseudo() << " est gagnant;"<<std::endl;

    return 0;
}*/















//avec boucle de jeux

/*

int main(void) {
    Controller control;
    control.getJoueurCourant().afficherJoueur();
    control.lancerPartie();

    while (control.getPartie().getJoueur1()->estGagnant() == false && control.getPartie().getJoueur2()->estGagnant() == false) {
        // TODO

        // tour pour chacun des joueurs
        for (unsigned int i = 0; i < 2; i++) {
            control.getJoueurCourant().afficherJoueur();

            unsigned int etat_tour = 0;
            while (etat_tour != 4) {
                // actions optionelles
                switch (etat_tour) {
                case 0:
                    unsigned int etat_action = 0;
                    while (etat_action != 4) {
                        switch (etat_action)
                        {
                        case 0:
                            std::cout << "Actions optionnelles: " << endl;
                            std::cout << "1. Utiliser un privilège" << endl;
                                    std:: cout << "2. Remplir le plateau" << endl;
                            std::cout << "3. Ne plus faire d'actions optionnelles" << endl;
                            std::cout << "Votre choix (1/2/3): ";
                            cin >> etat_action;
                            std::cout << endl;
                            break;

                        case 1:
                            try
                            {
                                control.utiliserPrivilege(control.getPartie().getEspaceJeux().getPlateau());
                                etat_action = 0;
                            }
                            catch(const std::exception& e)
                            {
                                std::cout << e.what() << '\n';
                                etat_action = 0;
                            }
                            break;
                        case 2:
                            try
                            {
                                control.remplirPlateau(control.getPartie().getEspaceJeux().getPlateau(), control.getPartie().getEspaceJeux().getSac(), control.getJoueurAdverse());
                                etat_action = 0;
                            }
                            catch(const std::exception& e)
                            {
                                std::cout << e.what() << '\n';
                                etat_action = 0;
                            }
                            break;

                        case 3:

                            etat_tour = 1;
                            etat_action = 4;
                            break;

                        default:
                            break;
                        }

                    }
                    break;


                case 1:
                    etat_action = 0;
                    while (etat_action != 4) {
                        switch (etat_action)
                        {
                        case 0:
                            std::cout << "Actions obligatoires: " << endl;
                            std::cout << "1. Récupérer des jetons" << endl;
                                    std:: cout << "2. Acheter une carte joaillerie" << endl;
                            std::cout << "3. Réserver une carte" << endl;
                                        cin >> etat_action;
                            std::cout << endl;
                            break;
                        case 1:
                            try
                            {
                                control.recupererJetons(control.getPartie().getEspaceJeux().getPlateau());
                                etat_action = 4;
                            }
                            catch(const std::exception& e)
                            {
                                std::cout << e.what() << '\n';
                                etat_action = 0;
                            }
                            break;
                        case 2:
                            try
                            {
                                control.acheterCarteJoaillerie(control.getPartie().getEspaceJeux().getPyramide());
                                etat_action = 4;
                            }
                            catch(const std::exception& e)
                            {
                                std::cout << e.what() << '\n';
                                etat_action = 0;
                            }
                            break;
                        case 3:
                            try
                            {
                                control.orReserverCarte(control.getPartie().getEspaceJeux().getPyramide(), control.getPartie().getEspaceJeux().getPlateau());
                                etat_action = 4;
                            }
                            catch(const std::exception& e)
                            {
                                std::cout << e.what() << '\n';
                                etat_action = 0;
                            }
                            break;
                        default:
                            break;
                        }
                        etat_tour = 2;

                    }
                    break;
                case 2:
                    //verif de fin de tout
                    break;


                default:
                    break;
                }
            }


        }

        control.setJoueurCourant(i); // dommage que changerJoueurCourant() ai disparu, je trouve cette solution moins élégante
    }

    return 0;
}

*/


















//#########################################
//###### Partie avec l'application Qt #####
//#########################################



int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    /*vueCarte carte = vueCarte(nullptr);
    carte.show();

    pageCreation page = pageCreation(nullptr);
    page.show();

    QWidget* widget = new QWidget;

    vueJeton* jeton = new vueJeton(nullptr);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(jeton);

    widget -> setLayout(layout);

    widget->show();

    vuePlateau* plateau = new vuePlateau(nullptr, 500, 500);
    plateau -> show();*/

    toutesPages* page = new toutesPages(nullptr, &app);
    page->show();

    return app.exec();
}



#include "back-end/controller.hpp"

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QtSql>

#include "back-end/exception.hpp"

#include "interface/code/vueCarte.h"
#include "interface/code/pageCreation.h"
#include "interface/code/vueJeton.h"
#include "interface/code/vuePlateau.h"
#include "interface/code/toutesPages.h"
#include <iostream>


//####################################
//###### Partie en mode Terminal #####
//####################################
//avec boucle de jeux

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    Controller control;
    control.lancerPartie();

    while (1) {
        // tour pour chacun des joueurs
        std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
        std::cout<< "Tour numero" << control.getPartie().getTour()+1 << endl;

            //correpond au tour de chaque joueur
            for (unsigned int i = 0; i < 2; i++) {
            std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------\n";
            std::cout<<"C'est a " <<control.getJoueurCourant().getPseudo()<<" de jouer : \n\n";
            control.getJoueurCourant().afficherJoueur();

            unsigned int etat_tour = 0;
            while (etat_tour != 10) {

                // actions optionelles
                switch (etat_tour) {
                case 0: {
                    bool a_deja_utilise_privilege = false;
                    bool a_deja_rempli_plateau = false;
                    unsigned int etat_action = 0;
                    while (etat_action != 10) {
                        switch (etat_action)
                        {
                        case 0:{
                            //appel du menu de choix des actions
                            etat_action = control.choixActionsOptionelles();
                            break;}
                        case 1:{
                            try
                            {
                                //utilisation d'un privilege
                                if (a_deja_utilise_privilege)
                                    throw SplendorException("Vous avez deja utilise cette action");
                                control.utiliserPrivilege(control.getPartie().getEspaceJeux().getPlateau());
                                a_deja_utilise_privilege = true;
                                etat_action = 0;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        }
                        case 2:{
                            try
                            {
                                //remplissage du plateau
                                if (a_deja_rempli_plateau)
                                    throw SplendorException("Vous avez deja utilise cette action");
                                control.remplirPlateau(control.getPartie().getEspaceJeux().getPlateau(), control.getPartie().getEspaceJeux().getSac());
                                a_deja_rempli_plateau = true;
                                etat_action = 0;

                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        }
                        case 3:{
                            etat_tour = 1;
                            etat_action = 10;
                            break;
                        }

                        case 9:{
                            control.quitter();
                            return 0;
                            return app.exec();
                        }

                        default:{
                            etat_action=0;
                            std::cout<<"Veuillez faire un choix correct !\n";
                            break;
                        }
                        }
                    }
                    break;
                }




                //actions obligatoires :
                case 1:{
                    unsigned int etat_action = 0;
                    while (etat_action != 10) {
                        switch (etat_action)
                        {
                        case 0:
                            //menu de choix des actions obligatoires
                            etat_action = control.choixActionsObligatoires();
                            break;
                        case 1:
                            try
                            {
                                //recuperation de jetons
                                control.recupererJetons(control.getPartie().getEspaceJeux().getPlateau());
                                etat_action = 10;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        case 2:
                            try
                            {
                                //achat carte joaillerie
                                control.acheterCarteJoaillerie(control.getPartie().getEspaceJeux());
                                etat_action = 10;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        case 3:
                            try
                            {
                                //reservation carte
                                control.orReserverCarte(control.getPartie().getEspaceJeux().getPyramide(), control.getPartie().getEspaceJeux().getPlateau());
                                etat_action = 10;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        case 9:{
                            control.quitter();
                            return 0;
                            return app.exec();

                        }
                        default:
                            etat_action=0;
                            std::cout<<"Veuillez faire un choix correct !\n";
                            break;
                        }
                        etat_tour = 2;
                    }
                    break;
                }



                //verification fin de tour d'un joueur
                case 2:{
                    //achat obligatoire d'une carte noble si le joueur a 3 ou 6 pts de prestige
                    if (control.getJoueurCourant().getptsPrestige() >= 3 or control.getJoueurCourant().getptsPrestige() >= 6) {
                        //rajouter une verif si il y a bien des cartes nobles
                        control.acheterCarteNoble(control.getPartie().getEspaceJeux().getPyramide());
                    }

                    //simulation de victoire

                    if (control.getJoueurCourant().getNbJetons() >= 4) {
                        std::cout << "Joueur " << control.getJoueurCourant().getPseudo() << " a gagne la partie" << std::endl;
                                etat_tour = 3;
                        break;
                    }

                    //fin du tour du joueur, on passe au joueur suivant
                    control.changerJoueurCourant();
                    etat_tour = 10;
                    break;
                }
                case 3:{
                    std::cout << "Fin de la partie !\nMerci d'avoir joue a Splendor Duel !\n";
                    return 0;
                    return app.exec();
                    break;
                }
                default:{
                    break;
                }
                }
            }
            //fin du tour :
            control.getPartie().incrementeTour();
        }
    }
    std::cout<<"le jeu n'est pas censer arriver la !!!";
    return 0;
    return app.exec();
}


//#########################################
//###### Partie avec l'application Qt #####
//#########################################



/*int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
//    vueCarte carte = vueCarte(nullptr);
//    carte.show();

//    pageCreation page = pageCreation(nullptr);
//    page.show();

//    QWidget* widget = new QWidget;

//    vueJeton* jeton = new vueJeton(nullptr);

//    QHBoxLayout* layout = new QHBoxLayout;
//    layout->addWidget(jeton);

//    widget -> setLayout(layout);

//    widget->show();

//    vuePlateau* plateau = new vuePlateau(nullptr, 500, 500);
//    plateau -> show();

    toutesPages* page = new toutesPages(nullptr, &app);
    page->show();

    return app.exec();
}*/

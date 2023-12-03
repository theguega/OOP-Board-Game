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

int main(void) {
    Controller control;
    control.lancerPartie();

    while (1) {
        // tour pour chacun des joueurs
        std::cout<<endl<<endl<<endl<<endl;
        std::cout<<endl<<endl<<endl<<endl;
        std::cout<<"Tour numero"<<control.getPartie().getTour()+1<<endl;

            for (unsigned int i = 0; i < 2; i++) {
            std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------\n";
            std::cout<<"C'est a "<<control.getJoueurCourant().getPseudo()<<" de jouer : "<<endl;
            control.getJoueurCourant().afficherJoueur();
            std::cout<<endl;

            unsigned int etat_tour = 0;
            while (etat_tour != 4) {

                // actions optionelles
                switch (etat_tour) {
                case 0: {
                    unsigned int etat_action = 0;
                    while (etat_action != 4) {
                        switch (etat_action)
                        {
                        case 0:{
                            //appel du menu de choix des actions
                            etat_action = control.choixActionsOptionelles();
                            std::cout << endl;
                            break;}

                        case 1:{
                            try
                            {
                                //utilisation d'un privilege
                                control.verifPrivileges();
                                control.verifPlateauvide();
                                control.utiliserPrivilege(control.getPartie().getEspaceJeux().getPlateau());
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        }
                        case 2:{
                            try
                            {
                                //replissage du plateau
                                control.remplirPlateau(control.getPartie().getEspaceJeux().getPlateau(), control.getPartie().getEspaceJeux().getSac(), control.getJoueurAdverse());
                                etat_action = 0;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        }
                        case 3:{

                            etat_tour = 1;
                            etat_action = 4;
                            break;
                        }

                        case 9:{

                            return 0;

                        }

                        default:{
                            break;}
                        }

                    }
                    break;}

                    //actions obligatoires :
                case 1:{
                    unsigned int etat_action = 0;

                    while (etat_action != 4) {

                        switch (etat_action)
                        {
                        case 0:
                            //menu de choix des actions obligatoires
                            etat_action = control.choixActionsObligatoires();
                            break;
                            //
                        case 1:
                            try
                            {
                                //recuperation de jetons
                                cout << control.getPartie().getEspaceJeux().getPlateau()<<endl;
                                control.recupererJetons(control.getPartie().getEspaceJeux().getPlateau());
                                etat_action = 4;
                                cout << "\nNouveau plateau : \n"<<control.getPartie().getEspaceJeux().getPlateau()<<endl;
                                cout<< "Etat du joueur apres recuperation :\n";
                                control.getJoueurCourant().afficherJoueur();
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        case 2:
                            try
                            {
                                control.acheterCarteJoaillerie(control.getPartie().getEspaceJeux());
                                etat_action = 4;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;
                        case 3:
                            try
                            {
                                control.orReserverCarte(control.getPartie().getEspaceJeux().getPyramide(), control.getPartie().getEspaceJeux().getPlateau());
                                etat_action = 4;
                            }
                            catch(SplendorException& e) { std::cerr << "\033[1;31m" << e.getInfo() << "\033[0m" << endl << endl;; etat_action = 0; }
                            break;

                        case 9:{
                            std::cout<<"Vous avez decider de quitter la partie\n";
                            return 0;

                        }
                        default:
                            break;
                        }
                        etat_tour = 2;

                    }
                    break;
                }


                case 2:{
                    //verification des conditions de victoires...

                    //si le joueur a assez de pts de prestige, il est obliges d'acheter une carte
                    if (control.getJoueurCourant().getptsPrestige() >= 3 or control.getJoueurCourant().getptsPrestige() >= 6) {
                        control.acheterCarteNoble(control.getPartie().getEspaceJeux().getPyramide());
                    }

                    // rajoute verification >10 jetons

                    //verif si un joueur a gagner
                    if (control.getJoueurCourant().getptsPrestige() >= 15) {
                        std::cout << "Joueur " << control.getJoueurCourant().getPseudo() << " a gagne la partie" << std::endl;
                                etat_tour = 3;
                        break;
                    }

                    //simulation de victoire
                    /*
                    if (control.getJoueurCourant().getNbJetons() >= 2) {
                        std::cout << "Joueur " << control.getJoueurCourant().getPseudo() << " a gagne la partie" << std::endl;
                                etat_tour = 3;
                        break;
                    }
                    */

                    //fin du tour du joueur, on passe au joueur suivant
                    control.changerJoueurCourant();
                    //on sort du case
                    etat_tour = 4;
                    break;
                }

                case 3:{
                    std::cout << "Fin de la partie !\nMerci d'avoir joue a Splendor Duel !\n";
                    //arret de l'application
                    return 0;
                    break;
                }


                case 9 : {
                    std::cout<<"Vous avez decider de quitter la partie\n";
                    return 0;
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
    //fin d'une partie
    return 0;
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

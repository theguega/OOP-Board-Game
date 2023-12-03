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

    while (control.getPartie().getJoueur1()->estGagnant() == false && control.getPartie().getJoueur2()->estGagnant() == false) {
        // tour pour chacun des joueurs
        std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------";
        std::cout<<endl<<endl<<endl<<endl;
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
                            control.utiliserPrivilege(control.getPartie().getEspaceJeux().getPlateau());
                        }
                        catch(SplendorException& e) { std::cout << e.getInfo() << '\n'; etat_action = 0; }
                        break;
                        }
                    case 2:{
                        try
                        {
                            //replissage du plateau
                            control.remplirPlateau(control.getPartie().getEspaceJeux().getPlateau(), control.getPartie().getEspaceJeux().getSac(), control.getJoueurAdverse());
                            etat_action = 0;
                        }
                        catch(SplendorException& e) { std::cout << e.getInfo() << '\n'; etat_action = 0; }
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
                    case 1:
                        try
                        {
                            cout << control.getPartie().getEspaceJeux().getPlateau();
                            control.recupererJetons(control.getPartie().getEspaceJeux().getPlateau());
                            etat_action = 4;
                            cout << control.getPartie().getEspaceJeux().getPlateau();
                            control.getJoueurCourant().afficherJoueur();
                        }
                        catch(SplendorException& e) { std::cout << e.getInfo() << '\n'; etat_action = 0; }
                        break;
                    case 2:
                        try
                        {
                            control.acheterCarteJoaillerie(control.getPartie().getEspaceJeux());
                            etat_action = 4;
                        }
                        catch(SplendorException& e) { std::cout << e.getInfo() << '\n'; etat_action = 0; }
                        break;
                    case 3:
                        try
                        {
                            control.orReserverCarte(control.getPartie().getEspaceJeux().getPyramide(), control.getPartie().getEspaceJeux().getPlateau());
                            etat_action = 4;
                        }
                        catch(SplendorException& e) { std::cout << e.getInfo() << '\n'; etat_action = 0; }
                        break;
                    default:
                        break;
                    }
                    etat_tour = 2;
                }
                break;
            }
            case 2:{
                std::cout << "verification fin de partie" << std::endl << std::endl;

                if (control.getJoueurCourant().getptsPrestige() >= 3 or control.getJoueurCourant().getptsPrestige() >= 6) {
                    control.acheterCarteNoble(control.getPartie().getEspaceJeux().getPyramide());
                }

                // rajoute verification >10 jetons

                if (control.getJoueurCourant().getptsPrestige() >= 15) {
                    std::cout << "Joueur " << control.getJoueurCourant().getPseudo() << " a gagné la partie" << std::endl;
                    etat_tour = 3;
                    break;
                }
                etat_tour = 0;
                control.changerJoueurCourant();
                break;
            }
            case 3:{
                std::cout << "Fin de partie";
                etat_tour = 4;
                break;
            }
            case 9:{
                return 0;
            }

            default:{
                break;
            }
        }
    }
    return 0;
}
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

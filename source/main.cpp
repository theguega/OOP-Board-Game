#include "controller.hpp"
#include <filesystem>

//Mettez ici le chemin absolue vers le projet
//Theo
//std::filesystem::path projectPath = string("/Users/theoguegan/Documents/UTC/GI01/LO21/Projet_LO21");
//Samuel B
//std::filesystem::path projectPath = string("\\Users\\Beziat\\source\\repos\\Projet_LO21");
//Robert
std::filesystem::path projectPath = string("/Users/robertantaluca/Desktop/Projet_LO21");
//Samuel M
//std::filesystem::path projectPath = string("C:/Users/samma/Documents/Programmation/LO21/Projet_LO21");
//Maxime


int main(int argc, const char * argv[]) {
    int i = 0;
    Controller control;
    //control.getJoueurCourant().afficherJoueur();
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
                                    std::cout << "Actions optionnelles : " << endl;
                                    std::cout << "1. Utiliser un privilège" << endl;
                                    std:: cout << "2. Remplir le plateau" << endl;
                                    std::cout << "3. Ne rien faire" << endl;
                                    std::cout << "Votre choix (1/2/3): ";
                                    cin >> etat_action;
                                    std::cout << endl;
                                    break;

                                case 1:
                                try
                                {
                                    control.utiliserPrivilege(control.getPartie().getEspaceJeux().getPlateau());
                                    }
                                    catch(const std::exception& e)
                                    {
                                        etat_action = 0;
                                }
                                
                                    
                                    break;

                                
                                default:
                                    break;
                                }

                        }
                        break;
                                
                    default:
                        break;
                }



                }
                
        
            }

            control.setJoueurCourant(i); // dommage que changerJoueurCourant() ai disparu, je trouve cette solution moins élégante
        }


    /*
        // simulation victoire d'un joueur
        if (i == 5)
            control.getJoueurCourant().updatePtsPrestige(16);
        control.getJoueurCourant().afficherJoueur();
        i++;
        control.tour_suivant();
    */
    if (control.getPartie().getJoueur1()->estGagnant())
        cout << control.getPartie().getJoueur1()->getPseudo() << " est gagnant;"<<std::endl;
    else if (control.getPartie().getJoueur2()->estGagnant())
        cout << control.getPartie().getJoueur2()->getPseudo() << " est gagnant;"<<std::endl;

    //control.getPartie().getJoueur1()->afficherJoueur();
    //control.getPartie().getJoueur2()->afficherJoueur();
    cout << control.getPartie().getEspaceJeux().getPlateau();
    //control.getPartie().getEspaceJeux().getPyramide().afficherPyramide();

    //control.enregisterScore();
    //control.sauvegardePartie();
    
    return 0;
}

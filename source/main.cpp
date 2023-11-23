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
        // simulation victoire d'un joueur
        if (i == 5)
            control.getJoueurCourant().updatePtsPrestige(16);
        control.getJoueurCourant().afficherJoueur();
        i++;
        control.tour_suivant();
    }

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

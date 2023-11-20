#include "controller.hpp"
#include <filesystem>

//Mettez ici le chemin absolue vers le projet
//Theo
//std::filesystem::path projectPath = string("/Users/theoguegan/Documents/UTC/GI01/LO21/Projet_LO21");
//Samuel B
std::filesystem::path projectPath = string("\\Users\\Beziat\\source\\repos\\Projet_LO21");
//Robert
//std::filesystem::path projectPath = string("/Users/robertantaluca/Desktop/Projet_LO21");
//Samuel M
//Maxime


int main(int argc, const char * argv[]) {
    Controller control;
    control.getPartie().getJoueur1()->afficherJoueur();
    control.getPartie().getJoueur2()->afficherJoueur();
    cout << control.getPartie().getEspaceJeux().getPlateau();
    control.getPartie().getEspaceJeux().getPyramide().afficherPyramide();
    return 0;
}

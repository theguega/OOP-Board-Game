#include <QWidget>
#include <QPushButton>
#include <interface/code/vueJeton.h>

vueJeton::vueJeton(QWidget* parent, int rad) : QPushButton(parent){

    /*switch(couleur){
        case bleuclair:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: lightblue; }");
            break;

        case jaune:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: yellow; }");
            break;

        case vert:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: green; }");
            break;

        case rouge:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: red; }");
            break;

        case noir:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: black }");
            break;

        case argent:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: gray; }");
            break;

        case perle:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: pink; }");
            break;
    }*/

    this->rad = rad;

    //setText("Test"); //Def le texte (inute pour la suite)
    setFixedSize(rad*2, rad*2); //Fixe la taille et qui permet d'avoir une taille de 2x le rad pour avoir pile la taille du bouton
    setStyleSheet(QString("QPushButton { "
                         "border-radius: %1px; " // Rayon du bord pour rendre le bouton circulaire
                         "background-color: pink; " // Couleur de fond
                         "color: white; " // Couleur du texte
                          "}"
                          ).arg(rad));
    /*"QPushButton:pressed { " // Style lorsqu'il est enfonce
    "background-color: %3; " // Couleur sombre pour effet d'enfoncement
    "}"  */
    //Def le style du bouton (plus tard switch selon la couleur du jeton)

    afficherCroix = false; //afficherCroix est un booleen pour savoir si on montre la croix de selection (false d'origine)
}

void vueJeton::apparaitre(){ //Fait apparaitre le jeton (utile quand on voudra les remettre sur le plateau)
    show();
}

void vueJeton::disparaitre(){ //Fait dispparaitre le jeton (utile quand on voudra les enelevr du plateau)
    hide();
}

bool vueJeton::getEstVisible(){ //Je sais plus a quoi ça sert (surement inutile)
    return estVisible;
}

void vueJeton::changeAfficherCroix(){ //Change l'ffichage de la croix par son inverse
    afficherCroix = !afficherCroix;
}

void vueJeton::enleverCroix(){ //Enleve la croix du jeton (utilse quand on voudra faire une deselection depuis le plateau)
    afficherCroix = false;
}

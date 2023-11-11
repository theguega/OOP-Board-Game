#include <QWidget>
#include <jetons.hpp>
#include <vueJeton.h>
#include <array>
#include <vuePlateau.h>

vuePlateau::vuePlateau(Plateau& plateau) : plateau(plateau){
    sac = plateau.getPlateau();
    for(int i = 0; i < 25; i++){
        //Créer un getteur pour les Jetons
        listeJetons[i] = sac.getJeton(i);
    }
}

vueJeton* vuePlateau::recupererBouton(Jetons* jeton){
    for(int i = 0; i < 25; i++){
        if(listeJetons[i]->jeton == jeton){
            return listeJetons[i]
        }
    }
    return nullptr
}

void vuePlateau::remplirPlateau(){
    plateau.remplirPlateau();
    vueJeton* temp;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 25; j++){
            //faire un getteur pour le plateau
            temp = recupererBouton(plateau.getJeton(i, j));
            temp->apparaitre(position());
        }
    }
}

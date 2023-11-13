
#include "espacejeux.hpp"

Pyramide::Pyramide( Pioche *piocheNv1, Pioche *piocheNv2,Pioche *piocheNv3,Pioche *piocheNoble): pNv1(*piocheNv1), pNv2(*piocheNv2), pNv3(*piocheNv3), pNoble(*piocheNoble) {
        // redimesionnement des tableaux
        array_cartes[0].resize(3); // Tableau de 3 Cartes niv3
        array_cartes[1].resize(4); // Tableau de 4 Cartes niv2
        array_cartes[2].resize(5); // Tableau de 5 Cartes niv1
        array_cartes[3].resize(4); // Tableau de 4 Cartes (les nobles)

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < array_cartes[i].size(); j++) {
                array_cartes[i][j] =  nullptr;
                
            }
        }
        this->remplirPyramide();

};

Pyramide::~Pyramide() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < array_cartes[i].size(); j++) {
            if (array_cartes[i][j] != nullptr) {
                delete array_cartes[i][j];
            }
        }
    }
};

 // Obtenir une référence temporaire


void Pyramide::remplirPyramide() {
    const Carte* ma_carte = nullptr;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < array_cartes[i].size(); j++) {
            if (array_cartes[i][j] == nullptr) {
                switch (i) {
                    case 0:
                        if (not(pNv3.estVide())) {
                            ma_carte = &pNv3.piocher(); // piocher/tirer des cartes de niveau 3
                            break;
                        }
                       
                    case 1:
                        if (not(pNv2.estVide())) {
                            ma_carte = &pNv2.piocher(); // piocher des cartes de niveau 2
                            break;
                        }
                    case 2:
                        if (not(pNv1.estVide())) {
                            ma_carte = &pNv1.piocher(); // piocher des cartes de niveau 1
                            break;
                        }
                    case 3:
                        if (not(pNoble.estVide())) {
                            ma_carte = &pNoble.piocher(); // piocher des cartes nobles
                            break;
                        }
                    default:
                        break;
                }
                
                array_cartes[i][j] = ma_carte;
            }
        }
    }
}

void Pyramide::remplircasePyramide(int i , int j) {
    const Carte* ma_carte = nullptr;
    if (array_cartes[i][j] == nullptr) {
        switch (i) {
            case 0:
                if (not(pNv3.estVide())) {
                    ma_carte = &pNv3.piocher(); // piocher/tirer des cartes de niveau 3
                    break;
                }
               
            case 1:
                if (not(pNv2.estVide())) {
                    ma_carte = &pNv2.piocher(); // piocher des cartes de niveau 2
                    break;
                }
            case 2:
                if (not(pNv1.estVide())) {
                    ma_carte = &pNv1.piocher(); // piocher des cartes de niveau 1
                    break;
                }
            case 3:
                if (not(pNoble.estVide())) {
                    ma_carte = &pNoble.piocher(); // piocher des cartes nobles
                    break;
                }
            default:
                break;
        }
        
        array_cartes[i][j] = ma_carte;
    }
}

bool Pyramide::estVide() const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < array_cartes[i].size(); j++) {
            if (array_cartes[i][j] != nullptr) {
                return false;
            }
        }
    }
    return true;
}

const Carte& Pyramide::prendreCarte(int i, int j) {
    if (array_cartes[i][j] != nullptr) {
        const Carte& ma_carte = *array_cartes[i][j];
        array_cartes[i][j] = nullptr;
        this -> remplircasePyramide(i,j);
        return ma_carte; 
    }
}

const Carte& Pyramide::PiocherCarte(int niveau) {

    switch (niveau) {
                    case 0:
                        if (not(pNv3.estVide())) {
                             return pNv3.piocher(); ; // piocher/tirer des cartes de niveau 3
                            break;
                        }
                       
                    case 1:
                        if (not(pNv2.estVide())) {
                             return pNv2.piocher();  // piocher des cartes de niveau 2
                            break;
                        }
                    case 2:
                        if (not(pNv1.estVide())) {
                             return pNv1.piocher(); // piocher des cartes de niveau 1
                            break;
                        }
                    case 3:
                        if (not(pNoble.estVide())) {
                            return pNoble.piocher(); // piocher des cartes nobles
                            break;
                        }
                    default:
                        break;
                }
   
}
/*
void Pyramide::acheterCarte(int i, int j) {
    if (array_cartes[i][j] != nullptr) {
        //actions en focntion du fonctionnement de strategy
        array_cartes[i][j] = nullptr;
        this -> remplircasePyramide(i,j);
    }
}
*/
//getnbcartes
//achetercartes





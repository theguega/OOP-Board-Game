#include "espacejeux.hpp"

Pyramide::Pyramide( Pioche& pNv1, Pioche& pNv2,Pioche& pNv3,Pioche& pNoble) {
       
        // redimesionnement des tableaux
        array_cartes[0].resize(2); // Tableau de 2 Cartes niv3
        array_cartes[1].resize(3); // Tableau de 3 Cartes niv2
        array_cartes[2].resize(4); // Tableau de 4 Cartes niv1
        array_cartes[3].resize(4); // Tableau de 4 Cartes (les nobles)

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < array_cartes[i].size(); j++) {
                array_cartes[i][j] =  nullptr;
                this->remplirPyramide(pNv1,pNv2,pNv3,pNoble);
            }
        }

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


void Pyramide::remplirPyramide(Pioche &pNv1, Pioche &pNv2, Pioche &pNv3, Pioche &pNoble) {
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

void Pyramide::remplircasePyramide(int i, int j, Pioche &pNv1, Pioche &pNv2, Pioche &pNv3, Pioche &pNoble) {
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

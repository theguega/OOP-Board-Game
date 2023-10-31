#include "espacejeux.hpp"

Pyramide::Pyramide( Pioche &pNv1, Pioche &pNv2,Pioche &pNv3,Pioche &pNoble) {
       
        // redimesionnement des tableaux
        cartes[0].resize(2); // Tableau de 2 Cartes niv3
        cartes[1].resize(3); // Tableau de 3 Cartes niv2
        cartes[2].resize(4); // Tableau de 4 Cartes niv1
        cartes[3].resize(4); // Tableau de 4 Cartes (les rares)

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < cartes[i].size(); j++) {
                switch (i)
                {
                case 0:
                    cartes[i][j] = pNv1.piocher(); // piocher/tirer des carte de niveau 3
                    break;
                case 1:
                    cartes[i][j] = pNv2.piocher(); // piocher cartes de niveau 2
                    break;
                case 2:
                    cartes[i][j] = pNv3.piocher(); // Piocher des cartes niveau 1
                    break;
                case 3:
                    cartes[i][j] = pNoble.piocher(); // piocher cartes nobles
                    break;
                
                default:
                    break;
                }
                
            }
        }

};

Pyramide::~Pyramide() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < cartes[i].size(); j++) {
            if (cartes[i][j] != nullptr) {
                delete cartes[i][j];
            }
        }
    }
};

void Pyramide::remplirPyramide(Pioche &pNv1, Pioche &pNv2,Pioche &pNv3,Pioche &pNoble){

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < cartes[i].size(); j++) {
            if (cartes[i][j] == nullptr) {
                switch (i)
                    {
                    case 0:
                        cartes[i][j] = pNv1.piocher(); // piocher/tirer des carte de niveau 3
                        break;
                    case 1:
                        cartes[i][j] = pNv2.piocher(); // piocher cartes de niveau 2
                        break;
                    case 2:
                        cartes[i][j] = pNv3.piocher(); // Piocher des cartes niveau 1
                        break;
                    case 3:
                        cartes[i][j] = pNoble.piocher(); // piocher cartes nobles
                        break;
                    
                    default:
                        break;
                    }
                    
                }
        
        }
    }
} 



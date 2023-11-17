#include "espacejeux.hpp"

Pyramide::Pyramide( Pioche *piocheNv1, Pioche *piocheNv2,Pioche *piocheNv3,Pioche *piocheNoble): pNv1(*piocheNv1), pNv2(*piocheNv2), pNv3(*piocheNv3), pNoble(*piocheNoble) {
        // redimesionnement des tableaux
        array_cartes[0].resize(5); // Tableau de 5 Cartes niv1
        array_cartes[1].resize(4); // Tableau de 4 Cartes niv2
        array_cartes[2].resize(3); // Tableau de 3 Cartes niv3
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
            array_cartes[i][j] = nullptr;
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
                        if (not(pNv1.estVide())) {
                            ma_carte = &pNv1.piocher(); // piocher/tirer des cartes de niveau 3
                            break;
                        }
                       
                    case 1:
                        if (not(pNv2.estVide())) {
                            ma_carte = &pNv2.piocher(); // piocher des cartes de niveau 2
                            break;
                        }
                    case 2:
                        if (not(pNv3.estVide())) {
                            ma_carte = &pNv3.piocher(); // piocher des cartes de niveau 1
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

void Pyramide::remplircasePyramide(unsigned int i , unsigned int j) {
    const Carte* ma_carte = nullptr;
    if (array_cartes[i][j] == nullptr) {
        switch (i) {
            case 0:
                if (not(pNv1.estVide())) {
                    ma_carte = &pNv1.piocher(); // piocher/tirer des cartes de niveau 3
                    break;
                }
               
            case 1:
                if (not(pNv2.estVide())) {
                    ma_carte = &pNv2.piocher(); // piocher des cartes de niveau 2
                    break;
                }
            case 2:
                if (not(pNv3.estVide())) {
                    ma_carte = &pNv3.piocher(); // piocher des cartes de niveau 1
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

//2 fois la meme fonction à ameliorer

const Carte& Pyramide::reserverCarte(int niveau, int numero) {
    niveau--;  numero++; // pour que l'utilisateur rentre les coordonnées de 1 à 5
    if (array_cartes[niveau][numero] != nullptr) {
        const Carte& ma_carte = *array_cartes[niveau][numero];
        array_cartes[niveau][numero] = nullptr;
        this -> remplircasePyramide(niveau,numero);
        return ma_carte; 
    }
    else{
        throw "erreur";
    }
}


const Carte& Pyramide::acheterCarte(unsigned int niveau, unsigned int numero) {
    niveau--;  numero++; // pour que l'utilisateur rentre les coordonnées de 1 à 5
    if (array_cartes[niveau][numero] != nullptr) {
        const Carte& ma_carte = *array_cartes[niveau][numero];
        array_cartes[niveau][numero] = nullptr;
        this -> remplircasePyramide(niveau,numero);
        return ma_carte; 
    }
    else{
        throw "erreur";
    }
    
}

const Carte& Pyramide::ReserverCartePioche(unsigned int niveau) {

    switch (niveau) {
                    case 0:
                        if (not(pNv1.estVide())) {
                             return pNv1.piocher(); ; // piocher/tirer des cartes de niveau 3
                            break;
                        }
                        else{
                            throw "erreur";
                        }
                       
                    case 1:
                        if (not(pNv2.estVide())) {
                             return pNv2.piocher();  // piocher des cartes de niveau 2
                            break;
                        }
                        else{
                            throw "erreur";
                        }
                    case 2:
                        if (not(pNv3.estVide())) {
                             return pNv3.piocher(); // piocher des cartes de niveau 1
                            break;
                        }
                        else{
                            throw "erreur";
                        }
                    case 3:
                        if (not(pNoble.estVide())) {
                            return pNoble.piocher(); // piocher des cartes nobles
                            break;
                        }
                        else{
                            throw "erreur";
                        }
                    default:
                        throw "erreur";
                        break;
                }
   
}


void Pyramide::afficherPyramide() const {
    std::cout << "Pyramide : " << std::endl;
    for (int i = 0; i < 3; i++) {

         switch (i) {
                    case 0:
                        std::cout << "Niveau 1 " << std::endl;
                    case 1:
                        std::cout << "Niveau 2 " << std::endl;
                    case 2:
                        std::cout << "Niveau 3 " << std::endl;
                    default:
                        break;
                }
        for (int j = 0; j < array_cartes[i].size(); j++) {
            if (array_cartes[i][j] != nullptr) {
                std::cout << "Carte " << i << " " << j << " : " << *array_cartes[i][j] << std::endl;
            }
        }
    }

}

int Pyramide::getNbCartesNiv(unsigned int niveau) const {
    niveau--;// pour que l'utilisateur rentre les coordonnées de 1 à 3
    int nbCartes = 0;
    for (int i = 0; i < array_cartes[niveau].size(); i++) {
        if (array_cartes[niveau][i] != nullptr) {
            nbCartes++;
        }
    }
    return nbCartes;

}

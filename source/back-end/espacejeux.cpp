#include "espacejeux.hpp"

Pyramide::Pyramide(Pioche * piocheNv1, Pioche * piocheNv2, Pioche * piocheNv3, Pioche * piocheNoble): pNv1( * piocheNv1), pNv2( * piocheNv2), pNv3( * piocheNv3), pNoble( * piocheNoble) {
    // redimesionnement des tableaux
    array_cartes[0].resize(5); // Tableau de 5 Cartes niv1
    array_cartes[1].resize(4); // Tableau de 4 Cartes niv2
    array_cartes[2].resize(3); // Tableau de 3 Cartes niv3
    array_cartes[3].resize(4); // Tableau de 4 Cartes (les nobles)

    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < array_cartes[i].size(); j++) {
            array_cartes[i][j] = nullptr;
        }
    }
    //this->remplirPyramide();

};

Pyramide::~Pyramide() {
    for (int i = 0; i < 4; i++) {
        for (size_t j = 0; j < array_cartes[i].size(); j++) {
            array_cartes[i][j] = nullptr;
        }
    }
};

// Obtenir une reference temporaire

void Pyramide::remplirPyramide() {
    const Carte * ma_carte = nullptr;

    for (size_t i = 0; i < array_cartes.size(); i++) {
        for (size_t j = 0; j < array_cartes[i].size(); j++) {
            if (array_cartes[i][j] == nullptr) {
                switch (i) {
                case 0:
                    if (not(pNv1.estVide())) {
                        ma_carte = & pNv1.piocher(); // piocher/tirer des cartes de niveau 3
                        break;
                    }

                case 1:
                    if (not(pNv2.estVide())) {
                        ma_carte = & pNv2.piocher(); // piocher des cartes de niveau 2
                        break;
                    }
                case 2:
                    if (not(pNv3.estVide())) {
                        ma_carte = & pNv3.piocher(); // piocher des cartes de niveau 1
                        break;
                    }
                case 3:
                    if (not(pNoble.estVide())) {
                        ma_carte = & pNoble.piocher(); // piocher des cartes nobles
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

void Pyramide::remplircasePyramide(unsigned int i, unsigned int j) {
    const Carte * ma_carte = nullptr;
    if (array_cartes[i][j] == nullptr) {
        switch (i) {
        case 0:
            if (not(pNv1.estVide())) {
                ma_carte = & pNv1.piocher(); // piocher/tirer des cartes de niveau 3
                break;
            }

        case 1:
            if (not(pNv2.estVide())) {
                ma_carte = & pNv2.piocher(); // piocher des cartes de niveau 2
                break;
            }
        case 2:
            if (not(pNv3.estVide())) {
                ma_carte = & pNv3.piocher(); // piocher des cartes de niveau 1
                break;
            }
        case 3:
            if (not(pNoble.estVide())) {
                ma_carte = & pNoble.piocher(); // piocher des cartes nobles
                break;
            }
        default:
            break;
        }

        array_cartes[i][j] = ma_carte;
    }
}

bool Pyramide::estVide() const {
    for (size_t i = 0; i < array_cartes.size(); i++) {
        for (size_t j = 0; j < array_cartes[i].size(); j++) {
            if (array_cartes[i][j] != nullptr) {
                return false;
            }
        }
    }
    return true;
}

//2 fois la meme fonction a ameliorer

const Carte & Pyramide::reserverCarte(int niveau, int numero) {
    if (array_cartes[niveau][numero] != nullptr) {
        const Carte & ma_carte = * array_cartes[niveau][numero];
        array_cartes[niveau][numero] = nullptr;
        this -> remplircasePyramide(niveau, numero);
        return ma_carte;
    } else {
        throw SplendorException("Pas de carte a cette emplacement");
    }
}

const Carte & Pyramide::acheterCarte(unsigned int niveau, unsigned int numero) {
    if (array_cartes[niveau][numero] != nullptr) {
        const Carte & ma_carte = * array_cartes[niveau][numero];
        array_cartes[niveau][numero] = nullptr;
        this -> remplircasePyramide(niveau, numero);
        return ma_carte;
    } else {
        throw SplendorException("Pas de carte a cette emplacement");
    }

}

const Carte & Pyramide::ReserverCartePioche(unsigned int niveau) {

    switch (niveau) {
    case 1:
        if (not(pNv1.estVide())) {
            return pNv1.piocher(); // piocher/tirer des cartes de niveau 3
            break;
        } else {
            throw SplendorException("Pioche vide");
        }

    case 2:
        if (!pNv2.estVide()) {
            return pNv2.piocher(); // piocher des cartes de niveau 2
            break;
        } else {
            throw SplendorException("Pioche vide");
        }
    case 3:
        if (!pNv3.estVide()) {
            return pNv3.piocher(); // piocher des cartes de niveau 1
            break;
        } else {
            throw SplendorException("Pioche vide");
        }
    case 4:
        throw SplendorException("Vous ne pouvez pas reserver de carte Noble");
    default:
        throw SplendorException("Indice de pioche invalide");
        break;
    }
}

void Pyramide::afficherPyramide() const {
    std::cout << "Pyramide : " << std::endl;
    for (size_t i = 0; i < array_cartes.size() - 1; i++) {
        std::cout << "Niveau " << i + 1 << " : " << std::endl;

        for (size_t j = 0; j < array_cartes[i].size(); j++) {
            if (array_cartes[i][j] != nullptr) {
                std::cout << "Carte " << i+1 << " " << j+1 << " : " << std::endl << * array_cartes[i][j] <<  "\n\n\n";
            }
        }
        std::cout<<"\n\n\n\n\n\n\n\n";
    }
}


void Pyramide::afficherNobles() const {
    std::cout << "Cartes nobles : " << std::endl;
        for (size_t j = 0; j < array_cartes[4].size(); j++) {
            if (array_cartes[4][j] != nullptr) {
                std::cout << "Carte " << j+1 << " : " << std::endl << * array_cartes[4][j] <<  "\n\n\n";
            }
        }
        std::cout<<"\n\n\n\n\n\n\n\n";
}

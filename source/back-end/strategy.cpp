#include "strategy.hpp"
#include <random>



std::vector<const Jeton*> StrategyHumain::recupJetonStrat(Plateau& plateau){
    std::cout << "Combien de jetons souhaitez-vous recuperer ? (1 a 3) " << std::endl;
    unsigned int nbJetonsRecup;
    std::cin >> nbJetonsRecup;

    while (nbJetonsRecup > 3 || nbJetonsRecup < 1){
        std::cout <<"Le nombre de jetons est impossible\nCombien de jetons souhaitez-vous recuperer ? (1 a 3) " << std::endl;
        std::cin >> nbJetonsRecup;
    }

    std::cout << "Merci de selectionner des jetons adjacents en ligne, en colonne ou en diagonale." << std::endl;

    std::vector<std::pair<unsigned int, unsigned int>> vecteurCoordonnees;

    // Récup des coordonnées des jetons
    for (unsigned int k = 0; k < nbJetonsRecup; k++){

        // Ajout des coordonnees
        vecteurCoordonnees.emplace_back(choisirJeton(plateau));
        // Ajout du jeton
        //jetonsRecup.push_back(&jeton);
    }

    // Verifier que les jetons sont adjacents
    if (nbJetonsRecup > 1) {
        bool result1 = true;
        bool result2 = true;
        bool result3 = false; // Diago 1
        bool result4 = false; // Diago 2

        // Verif que les jetons sont adjacents en ligne
        for (int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            if (vecteurCoordonnees[i].first != vecteurCoordonnees[i + 1].first) {
                result1 = false;
            }
        }
        // Verif que les jetons sont adjacents en colonne
        for (int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            if (vecteurCoordonnees[i].second != vecteurCoordonnees[i + 1].second) {
                result2 = false;
            }
        }
        // Verif que les jetons sont adjacents en diagonale

        // Fonction de comparaison pour trier en fonction du premier élément de la paire
        auto comparaison = [](const auto& a, const auto& b) {
            return a.first < b.first;
        };
        std::sort(vecteurCoordonnees.begin(), vecteurCoordonnees.end(), comparaison);

        for (int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            // première diagonale
            if ((vecteurCoordonnees[i].first+1 == vecteurCoordonnees[i + 1].first) && (vecteurCoordonnees[i].second-1 == vecteurCoordonnees[i + 1].second)) {
                result3 = true;
            }
        }

        for (int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            // seconde diagonale
            if ((vecteurCoordonnees[i].first+1 == vecteurCoordonnees[i + 1].first) && (vecteurCoordonnees[i].second+1 == vecteurCoordonnees[i + 1].second)) {
                result4 = true;
            }
        }

        if (!result1 && !result2 && !result3 && !result4) {
            throw StrategyException("Les jetons ne sont pas adjacents");
        }

    }

    // Récup des jetons
    std::vector<const Jeton*> jetonsRecup;
    for (unsigned int k = 0; k < nbJetonsRecup; k++){
        jetonsRecup.push_back(&plateau.recupererJeton(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second));
    }

    return jetonsRecup;
}

std::vector<const Jeton*> StrategyIA::recupJetonStrat(Plateau& plateau){
    std::cout << "Combien de jetons souhaitez-vous recuperer ? (1 a 3) " << std::endl;
    // Initialiser le générateur de nombres aléatoires avec la graine actuelle du système
    std::random_device rd;
    std::mt19937 gen(rd());
    // Créer une distribution uniforme pour les entiers entre 1 et 3 inclus
    std::uniform_int_distribution<int> distribution(1, 3);
    // Générer un nombre aléatoire
    int nbJetonsRecup = distribution(gen);
    std::cout<<"On recupere "<<nbJetonsRecup<<" jetons"<<std::endl;

    std::cout << "Merci de selectionner des jetons adjacents en ligne, en colonne ou en diagonale." << std::endl;
    // Méthode = 1 correspond à recup en colonne
    // Méthode = 2 correspond à recup en ligne
    // Méthode = 3 correspond à recup en diagonale
    int methode = distribution(gen);

    std::vector<std::pair<unsigned int, unsigned int>> vecteurCoordonnees;
    vecteurCoordonnees.emplace_back(choisirJeton(plateau));
    std::vector<std::pair<int, int>> coordonneesAdjacentes;


    if (methode == 1){

        while (coordonneesAdjacentes.size() < nbJetonsRecup) {
            // Choisir aléatoirement une ligne dans la colonne choisie
            std::uniform_int_distribution<int> distributionLigne(0, plateau.getLargeurMatrice() - 1);
            std::pair<int, int> coord = choisirJeton(plateau);

            // Vérifier si la coordonnée est valide
            if (coord.first + 2 < plateau.getLargeurMatrice()) {
                coordonneesAdjacentes.emplace_back(coord.first, coord.second);
                coordonneesAdjacentes.emplace_back(coord.first + 1, coord.second);
                coordonneesAdjacentes.emplace_back(coord.first + 2, coord.second);
            }
        }
    }
    if (methode == 2){

        while (coordonneesAdjacentes.size() < nbJetonsRecup) {
            // Choisir aléatoirement une colonne dans la colonne choisie
            std::uniform_int_distribution<int> distributionLigne(0, plateau.getLargeurMatrice() - 1);
            std::pair<int, int> coord = choisirJeton(plateau);

            // Vérifier si la coordonnée est valide
            if (coord.second + 2 < plateau.getLargeurMatrice()) {
                coordonneesAdjacentes.emplace_back(coord.first, coord.second);
                coordonneesAdjacentes.emplace_back(coord.first, coord.second+1);
                coordonneesAdjacentes.emplace_back(coord.first, coord.second+2);
            }
        }
    }
    if (methode == 3){

        while (coordonneesAdjacentes.size() < nbJetonsRecup) {
            // Choisir aléatoirement une colonne dans la colonne choisie
            std::uniform_int_distribution<int> distributionLigne(0, plateau.getLargeurMatrice() - 1);
            std::pair<int, int> coord = choisirJeton(plateau);

            // Vérifier si la coordonnée est valide
            if (coord.second + 2 < plateau.getLargeurMatrice() && coord.first + 2 < plateau.getLargeurMatrice()) {
                coordonneesAdjacentes.emplace_back(coord.first, coord.second);
                coordonneesAdjacentes.emplace_back(coord.first+1, coord.second+1);
                coordonneesAdjacentes.emplace_back(coord.first+2, coord.second+2);
            }
        }
    }


    // Récup des jetons
    std::vector<const Jeton*> jetonsRecup;
    for (unsigned int k = 0; k < nbJetonsRecup; k++){
        jetonsRecup.push_back(&plateau.recupererJeton(coordonneesAdjacentes[k].first, coordonneesAdjacentes[k].second));
    }

    return jetonsRecup;

}

std::pair<unsigned int, unsigned int> StrategyHumain::choisirJeton(Plateau& plateau){
    unsigned int i, j;
    std::cout << "Entrez la valeur de i : ";
    std::cin >> i;
    std::cout << "Entrez la valeur de j : ";
    std::cin >> j;

    // Retourner la paire d'entiers
    return std::make_pair(i, j);
}

std::pair<unsigned int, unsigned int> StrategyIA::choisirJeton(Plateau& plateau){
    // Obtenez les dimensions du plateau
    size_t plateauRows = plateau.getLargeurMatrice();
    size_t plateauCols = plateau.getLargeurMatrice();

    // distribution uniforme pour générer des indices aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distributionRow(0, plateauRows - 1);
    std::uniform_int_distribution<int> distributionCol(0, plateauCols - 1);

    // Génére des valeurs aléatoires pour i et j
    int i = distributionRow(gen);
    int j = distributionCol(gen);

    // Retournez le jeton correspondant aux indices aléatoires
    return std::make_pair(i, j);
}

unsigned int StrategyHumain::choixNiveau() {
    std::cout<<"Voulez-vous réserver une carte de la pyramide ou de la pioche de niveau i ? (0, 1, 2, 3)" << std::endl;
    unsigned int choix;
    std::cin >> choix;
    return choix;
}

unsigned int StrategyIA::choixNiveau() {
    std::cout<<"Voulez-vous réserver une carte de la pyramide ou de la pioche de niveau i ? (0, 1, 2, 3)" << std::endl;
    // Initialiser le générateur de nombres aléatoires avec la graine actuelle du système
    std::random_device rd;
    std::mt19937 gen(rd());
    // Créer une distribution uniforme pour les entiers entre 0 et 3 inclus
    std::uniform_int_distribution<int> distribution(0, 3);
    // Générer un nombre aléatoire
    int choix = distribution(gen);
    std::cout<<"On va en "<<choix<<".\n"<<std::endl;
    return choix;
}

unsigned int StrategyHumain::choixAchat(){
    std::cout << "Tapez 1 pour acheter une carte Réservée.\nTapez 2 pour acheter une carte du plateau." << std::endl;
    unsigned int choix;
    std::cin >> choix;
    while ((choix != 1) && (choix !=2)){
        std::cout<<"Le choix est incorrect\n"<<std::endl;
        std::cout << "Tapez 1 pour acheter une carte Réservée.\nTapez 2 pour acheter une carte du plateau." << std::endl;
        std::cin >> choix;
    }
    return choix;
}

unsigned int StrategyIA::choixAchat(){
    // Initialiser le générateur de nombres aléatoires avec la graine actuelle du système
    std::random_device rd;
    std::mt19937 gen(rd());
    // Créer une distribution uniforme pour les entiers entre 1 et 2 inclus
    std::uniform_int_distribution<int> distribution(1, 2);
    // Générer un nombre aléatoire
    int choix = distribution(gen);
    if (choix == 1) {
        std::cout << "On va acheter une carte réservée." << std::endl;
    }
    else {
        std::cout << "On va acheter une carte du plateau." << std::endl;
    }
    return choix;
}

std::pair<unsigned int, unsigned int> StrategyIA::reservationCarte(Pyramide& pyramide) {
    // Initialiser le générateur de nombres aléatoires avec la graine actuelle du système
    std::random_device rd;
    std::mt19937 gen(rd());
    // Créer une distribution uniforme pour les entiers entre 0 et 3 inclus
    std::uniform_int_distribution<int> distribution(0, 2);
    // Générer un nombre aléatoire
    int niveau = distribution(gen);
    std::cout << "Voici les cartes de la pyramide : " << std::endl;
    pyramide.afficherPyramide();

    std::cout << "Niveau: "<< niveau << std::endl;

    std::uniform_int_distribution<int> distributionNiveau(1, pyramide.getNbCartesNiv(niveau));
    int numCarte = distributionNiveau(gen);
    std::cout << "Niveau: "<< niveau << std::endl;
    std::cout << "Numéro de carte: "<< numCarte << std::endl;


    return std::make_pair(niveau, numCarte);
}

std::pair<unsigned int, unsigned int> StrategyHumain::reservationCarte(Pyramide& pyramide) {
    std::cout << "Voici les cartes de la pyramide : " << std::endl;
    pyramide.afficherPyramide();
    std::cout << "Tapez le niveau de la carte que vous voulez réserver : " << std::endl;
    unsigned int niveau;
    std::cin >> niveau;
    std::cout << "Tapez le numero de la carte que vous voulez réserver : " << std::endl;
    unsigned int numCarte;
    std::cin >> numCarte;
    // Vérifications
    while (numCarte > pyramide.getNbCartesNiv(niveau) || numCarte < 0 || niveau >= 3 || niveau < 0 ){
        std::cout<<"Le numéro de la carte ou son niveau est incorrect\n"<<std::endl;
        std::cout << "Tapez le niveau de la carte que vous voulez réserver : " << std::endl;
        std::cin >> niveau;
        std::cout << "Tapez le numero de la carte que vous voulez réserver : " << std::endl;
        std::cin >> numCarte;
    }

    return std::make_pair(niveau, numCarte);
}

std::pair<unsigned int, unsigned int> StrategyHumain::achatNoble(Pyramide& pyramide) {
    std::cout << "Tapez le numero de la carte noble que vous voulez acheter : " << std::endl;
    unsigned int numCarte;
    std::cin >> numCarte;
    // Vérifications
    while (numCarte > pyramide.getNbCartesNiv(4) || numCarte < 0){
        std::cout<<"Le numéro de la carte est incorrect\n"<<std::endl;
        std::cout << "Tapez le numero de la carte noble que vous voulez acheter : " << std::endl;
        std::cin >> numCarte;
    }

    return std::make_pair(4, numCarte);

}

std::pair<unsigned int, unsigned int> StrategyIA::achatNoble(Pyramide& pyramide) {
    std::cout << "Tapez le numero de la carte noble que vous voulez acheter : " << std::endl;
    // Initialiser le générateur de nombres aléatoires avec la graine actuelle du système
    std::random_device rd;
    std::mt19937 gen(rd());
    // Créer une distribution uniforme pour les entiers entre 0 et 3 inclus
    std::uniform_int_distribution<int> distribution(0, pyramide.getNbCartesNiv(4));
    // Générer un nombre aléatoire
    int numCarte = distribution(gen);
    std::cout<<"Numéro de carte : "<<numCarte<< std::endl;
    return std::make_pair(4, numCarte);

}

std::pair< Couleur, unsigned int> StrategyHumain::achatReserve(unsigned int nbCartesReservees){
    std::cout << "Voici les cartes réservées : " << std::endl;
    unsigned int i = 0;

    std::cout << "Tapez le numéro de la carte que vous voulez acheter : " << std::endl;
    unsigned int numCarte;
    std::cin >> numCarte;
    // Vérifications -> voir plus au niveau des jetons dans la main
    while (numCarte > nbCartesReservees){
        std::cout<<"Le numéro de la carte est invalide."<<std::endl;
        std::cout << "Tapez le numéro de la carte que vous voulez acheter : " << std::endl;
        std::cin >> numCarte;
    }
    // Vérification de la couleur de la carte réservée
    std::vector<std::string> listeCouleurs = {"blanc", "bleu", "vert", "noir", "rouge", "perle", "or", "indt"};
    std::cout << "Tapez la couleur de la carte que vous voulez acheter : " << std::endl;
    string couleur;
    std::cin >> couleur;
    // Vérification si la chaîne est présente dans la liste
    auto it = std::find(listeCouleurs.begin(), listeCouleurs.end(), couleur);
    while (it != listeCouleurs.end()){
        std::cout<<"Lea couleur est invalide"<<std::endl;
        std::cout << "Tapez la couleur de la carte que vous voulez acheter : " << std::endl;
        std::cin >> couleur;
        it = std::find(listeCouleurs.begin(), listeCouleurs.end(), couleur);
    }
    Couleur couleur2 = StringToCouleur(couleur);

    return std::make_pair(couleur2, numCarte);

}

std::pair< Couleur, unsigned int> StrategyIA::achatReserve(unsigned int nbCartesReservees){
    // Initialiser le générateur de nombres aléatoires avec la graine actuelle du système
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Tapez le numéro de la carte que vous voulez acheter : " << std::endl;
    // Vérifications -> voir plus au niveau des jetons dans la main
    // MODIFIER NB a voir par rapport à la couleur
    std::uniform_int_distribution<int> distribution2(0, nbCartesReservees);
    int numCarte = distribution2(gen);


    // Vérification de la couleur de la carte réservée
    std::vector<std::string> listeCouleurs = {"blanc", "bleu", "vert", "noir", "rouge", "perle", "or", "indt"};
    std::uniform_int_distribution<int> distribution(0, listeCouleurs.size() - 1);
    // Générer un indice aléatoire
    int indiceAleatoire = distribution(gen);

    // Utiliser l'indice pour obtenir la couleur aléatoire du vecteur
    std::string couleur = listeCouleurs[indiceAleatoire];

    std::cout << "Couleur aléatoire : " << couleur << std::endl;


    Couleur couleur2 = StringToCouleur(couleur);

    return std::make_pair(couleur2, numCarte);

}

void StrategyHumain::remplirPlateauStrat(Plateau& plateau, Sac& sac){
    plateau.remplirPlateau(sac);
}

void StrategyIA::remplirPlateauStrat(Plateau& plateau, Sac& sac){
    plateau.remplirPlateau(sac);
}

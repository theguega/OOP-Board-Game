#include "strategy.hpp"
#include <random>

unsigned int StrategyHumain::choix_min_max(unsigned int min, unsigned int max) {
    unsigned int choix;
    std::cout << "Choisissez un entier entre " << min << " et " << max <<" :"<<std::endl;
    std::cin>>choix;
    while(choix<min || choix>max) {
        std::cout<< "Votre choix ne rentre pas dans l'intervalle, veuillez recommencer : " << std::endl;
        std::cin>>choix;
    }
    return choix;
}

unsigned int StrategyIA::choix_min_max(unsigned int min, unsigned int max) {
    std::cout << "l'IA choisit entre " << min << " et " << max <<" :"<<std::endl;

    //generation d'un entier aleatoire entre min et max
    std::cout<<"pregen\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    unsigned int choix = distribution(gen);

    std::cout << "l'IA a choisit : " << choix << "\n";
    std::cout<<"postgen\n";
    return choix;
}

unsigned int StrategyHumain::choixMenu() {
    unsigned int choix;
    std::cin>>choix;
    while((choix<1) || (choix>3)) {
        std::cout<< "Votre choix ne rentre pas dans l'intervalle, veuillez recommencer : " << std::endl;
        std::cin>>choix;
    }
    return choix;
}

unsigned int StrategyIA::choixMenu() {
    //generation d'un entier aleatoire entre 1 et 3
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 3);
    unsigned int choix = distribution(gen);

    std::cout << "l'IA a choisit : " << choix << "\n";
    return choix;
}


























std::vector<const Jeton*> StrategyHumain::recupJetonStrat(Plateau& plateau){
    std::cout << "Combien de jetons souhaitez-vous recuperer ? (1 a 3) " << std::endl;
    unsigned int nbJetonsRecup;
    std::cin >> nbJetonsRecup;

    while (nbJetonsRecup > 3 || nbJetonsRecup < 1){
        std::cout <<"Le nombre de jetons est impossible \n Combien de jetons souhaitez-vous recuperer ? (1 a 3) " << std::endl;
        std::cin >> nbJetonsRecup;
    }

    std::cout << "Merci de selectionner des jetons adjacents en ligne, en colonne ou en diagonale." << std::endl << endl;

    std::vector<std::pair<unsigned int, unsigned int>> vecteurCoordonnees;

    // Recup des coordonnees des jetons
    for (unsigned int k = 0; k < nbJetonsRecup; k++){

        // Ajout des coordonnees
        std::cout<<"Jetons numero "<<k+1<<" : \n";
        vecteurCoordonnees.emplace_back(choisirJeton(plateau));
    }

    // Verifier que les jetons sont adjacents
    if (nbJetonsRecup > 1) {
        bool result1 = true;
        bool result2 = true;
        bool result3 = false; // Diago 1
        bool result4 = false; // Diago 2

        // Verif que les jetons sont adjacents en ligne
        for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            if (vecteurCoordonnees[i].first != vecteurCoordonnees[i + 1].first) {
                result1 = false;
            }
        }
        // Verif que les jetons sont adjacents en colonne
        for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            if (vecteurCoordonnees[i].second != vecteurCoordonnees[i + 1].second) {
                result2 = false;
            }
        }
        // Verif que les jetons sont adjacents en diagonale

        // Fonction de comparaison pour trier en fonction du premier element de la paire
        auto comparaison = [](const auto& a, const auto& b) {
            return a.first < b.first;
        };
        std::sort(vecteurCoordonnees.begin(), vecteurCoordonnees.end(), comparaison);

        for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            // premiere diagonale
            if ((vecteurCoordonnees[i].first+1 == vecteurCoordonnees[i + 1].first) && (vecteurCoordonnees[i].second-1 == vecteurCoordonnees[i + 1].second)) {
                result3 = true;
            }
        }

        for (unsigned int i = 0; i < vecteurCoordonnees.size()-1; i++) {
            // seconde diagonale
            if ((vecteurCoordonnees[i].first+1 == vecteurCoordonnees[i + 1].first) && (vecteurCoordonnees[i].second+1 == vecteurCoordonnees[i + 1].second)) {
                result4 = true;
            }
        }

        if (!result1 && !result2 && !result3 && !result4) {
            throw SplendorException("\nLes jetons ne sont pas adjacents");
        }

    }

    // Recup des jetons
    std::vector<const Jeton*> jetonsRecup;
    for (unsigned int k = 0; k < nbJetonsRecup; k++){
        if (plateau.caseVide(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second) || plateau.caseOr(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second))
            throw SplendorException("Il y a une case vide ou un jeton Or dans votre selection");
    }
    for (unsigned int k = 0; k < nbJetonsRecup; k++){
        jetonsRecup.push_back(&plateau.recupererJeton(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second));
    }
    return jetonsRecup;
}

std::vector<const Jeton*> StrategyIA::recupJetonStrat(Plateau& plateau){
    std::cout << "Combien de jetons souhaitez-vous recuperer ? (1 a 3) " << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    // Creer une distribution uniforme pour les entiers entre 1 et 3 inclus
    std::uniform_int_distribution<int> distribution(1, 3);
    // Generer un nombre aleatoire
    unsigned int nbJetonsRecup = distribution(gen);
    std::cout<<"On recupere "<<nbJetonsRecup<<" jetons"<<std::endl;

    // Methode = 1 correspond a recup en colonne
    // Methode = 2 correspond a recup en ligne
    // Methode = 3 correspond a recup en diagonale
    int methode = distribution(gen);

    std::vector<std::pair<unsigned int, unsigned int>> vecteurCoordonnees;
    vecteurCoordonnees.emplace_back(choisirJeton(plateau));
    std::vector<std::pair<int, int>> coordonneesAdjacentes;


    if (methode == 1){

        while (coordonneesAdjacentes.size() < nbJetonsRecup) {
            // Choisir aleatoirement une ligne dans la colonne choisie
            std::uniform_int_distribution<int> distributionLigne(0, plateau.getLargeurMatrice() - 1);
            std::pair<int, int> coord = choisirJeton(plateau);

            // Verifier si la coordonnee est valide
            if (coord.first + 2 < plateau.getLargeurMatrice()) {
                coordonneesAdjacentes.emplace_back(coord.first, coord.second);
                coordonneesAdjacentes.emplace_back(coord.first + 1, coord.second);
                coordonneesAdjacentes.emplace_back(coord.first + 2, coord.second);
            }
        }
    }
    if (methode == 2){

        while (coordonneesAdjacentes.size() < nbJetonsRecup) {
            // Choisir aleatoirement une colonne dans la colonne choisie
            std::uniform_int_distribution<int> distributionLigne(0, plateau.getLargeurMatrice() - 1);
            std::pair<int, int> coord = choisirJeton(plateau);

            // Verifier si la coordonnee est valide
            if (coord.second + 2 < plateau.getLargeurMatrice()) {
                coordonneesAdjacentes.emplace_back(coord.first, coord.second);
                coordonneesAdjacentes.emplace_back(coord.first, coord.second+1);
                coordonneesAdjacentes.emplace_back(coord.first, coord.second+2);
            }
        }
    }
    if (methode == 3){

        while (coordonneesAdjacentes.size() < nbJetonsRecup) {
            // Choisir aleatoirement une colonne dans la colonne choisie
            std::uniform_int_distribution<int> distributionLigne(0, plateau.getLargeurMatrice() - 1);
            std::pair<int, int> coord = choisirJeton(plateau);

            // Verifier si la coordonnee est valide
            if (coord.second + 2 < plateau.getLargeurMatrice() && coord.first + 2 < plateau.getLargeurMatrice()) {
                coordonneesAdjacentes.emplace_back(coord.first, coord.second);
                coordonneesAdjacentes.emplace_back(coord.first+1, coord.second+1);
                coordonneesAdjacentes.emplace_back(coord.first+2, coord.second+2);
            }
        }
    }

    // Recup des jetons
    std::vector<const Jeton*> jetonsRecup;
    for (unsigned int k = 0; k < nbJetonsRecup; k++){
        if (plateau.caseVide(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second) || plateau.caseOr(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second))
            throw SplendorException("Il y a une case vide ou un jeton Or dans votre selection");
    }
    for (unsigned int k = 0; k < nbJetonsRecup; k++){
        jetonsRecup.push_back(&plateau.recupererJeton(vecteurCoordonnees[k].first, vecteurCoordonnees[k].second));
    }
    return jetonsRecup;
}

unsigned int StrategyHumain::utiliserPrivilege() {
    unsigned int choix;
    std::cout<<"Combien de privilege voulez vous utiliser pour recup des jetons ? (1,2,3)\n";
    std::cin>>choix;

    return choix;
}

unsigned int StrategyIA::utiliserPrivilege() {
    std::cout<<"Combien de privilege voulez vous utiliser pour recup des jetons ? (1,2,3)\n";
    // Initialiser le generateur de nombres aleatoires avec la graine actuelle du systeme
    std::random_device rd;
    std::mt19937 gen(rd());
    // Creer une distribution uniforme pour les entiers entre 0 et 3 inclus
    std::uniform_int_distribution<int> distribution(1, 3);
    // Generer un nombre aleatoire
    unsigned int choix = distribution(gen);
    std::cout<<"l'IA utilise "<<choix<<" privilege\n"<<std::endl;
    return choix;
}

std::pair<unsigned int, unsigned int> StrategyHumain::choisirJeton(Plateau& plateau){
    unsigned int i, j;
    std::cout << "Entrez la valeur de i (1,2,3,4,5) : ";
    std::cin >> i;
    std::cout << "Entrez la valeur de j (1,2,3,4,5) : ";
    std::cin >> j;

    if((i > 5) || (i < 0) || (j > 5) || (j < 0))
        throw SplendorException("Indice de jeton incorrect");
    // Retourner la paire d'entiers
    return std::make_pair(i-1, j-1);
}

std::pair<unsigned int, unsigned int> StrategyIA::choisirJeton(Plateau& plateau){
    // Obtenez les dimensions du plateau
    size_t plateauRows = plateau.getLargeurMatrice();
    size_t plateauCols = plateau.getLargeurMatrice();

    // distribution uniforme pour generer des indices aleatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_int_distribution<int> distributionRow(0, plateauRows - 1);
    std::uniform_int_distribution<int> distributionCol(0, plateauCols - 1);

    // Genere des valeurs aleatoires pour i et j
    int i = distributionRow(gen);
    int j = distributionCol(gen1);
    if((i > 5) || (i < 0) || (j > 5) || (j < 0))
        throw SplendorException("Indice de jeton incorrect");
    // Retournez le jeton correspondant aux indices aleatoires
    std::cout<<"l'IA choisit de recup le jetons : ("<<i+1<<","<<j+1<<")\n";
    return std::make_pair(i, j);
}

unsigned int StrategyHumain::choixNiveau() {
    std::cout<<"Voulez-vous reserver une carte de la pyramide ou de la pioche de niveau i ? (0, 1, 2, 3)" << std::endl;
    unsigned int choix;
    std::cin >> choix;
    return choix;
}

unsigned int StrategyIA::choixNiveau() {
    std::cout<<"Voulez-vous reserver une carte de la pyramide ou de la pioche de niveau i ? (0, 1, 2, 3)" << std::endl;
    // Initialiser le generateur de nombres aleatoires avec la graine actuelle du systeme
    std::random_device rd;
    std::mt19937 gen(rd());
    // Creer une distribution uniforme pour les entiers entre 0 et 3 inclus
    std::uniform_int_distribution<int> distribution(0, 3);
    // Generer un nombre aleatoire
    int choix = distribution(gen);
    std::cout<<"On va en "<<choix<<".\n"<<std::endl;
    return choix;
}


unsigned int StrategyHumain::choixActionsOptionelles() {
    unsigned int choix;
    std::cout << "\033[1mActions optionnelles:\033[0m" << std::endl;
    std::cout << "1. Utiliser un privilege" << endl;
    std:: cout << "2. Remplir le plateau" << endl;
    std::cout << "3. Ne plus faire d'actions optionnelles" << endl;
    std::cout << "9. Quitter le jeu" << endl;
    std::cout << "Votre choix (1/2/3/9):" << std::endl;
    cin >> choix;
    return choix;
}

unsigned int StrategyIA::choixActionsOptionelles() {
    std::cout << "L'IA choisi entre: utiliser un privilege, remplir le plateau, ne rien faire (1/2/3): " << endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    // Creer une distribution uniforme pour les entiers entre 1 et 3 inclus
    std::uniform_int_distribution<int> distribution(1, 3);
    // Generer un nombre aleatoire
    unsigned int choix = distribution(gen);
    std::cout<<"Elle a choisi "<<choix<<".\n"<<std::endl;
    return choix;
}


unsigned int StrategyHumain::choixActionsObligatoires() {
    unsigned int choix;
    std::cout << "\033[1mActions obligatoires:\033[0m" << std::endl;
    std::cout << "1. Recuperer des jetons" << endl;
    std:: cout << "2. Acheter une carte joaillerie" << endl;
    std::cout << "3. Reserver une carte" << endl;
    std::cout << "9. Quitter le jeu" << endl;
    std::cout << "Votre choix (1/2/3/9):" << std::endl;
    cin >> choix;
    return choix;
}

unsigned int StrategyIA::choixActionsObligatoires() {
    std::cout << "L'IA choisi entre: Recuperer des jetons, Acheter une carte joaillerie, Reserver une carte (1/2/3): " << endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    // Creer une distribution uniforme pour les entiers entre 0 et 3 inclus
    std::uniform_int_distribution<int> distribution(1, 3);
    // Generer un nombre aleatoire
    unsigned int choix = distribution(gen);
    std::cout<<"Elle a choisit"<<choix<<".\n"<<std::endl;
    return choix;
}

unsigned int StrategyHumain::choixAchat(){
    std::cout << "Tapez 1 pour acheter une carte Reservee.\nTapez 2 pour acheter une carte du plateau." << std::endl;
    unsigned int choix;
    std::cin >> choix;
    while ((choix != 1) && (choix !=2)){
        std::cout<<"Le choix est incorrect\n"<<std::endl;
        std::cout << "Tapez 1 pour acheter une carte Reservee.\nTapez 2 pour acheter une carte du plateau." << std::endl;
        std::cin >> choix;
    }
    return choix;
}

unsigned int StrategyIA::choixAchat(){
    // Initialiser le generateur de nombres aleatoires avec la graine actuelle du systeme
    std::random_device rd;
    std::mt19937 gen(rd());
    // Creer une distribution uniforme pour les entiers entre 1 et 2 inclus
    std::uniform_int_distribution<int> distribution(1, 2);
    // Generer un nombre aleatoire
    int choix = distribution(gen);
    if (choix == 1) {
        std::cout << "On va acheter une carte reservee." << std::endl;
    }
    else {
        std::cout << "On va acheter une carte du plateau." << std::endl;
    }
    return choix;
}

std::pair<unsigned int, unsigned int> StrategyIA::reservationCarte(Pyramide& pyramide) {
    // Initialiser le generateur de nombres aleatoires avec la graine actuelle du systeme
    std::random_device rd;
    std::mt19937 gen(rd());

    std::random_device rd1;
    std::mt19937 gen1(rd1());
    // Creer une distribution uniforme pour les entiers entre 0 et 3 inclus
    std::uniform_int_distribution<int> distribution(1, 3);
    // Generer un nombre aleatoire
    int niveau = distribution(gen);

    std::cout << "Niveau: "<< niveau << std::endl;

    std::uniform_int_distribution<int> distributionNiveau(1, pyramide.getNbCartesNiv(niveau-1));
    int numCarte = distributionNiveau(gen1);
    std::cout << "Numero de carte: "<< numCarte << std::endl;


    return std::make_pair(niveau, numCarte);
}

std::pair<unsigned int, unsigned int> StrategyHumain::reservationCarte(Pyramide& pyramide) {
    std::cout << "Tapez le niveau de la carte que vous voulez reserver : " << std::endl;
    unsigned int niveau;
    std::cin >> niveau;
    std::cout << "Tapez le numero de la carte que vous voulez reserver : " << std::endl;
    unsigned int numCarte;
    std::cin >> numCarte;
    // Verifications
    while (numCarte > pyramide.getNbCartesNiv(niveau) || niveau <= 0 || niveau >= 3 || numCarte <= 0){
        std::cout<<"Le numero de la carte ou son niveau est incorrect\n"<<std::endl;
        std::cout << "Tapez le niveau de la carte que vous voulez reserver : " << std::endl;
        std::cin >> niveau;
        std::cout << "Tapez le numero de la carte que vous voulez reserver : " << std::endl;
        std::cin >> numCarte;
    }

    return std::make_pair(niveau, numCarte);
}

std::pair<unsigned int, unsigned int> StrategyHumain::achatNoble(Pyramide& pyramide) {
    std::cout << "Tapez le numero de la carte noble que vous voulez acheter : " << std::endl;
    unsigned int numCarte;
    std::cin >> numCarte;
    // Verifications
    while (numCarte > pyramide.getNbCartesNiv(4) || numCarte < 0){
        std::cout<<"Le numero de la carte est incorrect\n"<<std::endl;
        std::cout << "Tapez le numero de la carte noble que vous voulez acheter : " << std::endl;
        std::cin >> numCarte;
    }

    return std::make_pair(4, numCarte);

}

std::pair<unsigned int, unsigned int> StrategyIA::achatNoble(Pyramide& pyramide) {
    std::cout << "Tapez le numero de la carte noble que vous voulez acheter : " << std::endl;
    // Initialiser le generateur de nombres aleatoires avec la graine actuelle du systeme
    std::random_device rd;
    std::mt19937 gen(rd());
    // Creer une distribution uniforme pour les entiers entre 0 et 3 inclus
    std::uniform_int_distribution<int> distribution(0, pyramide.getNbCartesNiv(4));
    // Generer un nombre aleatoire
    int numCarte = distribution(gen);
    std::cout<<"Numero de carte : "<<numCarte<< std::endl;
    return std::make_pair(4, numCarte);

}

std::pair< Couleur, unsigned int> StrategyHumain::achatReserve(unsigned int nbCartesReservees){
    std::cout << "Voici les cartes reservees : " << std::endl;
    unsigned int i = 0;

    std::cout << "Tapez le numero de la carte que vous voulez acheter : " << std::endl;
    unsigned int numCarte;
    std::cin >> numCarte;
    // Verifications -> voir plus au niveau des jetons dans la main
    while (numCarte > nbCartesReservees){
        std::cout<<"Le numero de la carte est invalide."<<std::endl;
        std::cout << "Tapez le numero de la carte que vous voulez acheter : " << std::endl;
        std::cin >> numCarte;
    }
    // Verification de la couleur de la carte reservee
    std::vector<std::string> listeCouleurs = {"blanc", "bleu", "vert", "noir", "rouge", "perle", "or", "indt"};
    std::cout << "Tapez la couleur de la carte que vous voulez acheter : (blanc, bleu, vert, perle, or, indt) " << std::endl;
    string couleur;
    std::cin >> couleur;
    // Verification si la chaîne est presente dans la liste
    auto it = std::find(listeCouleurs.begin(), listeCouleurs.end(), couleur);
    while (it == listeCouleurs.end()){
        std::cout<<"La couleur est invalide"<<std::endl;
        std::cout << "Tapez la couleur de la carte que vous voulez acheter : " << std::endl;
        std::cin >> couleur;
        it = std::find(listeCouleurs.begin(), listeCouleurs.end(), couleur);
    }
    Couleur couleur2 = StringToCouleur(couleur);

    return std::make_pair(couleur2, numCarte);

}

std::pair< Couleur, unsigned int> StrategyIA::achatReserve(unsigned int nbCartesReservees){
    // Initialiser le generateur de nombres aleatoires avec la graine actuelle du systeme
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Tapez le numero de la carte que vous voulez acheter : " << std::endl;
    // Verifications -> voir plus au niveau des jetons dans la main
    // MODIFIER NB a voir par rapport a la couleur
    std::uniform_int_distribution<int> distribution2(0, nbCartesReservees);
    int numCarte = distribution2(gen);


    // Verification de la couleur de la carte reservee
    std::vector<std::string> listeCouleurs = {"blanc", "bleu", "vert", "noir", "rouge", "perle", "or", "indt"};
    std::uniform_int_distribution<int> distribution(0, listeCouleurs.size() - 1);
    // Generer un indice aleatoire
    int indiceAleatoire = distribution(gen);

    // Utiliser l'indice pour obtenir la couleur aleatoire du vecteur
    std::string couleur = listeCouleurs[indiceAleatoire];

    std::cout << "Couleur aleatoire : " << couleur << std::endl;


    Couleur couleur2 = StringToCouleur(couleur);

    return std::make_pair(couleur2, numCarte);

}

#include "joueur.hpp"
#include <algorithm>


std::string toStringType(type t) {
    switch (t) {
        case type::IA: return "IA";
        case type::HUMAIN: return "HUMAIN";
    }
    throw JoueurException("Type inconnu");
}

type toType(std::string s) {
    if (s == "IA") return type::IA;
    return type::HUMAIN;
}

// Constructeur
Joueur::Joueur(string pseudo, type typeDeJoueur):
                // Voir strategyyy
               pseudo(pseudo), typeDeJoueur(typeDeJoueur), ptsPrestige(0), nbCouronnes(0), gagnant(0) {
                //on initialise les map avec les bonnes couleurs
                for (const auto& couleur : Couleurs) {
                    if (couleur != Couleur::INDT) {
                        jetons[couleur];
                        if (couleur != Couleur::OR) {
                            cartes[couleur];
                            cartesReservees[couleur];
                            bonus[couleur] = 0;
                        }
                    }
                }
}

// Destructeur
Joueur::~Joueur() {
    // Voir l'interet d'un destructeur
    /*
    for (int i = 0; i < nbCartes; i++) {
        delete cartes[i];
    }
    for (int i = 0; i < nbJetons; i++) {
        delete jetons[i];
    }
    for (int i = 0; i < nbPrivileges; i++) {
        delete privileges[i];
    }*/
}

// Getter
size_t Joueur::getNbCartes() const {
    size_t nbCartes = 0;
    for (const auto& couleur : Couleurs) {
        if (couleur != Couleur::INDT && couleur != Couleur::OR) {
            nbCartes += cartes.at(couleur).size();
        }
    }

    return nbCartes;
}

size_t Joueur::getNbCartesReservees() const {
    size_t nbCartes = 0;
    for (const auto& couleur : Couleurs) {
        if (couleur != Couleur::INDT && couleur != Couleur::OR) {
            nbCartes += cartesReservees.at(couleur).size();
        }
    }

    return nbCartes;
}

size_t Joueur::getNbJetons() const {
    size_t nbJetons = 0;
    for (const auto& couleur : Couleurs) {
        if (couleur != Couleur::INDT && couleur != Couleur::OR) {
            nbJetons += jetons.at(couleur).size();
        }
    }

    return nbJetons;
}

// Affichages

void Joueur::afficherJoueur() const {
    std::cout << "Pseudo : " << pseudo << std::endl;
    std::cout << "Type de joueur : " << toStringType(typeDeJoueur) << std::endl;
    std::cout << "Points de prestiges : " << ptsPrestige << std::endl;
    std::cout << "Nombre de couronnes : " << nbCouronnes << std::endl;
    std::cout << "Nombre de cartes : " << getNbCartes() << std::endl;
    std::cout << "Nombre de cartes reservees : " << getNbCartesReservees() << std::endl;
    std::cout << "Nombre de jetons : " << getNbJetons() << std::endl;
    std::cout << "Nombre de privileges : " << getNbPrivileges() << std::endl;
}

void Joueur::afficherCartes() const {
    for (int i = 0; i < getNbCartes(); i++) {
        std::cout << "Carte " << i << " : " << std::endl;
        //cartes[i]->afficherCarte();
    }
}

void Joueur::afficherJetons() const {
    for (int i = 0; i < getNbJetons(); i++) {
        std::cout << "Jeton " << i << " : " << std::endl;
        //jetons[i]->afficherJeton();
    }
}

// Ajout des éléments

void Joueur::addCarte(const Carte &carte) {
    cartes[carte.getBonus().getCouleur()].push_back(&carte);
    ptsPrestige += carte.getNbPtsPrivilege();
    nbCouronnes += carte.getNbCouronnes();
}

void Joueur::addCarteReservee(const Carte &carte) {
    cartesReservees[carte.getBonus().getCouleur()].push_back(&carte);
}

void Joueur::addCarteNoble(const Carte& carte){
    cartesNobles.push_back(&carte);
}

void Joueur::addJeton(const Jeton& jeton) {
    jetons[jeton.getCouleur()].push_back(&jeton);
}

void Joueur::addPrivilege(const Privilege &privilege) {
    privileges.push_back(&privilege);
}


// Suppression des éléments

void::Joueur::supCarte(Carte &carte) {
    for (int i = 0; i < cartes[carte.getBonus().getCouleur()].size(); i++) {
        if (cartes[carte.getBonus().getCouleur()][i] == &carte) {
            nbCouronnes -= carte.getNbCouronnes();
            ptsPrestige -= carte.getNbPtsPrivilege();
            cartes[carte.getBonus().getCouleur()].erase(cartes[carte.getBonus().getCouleur()].begin() + i);
        }
    }
}

void::Joueur::supCarteReservee(const Carte &carte) {
    for (int i = 0; i < cartes[carte.getBonus().getCouleur()].size(); i++) {
        if (cartesReservees[carte.getBonus().getCouleur()][i] == &carte) {
            cartesReservees[carte.getBonus().getCouleur()].erase(cartes[carte.getBonus().getCouleur()].begin() + i);
        }
    }
}

void Joueur::supCarteNoble(const Carte& carte){
    for (int i = 0; i < cartesNobles.size(); i++) {
        if (cartesNobles[i] == &carte) {
            cartesNobles.erase(cartesNobles.begin()+i);
        }
    }
}

void::Joueur::supJeton(Jeton *jeton, EspaceJeux& espaceJeux) {
    for (int i = 0; i < jetons[jeton->getCouleur()].size(); i++) {
        if (jetons[jeton->getCouleur()][i] == jeton) {
            // On rajoute le jeton dans le sac
            espaceJeux.getSac().ajouterJeton(*jetons[jeton->getCouleur()][i]);
            jetons[jeton->getCouleur()].erase(jetons[jeton->getCouleur()].begin() + i);
        }
    }
}

void Joueur::supJetonNb(unsigned int nb, Couleur c, EspaceJeux& espaceJeux){
    for (int i = 0; i < nb; i++) {
        // On rajoute le jeton dans le sac
        espaceJeux.getSac().ajouterJeton(*jetons[c].back());
        // On supprime le jeton du joueur
        jetons[c].pop_back();
    }

}

const Privilege&::Joueur::supPrivilege(Plateau& plateau) {
    const Privilege& sup = *privileges[0];
    privileges.erase(privileges.begin());
    // rajout du privilège sur le plateau
    plateau.poserPrivilege(sup);

    return  sup;
}



bool Joueur::nbPtsPrestigeParCouleurSupDix() const{
    // Itère sur toutes les couleurs
    for (const auto& pair : cartes) {
        const std::vector<const Carte*>& tab = pair.second;
        unsigned int somme = 0;

        // Calcule la somme pour chaque couleur
        for (const auto* carte : tab) somme += carte->getNbPtsPrivilege();
        if (somme >= 10) return true;
    }
    return false;
}

bool Joueur::verifAchatCarte(const Carte& carte, EspaceJeux& espaceJeux) {
    // 1 recuperer les points nécessaires pour acheter la carte
    // 2 voir le nb de jetons par couleur
    // 3 ajouter les bonus
    // 4 voir si le joueur a assez de points pour acheter la carte
    // 5 si pas assez essayer avec les jetons or

    // recup des points nécessaires pour acheter la carte
    unsigned int needBlanc =  carte.getPrix().getBlanc() ;
    unsigned int needBleu =  carte.getPrix().getBleu();
    unsigned int needVert =  carte.getPrix().getVert();
    unsigned int needRouge =  carte.getPrix().getRouge();
    unsigned int needNoir =  carte.getPrix().getNoir();
    unsigned int needPerle = carte.getPrix().getPerle();

    // recup des jetons du joueur
    // Map des bonus associés à chaque couleur

// Map des bonus associés à chaque couleur


    unsigned int nbBlanc = 0;
    auto itBlanc = jetons.find(Couleur::BLANC);
    if (itBlanc != jetons.end()) {
        nbBlanc = itBlanc->second.size();

        auto itBonusBlanc = bonus.find(Couleur::BLANC);
        if (itBonusBlanc != bonus.end()) {
            nbBlanc += itBonusBlanc->second;
        }
    }

    unsigned int nbBleu = 0;
    auto itBleu = jetons.find(Couleur::BLEU);
    if (itBleu != jetons.end()) {
        nbBleu = itBleu->second.size();

        auto itBonusBleu = bonus.find(Couleur::BLEU);
        if (itBonusBleu != bonus.end()) {
            nbBleu += itBonusBleu->second;
        }
    }

    unsigned int nbVert = 0;
    auto itVert = jetons.find(Couleur::VERT);
    if (itVert != jetons.end()) {
        nbVert = itVert->second.size();

        auto itBonusVert = bonus.find(Couleur::VERT);
        if (itBonusVert != bonus.end()) {
            nbVert += itBonusVert->second;
        }
    }

    unsigned int nbRouge = 0;
    auto itRouge = jetons.find(Couleur::ROUGE);
    if (itRouge != jetons.end()) {
        nbRouge = itRouge->second.size();

        auto itBonusRouge = bonus.find(Couleur::ROUGE);
        if (itBonusRouge != bonus.end()) {
            nbRouge += itBonusRouge->second;
        }
    }

    unsigned int nbNoir = 0;
    auto itNoir = jetons.find(Couleur::NOIR);
    if (itNoir != jetons.end()) {
        nbNoir = itNoir->second.size();

        auto itBonusNoir = bonus.find(Couleur::NOIR);
        if (itBonusNoir != bonus.end()) {
            nbNoir += itBonusNoir->second;
        }
    }

    unsigned int nbPerle = 0;
    auto itPerle = jetons.find(Couleur::PERLE);
    if (itPerle != jetons.end()) {
        nbPerle = itPerle->second.size();

    }

    unsigned int nbOr = 0;
    auto itOr = jetons.find(Couleur::OR);
    if (itOr != jetons.end()) {
        nbOr = itOr->second.size();

    }

    if (nbBlanc >= needBlanc && nbBleu >= needBleu && nbVert >= needVert &&
        nbRouge >= needRouge && nbNoir >= needNoir && nbPerle >= needPerle) {

        // On supprime les jetons utilisés
        supJetonNb(needBlanc, Couleur::BLANC, espaceJeux);
        supJetonNb(needBleu, Couleur::BLEU, espaceJeux);
        supJetonNb(needVert, Couleur::VERT, espaceJeux);
        supJetonNb(needRouge, Couleur::ROUGE, espaceJeux);
        supJetonNb(needNoir, Couleur::NOIR, espaceJeux);
        supJetonNb(needPerle, Couleur::PERLE, espaceJeux);


        return true;  // Le joueur a suffisamment de jetons pour acheter la carte
    }

    // 5. Si pas assez, essayer avec les jetons or
    unsigned int jetonsOrUtilises = 0;

    // Fonction pour ajouter des jetons or à une couleur donnée
    auto ajouterJetonsOr = [&jetonsOrUtilises, &nbOr](unsigned int& nbCouleur, unsigned int besoin) {
        while (nbOr > 0 && besoin > nbCouleur) {
            // Utiliser un jeton or pour compléter le besoin
            nbOr--;
            nbCouleur++;
            jetonsOrUtilises++;
        }
    };

    ajouterJetonsOr(nbBlanc, needBlanc);
    ajouterJetonsOr(nbBleu, needBleu);
    ajouterJetonsOr(nbVert, needVert);
    ajouterJetonsOr(nbRouge, needRouge);
    ajouterJetonsOr(nbNoir, needNoir);
    ajouterJetonsOr(nbPerle, needPerle);

    // Vérifier à nouveau si le joueur a maintenant assez de points pour acheter la carte
    if (needBlanc <= nbBlanc && needBleu <= nbBleu && needVert <= nbVert &&
        needRouge <= nbRouge && needNoir <= nbNoir && needPerle <= nbPerle) {
        std::cout << "Carte achetable avec " << jetonsOrUtilises << " jeton(s) or utilisé(s)." << std::endl;

        supJetonNb(needBlanc, Couleur::BLANC, espaceJeux);
        supJetonNb(needBleu, Couleur::BLEU, espaceJeux);
        supJetonNb(needVert, Couleur::VERT, espaceJeux);
        supJetonNb(needRouge, Couleur::ROUGE, espaceJeux);
        supJetonNb(needNoir, Couleur::NOIR, espaceJeux);
        supJetonNb(needPerle, Couleur::PERLE, espaceJeux);
        supJetonNb(jetonsOrUtilises, Couleur::OR, espaceJeux);

        return true;
    } else {
        std::cout << "Le joueur n'a pas assez de jetons pour acheter la carte." << std::endl;
        return false;
    }
}


///////////////////////// Actions d'un joueur /////////////////////////

void Joueur::utiliserPrivilege(Plateau& plateau){
    if (privileges.size() == 0) {
        throw JoueurException("Le joueur n'a pas de privilège");
    }
    if (plateau.getLargeurMatrice()==0){
        throw JoueurException("Le plateau n'a pas de jetons");
    }
    const Privilege& privilege = supPrivilege(plateau);
    plateau.poserPrivilege(privilege);
    const Jeton& jetonSelec = strategy->choisirJeton(plateau);
    addJeton(jetonSelec);

}

void Joueur::remplirPlateau(Plateau& plateau, Sac& sac, Joueur& joueurAdverse){
    strategy->remplirPlateauStrat(plateau, sac);
    if (privileges.size() == 3){
        std::cout<< "Vous avez deja 3 privileges. Vous n'en recupererez donc pas plus !" << std::endl;
        return;
    }
    // Verifier s'il reste des privileges sur le plateau
    if (!plateau.pivilegeDisponible()){
        std::cout<< "Il n'y a plus de privileges sur le plateau !\nLe joueur adverse perd donc un privilege..." << std::endl;
        const Privilege& privilege = joueurAdverse.supPrivilege(plateau); // recuperation du privilege du joueur adverse
        addPrivilege(privilege); // ajout du privilege au joueur
        return;
    }
    // Cas standard
    const Privilege& privilege = plateau.recupererPrivilege();
    addPrivilege(privilege);
}

void Joueur::recupererJetons(Plateau& plateau){
    std::cout << "Combien de jetons souhaitez-vous recuperer ? (1 a 3) " << std::endl;
    unsigned int nbJetonsRecup;
    std::cin >> nbJetonsRecup;

    while (nbJetonsRecup > 3 || nbJetonsRecup < 1){
        std::cout <<"Le nombre de jetons est impossible\nCombien de jetons souhaitez-vous recuperer ? (1 a 3) " << std::endl;
        std::cin >> nbJetonsRecup;
    }

    std::cout << "Merci de selectionner des jetons adjacents en ligne, en colonne ou en diagonale." << std::endl;

    std::vector<std::pair<unsigned int, unsigned int>> vecteurCoordonnees;
    std::vector<const Jeton*> jetonsRecup;

    // Récup des coordonnées des jetons
    for (unsigned int k = 0; k < nbJetonsRecup; k++){
        unsigned int i, j;
        const Jeton& jeton = strategy->choisirJeton(plateau);
        // Ajout des coordonnees
        vecteurCoordonnees.emplace_back(i, j);
        // Ajout du jeton
        jetonsRecup.push_back(&jeton);
    }

    // Verifier que les jetons sont adjacents
    if (jetons.size() > 1) {
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
            throw JoueurException("Les jetons ne sont pas adjacents");
        }

    }

    // ajout des jetons dans la main du joueur
    for (auto & i : jetonsRecup){
        addJeton(*i);
    }

}

void Joueur::orReserverCarte (Pyramide& pyramide, Plateau& plateau){
    std::cout<<"Volez-vous réserver une carte de la pyramide ou de la pioche de niveau i ? (0, 1, 2, 3)" << std::endl;
    unsigned int choix;
    std::cin >> choix;

    if (choix == 0){
        // Reservation de la carte
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
        const Carte& carte = pyramide.acheterCarte(niveau, numCarte);
        addCarteReservee(carte);


        // Recuperation d'un jeton or Voir exception mécanique de jeu
        const Jeton& jeton = strategy->choisirJeton(plateau);
        if(jeton.getCouleur() != Couleur::OR){
            throw JoueurException("Le jeton choisi n'est pas un jeton or");
        }
        addJeton(jeton);


    }
    else if (choix == 1 || choix == 2 || choix == 3){
        // Reservation de la carte
        const Carte& carte = pyramide.ReserverCartePioche(choix);
        addCarteReservee(carte);

        // Recuperation d'un jeton or
        const Jeton& jeton = strategy->choisirJeton(plateau);
        if(jeton.getCouleur() != Couleur::OR){
            throw JoueurException("Le jeton choisi n'est pas un jeton or");
        }
        addJeton(jeton);
    }


}

void Joueur::acheterCarteNoble (Pyramide& pyramide){
    // affichage cartes nobles
    pyramide.afficherPyramide();
    std::cout << "Tapez le numero de la carte noble que vous voulez acheter : " << std::endl;
    unsigned int numCarte;
    std::cin >> numCarte;
    // Vérifications
    while (numCarte > pyramide.getNbCartesNiv(4) || numCarte < 0){
        std::cout<<"Le numéro de la carte est incorrect\n"<<std::endl;
        std::cout << "Tapez le numero de la carte noble que vous voulez acheter : " << std::endl;
        std::cin >> numCarte;
    }
    const Carte& carte = pyramide.acheterCarte(4, numCarte);
    addCarteNoble(carte);
}


void Joueur::acheterCarteJoaillerie (EspaceJeux& espaceJeux){
    // Voir comment gérer les bonus
    std::cout << "Tapez 1 pour acheter une carte Réservée.\nTapez 2 pour acheter une carte du plateau." << std::endl;
    unsigned int choix;
    std::cin >> choix;
    while ((choix != 1) && (choix !=2)){
        std::cout<<"Le choix est incorrect\n"<<std::endl;
        std::cout << "Tapez 1 pour acheter une carte Réservée.\nTapez 2 pour acheter une carte du plateau." << std::endl;
        std::cin >> choix;
    }

    // Achat carte reservee
    if (choix == 1){
        std::cout << "Voici les cartes réservées : " << std::endl;
        unsigned int i = 0;
        // Affichage de la réserve
        for (auto & cartesReservee : cartesReservees) {
            std::cout <<"Numéro "<<i << " : ";
            //std::cout<<cartesReservee;
            i++;
        }
        std::cout << "Tapez le numéro de la carte que vous voulez acheter : " << std::endl;
        unsigned int numCarte;
        std::cin >> numCarte;
        // Vérifications -> voir plus au niveau des jetons dans la main
        while (numCarte > cartesReservees.size()){
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

        const Carte& carte = *cartesReservees[couleur2][numCarte];



        // A MODIFIER
        if (!verifAchatCarte(carte, espaceJeux)) {
            throw JoueurException("Vous n'avez pas assez de points pour acheter cette carte...");
        }
        addCarte(carte);
        // rajout des couronnes
        nbCouronnes += carte.getNbCouronnes();
        // Rajout du bonus dans le joueur
        bonus[carte.getBonus().getCouleur()] += carte.getBonus().getNbBonus();
        supCarteReservee(carte);
    }
    // Achat carte du plateau
    else if (choix == 2){
        // Affichage des cartes
        std::cout << "Voici les cartes du plateau : " << std::endl;
        espaceJeux.getPyramide().afficherPyramide(); //Gerer l'affichage de la pyramide

        std::cout << "Tapez le niveau de la carte que vous voulez acheter : " << std::endl;
        unsigned int niveau;
        std::cin >> niveau;
        std::cout << "Tapez le numero de la carte que vous voulez acheter : " << std::endl;
        int numCarte;
        std::cin >> numCarte;

        // Vérifications
        while (numCarte > espaceJeux.getPyramide().getNbCartesNiv(niveau)){
            std::cout<<"Le numéro de la carte est incorrect\n"<<std::endl;
            std::cout << "Tapez le numero de la carte que vous voulez acheter : " << std::endl;
            std::cin >> numCarte;
        }

        const Carte& carte = espaceJeux.getPyramide().acheterCarte(niveau, numCarte);
        if (!verifAchatCarte(carte, espaceJeux)){
            throw JoueurException("Vous n'avez pas assez de points pour acheter cette carte");
        }
        addCarte(carte);
        // rajout des couronnes
        nbCouronnes += carte.getNbCouronnes();
        // Rajout du bonus dans le joueur
        bonus[carte.getBonus().getCouleur()] += carte.getBonus().getNbBonus();
    }
    else {
        std::cout<<"Le choix est incorrect\n"<<std::endl;
    }


}


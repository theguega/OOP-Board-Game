#include "strategy.hpp"
#include <random>

unsigned int StrategyHumain::choix_min_max(unsigned int min, unsigned int max) {
    unsigned int choix;
    qDebug() << "Choisissez un entier entre " << min << " et " << max <<" :"<<"\n";
    std::cin>>choix;
    if(choix<min || choix>max)
        throw SplendorException("Votrez choix ne rentrait pas dans l'intervalle");
    return choix;
}

unsigned int StrategyIA::choix_min_max(unsigned int min, unsigned int max) {
    qDebug() << "l'IA choisit entre " << min << " et " << max <<" :"<<"\n";

    //generation d'un entier aleatoire entre min et max
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    int choix = distribution(gen);

    qDebug() << "l'IA a choisit : " << choix << "\n";
    return choix;
}




unsigned int StrategyHumain::choixMenu(vector<int> poss) {
    unsigned int choix;
    std::cin>>choix;
    if(((choix<1) || (choix>3)) && (choix != 9))
        throw SplendorException("Votre choix n'est pas conforme");
    return choix;
}

unsigned int StrategyIA::choixMenu(vector<int> poss) {
    //generation d'un entier aleatoire entre 1 et 3
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, poss.size());
    unsigned int choix = distribution(gen);

    qDebug() << "l'IA a choisit : " << choix << "\n";
    return poss[choix-1];
}




Couleur StrategyHumain::choixCouleur() {
    qDebug() << "Choisissez une couleur : (blanc,bleu,vert,noir,rouge,perle,indt) (sensible a la casse) \n" << "\n";
    string couleur_input;
    std::cin >> couleur_input;
    Couleur couleur = StringToCouleur(couleur_input);

    return couleur;
}

Couleur StrategyIA::choixCouleur() {
    std::vector<std::string> listeCouleurs = {"blanc", "bleu", "vert", "noir", "rouge", "perle", "indt"};

    //generation d'un entier aleatoire entre 0 et 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 6);
    int choix = distribution(gen);

    Couleur couleur = StringToCouleur(listeCouleurs[choix]);
    qDebug() << "l'IA a choisit la couleur " << listeCouleurs[choix] << "\n";

    return couleur;
}

Couleur StrategyHumain::choixCouleurNonINDT() {
    qDebug() << "Choisissez une couleur : (blanc,bleu,vert,noir,rouge,perle) (sensible a la casse) \n" << "\n";
    string couleur_input;
    std::cin >> couleur_input;
    Couleur couleur = StringToCouleur(couleur_input);

    if(couleur==Couleur::INDT)
        throw SplendorException("La couleur ne doit pas etre indtermine dans ce cas ci");

    return couleur;
}

Couleur StrategyIA::choixCouleurNonINDT() {
    std::vector<std::string> listeCouleurs = {"blanc", "bleu", "vert", "noir", "rouge", "perle"};

    //generation d'un entier aleatoire entre 0 et 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, listeCouleurs.size());
    int choix = distribution(gen);

    Couleur couleur = StringToCouleur(listeCouleurs[choix]);
    qDebug() << "l'IA a choisit la couleur " << listeCouleurs[choix] << "\n";

    return couleur;
}

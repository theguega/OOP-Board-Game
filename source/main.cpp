#include "partie.hpp"
#include <filesystem>


//Mettez ici le chemin absolue vers le projet
//Theo
//std::filesystem::path projectPath = string("/Users/theoguegan/Documents/UTC/GI01/LO21/Projet_LO21");
//Samuel B
//std::filesystem::path projectPath = string("\\Users\\Beziat\\source\\repos\\Projet_LO21");
//Robert
//std::filesystem::path projectPath = string("/Users/robertantaluca/Desktop/Projet_LO21");
//Samuel M
//std::filesystem::path projectPath = string("C:/Users/samma/Documents/Programmation/LO21/Projet_LO21");
//Maxime

int main(int argc, const char * argv[]) {

    Partie *partie = new Partie();
    std::cout<<"Breakpoint creation"<<std::endl;
    delete partie;
    std::cout<<"Breakpoint destruction"<<std::endl;
    std::cout<<"Test";
    
    return 0;
}


/*
        std::cout << "Bonjour !\nVeuillez creer les joueurs : \n";
        std::string nom, prenom;
        std::string typedejoueur;
        type typeDeJoueur;

        std::cout << "Nom du joueur 1 : ";
        std::cin >> nom;
        std::cout << "Prenom du joueur 1 : ";
        std::cin >> prenom;
        std::cout << "Type de joueur (IA ou HUMAIN) : ";
        std::cin >> typedejoueur;
        typeDeJoueur = toType(typedejoueur);
        Joueur joueur1(nom, prenom, typeDeJoueur);
        std::cout << "\n\n";

        joueur1.afficherJoueur();

        joueur1.addPrivilege(plateau.recupererPrivilege());
        //joueur1.afficherPrivileges();
        joueur1.afficherJoueur();
        */


/*
        //Création du lot
        const LotDeJetons& lotJetons = LotDeJetons::getLotDeJetons();
        //Création du sac
        Sac& sac = Sac::getSac(lotJetons);
        //Creation du plateau
        const LotPrivileges& lotPrivileges = LotPrivileges::getLotPrivileges();
        Plateau& plateau = Plateau::getPlateau(sac, lotPrivileges);

        //Recuperation de deux jetons sur le plateau et remise dans le sac
        const Jeton& jeton1 = plateau.recupererJeton(0,0);
        std::cout << jeton1 << "\n";
        sac.ajouterJeton(jeton1);
        
        const Jeton& jeton2 = plateau.recupererJeton(2,2);
        std::cout << jeton2 << "\n";
        sac.ajouterJeton(jeton2);

        //Remise d'un jeton du sac sur le plateau
        plateau.positionerJeton(sac.piocherJeton());

        std::cout<<"Voilaaaa, on est content"<<std::endl;
        */

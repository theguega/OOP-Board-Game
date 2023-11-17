#include "partie.hpp"
#include <filesystem>

//Mettez ici le chemin absolue vers le projet
//Theo
//std::filesystem::path projectPath = string("/Users/theoguegan/Documents/UTC/GI01/LO21/Projet_LO21");
//Samuel B
//std::filesystem::path projectPath = string("\\Users\\Beziat\\source\\repos\\Projet_LO21");
//Robert
std::filesystem::path projectPath = string("/Users/robertantaluca/Desktop/Projet_LO21");
//Samuel M
//Maxime

int main(int argc, const char * argv[]) {

    std::cout<<"Bonjour, à combien de joueur voulez vous jouer ? (0,1,2)"<<std::endl;
    int nbJoueur;
    std::cin>>nbJoueur;
    switch (nbJoueur) {
        case 0: 
        {
            std::cout<<"IA vs IA"<<std::endl;
            Partie *partie = new Partie();
            std::cout<<"Breakpoint creation"<<std::endl;
            std::cout<<partie->getEspaceJeux()->getPlateau()<<std::endl;
            partie->getEspaceJeux()->getPyramide().afficherPyramide();
            delete partie;
            std::cout<<"Breakpoint destruction"<<std::endl;
            std::cout<<"Test";
            break;
        }
        
        case 1:
        {
            std::cout<<"IA vs HUMAIN"<<std::endl;
            std::cout<<"Veuillez saisir le nom du joueur"<<std::endl;
            std::string nom;
            std::cin>>nom;
            std::cout<<"Veuillez saisir le prenom du joueur"<<std::endl;
            std::string prenom;
            std::cin>>prenom;
            Partie *partie1 = new Partie(nom, prenom);
            std::cout<<"Breakpoint creation"<<std::endl;
            delete partie1;
            std::cout<<"Breakpoint destruction"<<std::endl;
            break;
        }
        case 2:
        {
            std::cout<<"HUMAIN vs HUMAIN"<<std::endl;
            std::cout<<"Veuillez saisir le nom du joueur 1"<<std::endl;
            std::string nom1;
            std::cin>>nom1;
            std::cout<<"Veuillez saisir le prenom du joueur 1"<<std::endl;
            std::string prenom1;
            std::cin>>prenom1;
            std::cout<<"Veuillez saisir le nom du joueur 2"<<std::endl;
            std::string nom2;
            std::cin>>nom2;
            std::cout<<"Veuillez saisir le prenom du joueur 2"<<std::endl;
            std::string prenom2;
            std::cin>>prenom2;
            Partie *partie2 = new Partie(nom1, prenom1, nom2, prenom2);
            std::cout<<"Breakpoint creation"<<std::endl;
            delete partie2;
            std::cout<<"Breakpoint destruction"<<std::endl;
            break;
        }
        default:
            std::cout<<"Erreur, veuillez saisir un nombre entre 0 et 2"<<std::endl;
            return 0;
            break;
    }

    //boucle de jeux

    return 0;
}

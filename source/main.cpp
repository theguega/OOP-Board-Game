#include <iostream>
#include "jetons.hpp"

int main(int argc, const char * argv[]) {
    try
    {
        //Création du lot
        LotDeJetons lotJetons;
        //Création du sac
        Sac sac(lotJetons);
        //Creation du plateau
        LotPrivileges lotPrivileges;
        Plateau plateau(sac, lotPrivileges);

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
    }
    catch (JetonException& e)
    {
        std::cout << e.getInfo() << "\n";
    }
    
    return 0;
}

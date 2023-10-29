#include <iostream>
#include "jetons.hpp"

int main(int argc, const char * argv[]) {
    try
    {
        //Création du lot
        LotDeJetons lot;
        //Création du sac
        Sac sac(lot);
        
        //Creation du plateau
        LotPrivilege lotPrivilege;

        //test (fonctionnel) de remplissage de plateau (se fera par le joueur dans le jeu)
        Plateau plateau(lotPrivilege);
        for (int i=0; i<25; i++) {
            plateau.positionerJeton(&sac.piocherJeton());
        }
        
        std::cout<<"hi";
        
    }
    catch (JetonException& e)
    {
        std::cout << e.getInfo() << "\n";
    }
    
    return 0;
}

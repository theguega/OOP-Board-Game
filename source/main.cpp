#include <iostream>
#include "jetons.hpp"


int main(int argc, const char * argv[]) {
    try
    {
        //Création du lot
        LotDeJetons lot;
        //Création du sac
        Sac sac = Sac(lot);
        //Tirage de 2 jetons
        std::cout << sac.piocherJeton() << "\n";
        std::cout << sac.piocherJeton() << "\n";
        std::cout << sac.piocherJeton() << "\n";
        std::cout << sac.piocherJeton() << "\n";
    }
    catch (JetonException& e)
    {
        std::cout << e.getInfo() << "\n";
    }
    
    return 0;
}

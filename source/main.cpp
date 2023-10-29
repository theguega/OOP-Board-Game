#include <iostream>
#include "jetons.hpp"

int main(int argc, const char * argv[]) {
    Jetons jeton1(CouleurJeton::RUBIS);
    Jetons jeton2(CouleurJeton::SAPHIR);
    std::cout<<jeton1<<std::endl;
    return 0;
}

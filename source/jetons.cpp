#include "jetons.hpp"

std::ostream& operator<<(std::ostream& f, const Jetons& jeton) {
    f<<jeton.getCouleur();
    return f;
};
#include "jetons.hpp"

std::initializer_list<CouleurJeton> CouleursJeton = { CouleurJeton::RUBIS, CouleurJeton::SAPHIR, CouleurJeton::ÉMERAUDE, CouleurJeton::ONYX, CouleurJeton::DIAMANT, CouleurJeton::OR, CouleurJeton::PERLE };

std::string toString(CouleurJeton c)
{
    switch (c)
    {
    case CouleurJeton::RUBIS: return "Rubis";
    case CouleurJeton::SAPHIR: return "Saphir";
    case CouleurJeton::ONYX: return "Onyx";
    case CouleurJeton::ÉMERAUDE: return "Emeraude";
    case CouleurJeton::DIAMANT: return "Diamant";
    case CouleurJeton::OR: return "Or";
    case CouleurJeton::PERLE: return "Perle";
    default: throw JetonException("Couleur inconnue");
    }
}

std::ostream& operator<<(std::ostream& f, CouleurJeton c)
{
    return f << toString(c);
}

std::ostream& operator<< (std::ostream& f, const Jetons& jeton) {
    f << jeton.getCouleur();
    return f;
}
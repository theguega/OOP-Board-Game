#include <QWidget>
#include <jetons.hpp>
#include <vueJeton.h>
#include <array>


#ifndef VUEPLATEAU_H
#define VUEPLATEAU_H

class vuePlateau : public QWidget{
private:
    //Choix entre pointeur et référence ?
    Sac &sac;
    Plateau &plateau;
    std::array<const vueJeton, 25> listeJetons;
public:
    vuePlateau(Plateau &plateau);
    vueJeton* recupereBouton(Jetons* jeton);
    void remplirPlateau();

};

#endif // VUEPLATEAU_H

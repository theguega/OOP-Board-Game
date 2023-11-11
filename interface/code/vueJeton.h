#include <QWidget>
#include <QPushButton>
#include <jetons.hpp>

#ifndef VUEJETON_H
#define VUEJETON_H

class position{
private:
    int x;
    int y;
public:
    position(int x, int y) : x(x), y(y){}
    getx() const {return x;}
    gety() const {return y;}
};



class vueJeton : public QPushButton{
    Q_OBJECT
private:
    //récupère l'adresse du jeton auquel vueJeton est reliée
    Jeton* jeton;
public:
    vueJeton(QWidget* parent = nullptr, type couleur, Jeton* jeton);
    void apparaitre(position pos) const;
    void disparaitre() const;
    Jeton* getJeton() const {return jeton;}
};

#endif // VUEJETON_H

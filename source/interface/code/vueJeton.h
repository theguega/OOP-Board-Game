#ifndef VUEJETON_H
#define VUEJETON_H

#include <QWidget>
#include <QPushButton>
#include <Qpainter>
#include "back-end/jetons.hpp"

class position{
private:
    int x;
    int y;
public:
    position(int x, int y) : x(x), y(y){}
    int getx() const {return x;}
    int gety() const {return y;}
};

class vueJeton : public QPushButton{
    Q_OBJECT
private:
    //recupere l'adresse du jeton auquel vueJeton est reliee
    //Jeton* jeton;
    bool estVisible;
    int rad;
    bool afficherCroix;
    Jeton* jeton;
    QColor Qcouleur;
    QColor QcouleurClair;
    QColor couleurContour;
public:
    vueJeton(QWidget* parent = nullptr, int rad = 0, Jeton* jeton = nullptr);
    void apparaitre();
    void disparaitre();
    bool getEstVisible();
    void changeAfficherCroix();
    void enleverCroix();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // VUEJETON_H

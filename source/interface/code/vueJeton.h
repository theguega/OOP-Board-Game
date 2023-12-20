#ifndef VUEJETON_H
#define VUEJETON_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
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
    bool estVisible;
    int rad;
    bool afficherCroix;
    const Jeton* jeton;
    QColor Qcouleur;
    QColor QcouleurClair;
    QColor couleurContour;
    position* pos;
public:
    vueJeton(QWidget* parent = nullptr, int rad = 0, const Jeton* jeton = nullptr, position* p = nullptr);
    void apparaitre();
    void disparaitre();
    bool getEstVisible();
    void changeAfficherCroix();
    void enleverCroix();
    position* getPosition(){return pos;}
    void setJeton(const Jeton* j){jeton = j;}
    const Jeton* getJeton(){return jeton;}
    ~vueJeton(){delete pos;}
protected:
    void paintEvent(QPaintEvent *event);
};

class vueJetonJoueur : public QWidget{
private:
    int n;
    int tailleJeton;

    QColor Qcouleur;
    QColor QcouleurClair;
    QColor couleurContour;

    Jeton* jeton;
public:
    vueJetonJoueur(QWidget* parent, Jeton* j, int tj, int n);
    void setN(int n){this->n = n;}
protected:
    void paintEvent(QPaintEvent *event);
};

QColor couleurEnQ(std::string c);

#endif // VUEJETON_H

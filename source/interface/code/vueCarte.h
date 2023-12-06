#ifndef VUECARTE_H
#define VUECARTE_H

#include <QWidget>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QEvent>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include <string>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "vueJeton.h"
#include "back-end/carte.hpp"

class carteVisuel : public QWidget{ //Gere le visuel de la carte
    Q_OBJECT
private:
    //Carte* carte;
    int h;
    int l;
    QColor triangleColor;
    int numero = 0;
protected:
    void paintEvent(QPaintEvent *) override;
public:
    carteVisuel(QWidget* parent = nullptr, int hauteur = 0, int largeur = 0, QColor couleur = Qt::blue);
};

class carteInfo : public QWidget{ //Gere les infos de la carte
    Q_OBJECT
private:
    int h;
    int l;
    std::string texteInfo;
    QLabel* labelInfo;
    QVBoxLayout* layout;
protected:
    void paintEvent(QPaintEvent *event);
public:
    carteInfo(QWidget* parent, int hauteur, int largeur, std::string texte);
};

class vueCarte : public QStackedWidget{ //Gere la carte elle même
    Q_OBJECT
private:
    int h;
    int l;

    position* pos = nullptr;
    QColor triangleColor = Qt::blue;

    int numero = 0;

    std::string texteInfo = "Ceci est un test";
    carteInfo* info;
    carteVisuel* visu;

    bool estAffiche = true;
    bool affichageInfo = true;

    Carte* carte;
protected:
    bool event(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            qDebug() << "Clic gauche detecte sur le widget.";
        } else if (event->button() == Qt::RightButton) {
            qDebug() << "Clic droit detecte sur le widget.";
        }
    }
public:
    vueCarte(QWidget* parent = nullptr, int hauteur = 0, int largeur = 0, Carte* carte = nullptr);
    void setPosition(position* pos){this->pos = pos;}
    position* getPosition(){return pos;}
    void cacherInfo(){affichageInfo = false;}
    void afficherInfo(){affichageInfo = true;}
};

#endif // VUECARTE_H

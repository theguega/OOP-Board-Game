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
#include "back-end/espacejeux.hpp"

class carteVisuel : public QWidget{ //Gere le visuel de la carte
    Q_OBJECT
private:
    const Carte* carte;
    int h;
    int l;
protected:
    void paintEvent(QPaintEvent *) override;
public:
    carteVisuel(QWidget* parent = nullptr, int hauteur = 0, int largeur = 0, const Carte* carte = nullptr);
    void setCarte(const Carte* c){carte = c;}
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
    void setInfo(std::string texte){labelInfo->setText(QString::fromStdString(texte));}
};

class vueCarte : public QStackedWidget{ //Gere la carte elle même
    Q_OBJECT
private:
    int h;
    int l;

    position* pos = nullptr;
    QColor triangleColor = Qt::blue;

    int numero = 0;

    std::string texteInfo;
    carteInfo* info;
    carteVisuel* visu;

    bool estAffiche = true;
    bool affichageInfo = true;

    const Carte* carte;
protected:
    bool event(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            qDebug() << "Clic gauche detecte sur le widget.";
            emit carteAchetee(pos);
        } else if (event->button() == Qt::RightButton) {
            qDebug() << "Clic droit detecte sur le widget.";
            emit carteReservee(pos);
        }
    }
public:
    vueCarte(QWidget* parent = nullptr, int hauteur = 0, int largeur = 0, const Carte* carte = nullptr);
    void setPosition(position* pos){this->pos = pos;}
    position* getPosition(){return pos;}
    void cacherInfo(){affichageInfo = false;}
    void afficherInfo(){affichageInfo = true;}
    void setCarte(const Carte* c){carte = c; visu->setCarte(c); info->setInfo(c->getInfos()); update();}
    const Carte* getCarte(){return carte;}
signals:
    void carteReservee(position* position);
    void carteAchetee(position* position);
};

class vuePaquet : public QWidget{
    Q_OBJECT
private:
    int h;
    int l;
    TypeCarte niveau;
    Pioche* pioche;

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            qDebug() << "Clic gauche detecte sur le widget.";
        }
    }
    void paintEvent(QPaintEvent* event);
public:
    vuePaquet(Pioche& p, int hauteur=0, int largeur=0, QWidget* parent = nullptr): QWidget(parent), h(hauteur), l(largeur), niveau(p.getTypeCarte()), pioche(&p){setFixedSize(l, h);}
    int getNbCartes(){return pioche->getNbCartes();}
};

#endif // VUECARTE_H

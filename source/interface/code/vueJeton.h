#ifndef VUEJETON_H
#define VUEJETON_H

#include <QWidget>
#include <QPushButton>
#include <Qpainter>

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
public:
    vueJeton(QWidget* parent = nullptr, int rad = 0);
    void apparaitre();
    void disparaitre();
    bool getEstVisible();
    void changeAfficherCroix();
    void enleverCroix();
protected:
    void paintEvent(QPaintEvent *event) override {
        QPushButton::paintEvent(event); // Appeler la methode paintEvent de la classe de base pour dessiner le bouton

        if (afficherCroix) {
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(Qt::white);

            // Dessiner une croix qui prend tout le cercle et est centree avec une rotation de 45 degres
            painter.save(); // Sauvegarder l'etat actuel du QPainter
            painter.translate(width() / 2, height() / 2); // Translation pour le centre du bouton
            painter.rotate(45); // Rotation de 45 degres
            painter.drawLine(-width() / 2, 0, width() / 2, 0); // Horizontal
            painter.drawLine(0, -height() / 2, 0, height() / 2); // Vertical
            painter.restore(); // Restaurer l'etat precedent du QPainter
        }
    }
};

#endif // VUEJETON_H

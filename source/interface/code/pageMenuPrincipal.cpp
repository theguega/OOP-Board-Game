#include "pageMenuPrincipal.h"
#include <QPainter>



pageMenuPrincipal::pageMenuPrincipal(QWidget *parent) : QWidget(parent) {

    boutonDemarrer = new QPushButton("Commencer une nouvelle partie");
    boutonSauvegarde = new QPushButton("Demarrer une partie sauvegardee");
    boutonBibli = new QPushButton("Scores");
    boutonQuitter = new QPushButton("Quitter");

    coucheMP = new QVBoxLayout(this);
    coucheMP->addWidget(boutonDemarrer);
    coucheMP->addWidget(boutonSauvegarde);
    coucheMP->addWidget(boutonBibli);
    coucheMP->addWidget(boutonQuitter);

    setLayout(coucheMP);
}

pageMenuPrincipal::~pageMenuPrincipal() {
    delete boutonDemarrer;
    delete boutonSauvegarde;
    delete boutonBibli;
    delete boutonQuitter;
    delete coucheMP;
}

void pageMenuPrincipal::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QColor("#252525")); //On definie la couleur du pinceau en blanc

    painter.drawPolygon(rect()); //On colorie le polygone

}


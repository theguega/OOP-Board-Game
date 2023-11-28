#include <QApplication>
#include <QWidget>
#include <QDebug>
#include "vueCarte.h"
#include "pageCreation.h"
#include "vueJeton.h"
#include "vuePlateau.h"
#include "toutesPages.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    /*vueCarte carte = vueCarte(nullptr);
    carte.show();*/

    /*pageCreation page = pageCreation(nullptr);
    page.show();*/

    /*QWidget* widget = new QWidget;

    vueJeton* jeton = new vueJeton(nullptr);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(jeton);

    widget -> setLayout(layout);

    widget->show();*/

    /*vuePlateau* plateau = new vuePlateau(nullptr, 500, 500);
    plateau -> show();*/

    toutesPages* page = new toutesPages(nullptr, &app);
    page -> show();

    return app.exec();
}

#include "back-end/controller.hpp"

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QtSql>

#include "back-end/exception.hpp"

#include "interface/code/vueCarte.h"
#include "interface/code/pageCreation.h"
#include "interface/code/vueJeton.h"
#include "interface/code/vuePlateau.h"
#include "interface/code/toutesPages.h"
#include <iostream>

int main(int argc, char * argv[]) {
    int choix;
    std::cout<<"\033[1;33mMode Console (1) ou Graphique (2) ?\033[0m\n";
    //std::cin>>choix;
    choix=2;
    if (choix==1) {
        try {
            Controller control;
            if(control.getStatutPartie()=="New")
                control.lancerPartie();
            control.jouer();
        } catch (SplendorException& e) {qWarning() << e.getInfo() ;};
        return 0;
    } else {
        QApplication app(argc, argv);
        toutesPages* page = new toutesPages(nullptr, &app);
        page->show();
        return app.exec();
    }
}

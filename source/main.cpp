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



//#########################################
//###### Partie avec l'application Qt #####
//#########################################


int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    toutesPages* page = new toutesPages(nullptr, &app);
    page->show();
    return app.exec();
}











//####################################
//###### Partie en mode Terminal #####
//####################################


/*int main(void) {
    try {
        Controller control;
        if(control.getStatutPartie()=="New")
            control.lancerPartie();
        control.jouer();
    } catch (SplendorException& e) {qWarning() << e.getInfo() ;};

    return 0;
}*/

#ifndef TOUTESPAGES_H
#define TOUTESPAGES_H

#include <QStackedWidget>
#include "pageSauvegarde.h"
#include "pageJeu.h"
#include "pageMenuPrincipal.h"

class toutesPages : public QStackedWidget {
    Q_OBJECT
private:
    pageMenuPrincipal* menuPrincipal;
    pageJeu* jeu;
    pageSauvegarde* scrollSauvegardes;
public:
    toutesPages(QWidget* parent, QApplication* app);
    fermerFenetre(){this -> hide();}
    ~toutesPages() = default;
};

#endif //TOUTESPAGES_H

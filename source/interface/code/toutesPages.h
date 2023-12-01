#ifndef TOUTESPAGES_H
#define TOUTESPAGES_H

#include <QStackedWidget>
#include "pageBibliotheque.h"
#include "pageSauvegarde.h"
#include "pageJeu.h"
#include "pageMenuPrincipal.h"


class toutesPages : public QStackedWidget {
    Q_OBJECT
private:
    pageMenuPrincipal* menuPrincipal;
    pageJeu* jeu;
    pageSauvegarde* scrollSauvegardes;
    pageBibliotheque* bibli;
public:
    toutesPages(QWidget* parent, QApplication* app);
    void fermerFenetre(){this -> hide();}
    ~toutesPages() = default;
};

#endif //TOUTESPAGES_H

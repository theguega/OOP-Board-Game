#include <QStackedWidget>
#include "pageSauvegarde.h"
#include "pageJeu.h"
#include "pageMenuPrincipal.h"

#ifndef TOUTESPAGES_H
#define TOUTESPAGES_H

class toutesPages : public QStackedWidget {
    Q_OBJECT
private:

public:
    toutesPages(pageMenuPrincipal* menuPrincipal, pageJeu* jeu, pageSauvegarde* scrollSauvegardes, QApplication* app);
    ~toutesPages() = default;
};

#endif //TOUTESPAGES_H

#include <QStackedWidget>
#include "pagePrincipale.h"
#include "pageSauvegarde.h"
#include "pageJeu.h"
#include "pageMenuPrincipal.h"

class toutesPages : public QStackedWidget {
private:

public:
    toutesPages(pageMenuPrincipal& menuPrincipal, pageJeu& jeu, pageSauvegarde& scrollSauvegardes, QApplication& app);
};

#ifndef TOUTESPAGES_H
#define TOUTESPAGES_H

#include <QStackedWidget>
#include "pageBibliotheque.h"
#include "pageJeu.h"
#include "pageMenuPrincipal.h"


class toutesPages : public QStackedWidget {
    Q_OBJECT
private:
    pageMenuPrincipal* menuPrincipal;
    pageJeu* jeu;
    pageBibliotheque* bibli;
    popUpValider* pop; //PopUp pour valider les choix de l'utilisateur
public:
    toutesPages(QWidget* parent, QApplication* app);
    void fermerFenetre(){this -> hide();}
    ~toutesPages() = default;
public slots:
    void boutonOuiPresse();
    void boutonNonPresse() { //Connecte le bouton non du PopUpValider
        pop -> hide();
    }
signals:
    void fermerToutesPages();
};

#endif //TOUTESPAGES_H

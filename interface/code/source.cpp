#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScreen>
#include <QLabel>
#include <QPixmap>
#include <QStackedWidget>
#include <QScrollArea>
#include "pagePrincipale.h"
#include "pageSauvegarde.h"
#include "pageJeu.h"
#include "pageMenuPrincipal.h"
#include "toutesPages.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //QScreen *ecran = QGuiApplication::primaryScreen();
    //QSize tailleEcran = ecran->availableGeometry().size();

    /*int tailleLargeur = tailleEcran.width() / 2;
    int tailleHauteur = tailleEcran.height() / 2;*/

    QWidget pagePrincipale;
    pagePrincipale.setWindowTitle("Splenduor Duel");

    // Création des pages directement dans la fonction
    pageMenuPrincipal menuPrincipal;
    pageJeu jeu;
    pageSauvegarde scrollSauvegardes;

    // Ajout des pages à toutesPages
    toutesPages pages(&menuPrincipal, &jeu, &scrollSauvegardes, &app);

    QVBoxLayout mainLayout(&pagePrincipale);
    mainLayout.addWidget(&pages);

    pagePrincipale.show();

    return app.exec();
}

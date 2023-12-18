QT += widgets
QT += sql
CONFIG += console

SOURCES += \
    main.cpp \
    interface/code/pageBibliotheque.cpp \
    interface/code/pageCreation.cpp \
    interface/code/pageJeu.cpp \
    interface/code/pageJoueur.cpp \
    interface/code/pageMenuPrincipal.cpp \
    interface/code/pagePrincipale.cpp \
    interface/code/pageSauvegarde.cpp \
    interface/code/popUp.cpp \
    interface/code/toutesPages.cpp \
    interface/code/vueCarte.cpp \
    interface/code/vueJeton.cpp \
    interface/code/vuePlateau.cpp \
    interface/code/vuePyramide.cpp \
    back-end/carte.cpp \
    back-end/controller.cpp \
    back-end/espacejeux.cpp \
    back-end/jetons.cpp \
    back-end/joueur.cpp \
    back-end/partie.cpp \
    back-end/strategy.cpp

HEADERS += \
    interface/code/pageBibliotheque.h \
    interface/code/pageCreation.h \
    interface/code/pageJeu.h \
    interface/code/pageJoueur.h \
    interface/code/pageMenuPrincipal.h \
    interface/code/pagePrincipale.h \
    interface/code/pageSauvegarde.h \
    interface/code/popUp.h \
    interface/code/toutesPages.h \
    interface/code/vueCarte.h \
    interface/code/vueJeton.h \
    interface/code/vuePlateau.h \
    interface/code/vuePyramide.h \
    back-end/carte.hpp \
    back-end/controller.hpp \
    back-end/espacejeux.hpp \
    back-end/jetons.hpp \
    back-end/joueur.hpp \
    back-end/partie.hpp \
    back-end/strategy.hpp \
    back-end/exception.hpp

DISTFILES += \
    gif/200w.gif \
    data/data_carte.sqlite \
    data/save.sqlite \
    data/score.sqlite \
    PROBLEMES.md

QT += widgets
QT += sql

SOURCES += \
    main.cpp \
    interface/code/pageCreation.cpp \
    interface/code/pageJeu.cpp \
    interface/code/pageJoueur.cpp \
    interface/code/pageMenuPrincipal.cpp \
    interface/code/pagePrincipale.cpp \
    interface/code/pageSauvegarde.cpp \
    interface/code/popUp.cpp \
    interface/code/source.cpp \
    interface/code/source2.cpp \
    interface/code/toutesPages.cpp \
    interface/code/vueCarte.cpp \
    interface/code/vueJeton.cpp \
    interface/code/vuePlateau.cpp \
    interface/code/vuePyramide.cpp \
    backend/carte.cpp \
    backend/controller.cpp \
    backend/espacejeux.cpp \
    backend/jetons.cpp \
    backend/joueur.cpp \
    backend/partie.cpp \
    backend/strategy.cpp 

HEADERS += \
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
    backend/carte.hpp \
    backend/controller.hpp \
    backend/espacejeux.hpp \
    backend/jetons.hpp \
    backend/joueur.hpp \
    backend/partie.hpp \
    backend/strategy.hpp 

DISTFILES += \
    data/data_carte.sqlite \
    data/save.sqlite \
    data/score.sqlite
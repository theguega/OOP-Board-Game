#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#ifndef PAGEMENUPRINCIPAL_H
#define PAGEMENUPRINCIPAL_H

class pageMenuPrincipal : public QWidget {
    Q_OBJECT
private:
    QPushButton *boutonDemarrer;
    QPushButton *boutonSauvegarde;
    QPushButton *boutonQuitter;

    QVBoxLayout *coucheMP;

public:
    pageMenuPrincipal(QWidget *parent = nullptr);
    ~pageMenuPrincipal();  // Ajout du destructeur pour libérer la mémoire
    QPushButton* getBoutonQuitter() const { return boutonQuitter; }
    QPushButton* getBoutonSauvegarde() const { return boutonSauvegarde; }
    QPushButton* getBoutonDemarrer() const { return boutonDemarrer; }
};

#endif // PAGEMENUPRINCIPAL_H

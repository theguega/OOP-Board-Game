#ifndef PAGEMENUPRINCIPAL_H
#define PAGEMENUPRINCIPAL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class pageMenuPrincipal : public QWidget {
    Q_OBJECT
private:
    QPushButton *boutonDemarrer;
    QPushButton *boutonSauvegarde;
    QPushButton *boutonBibli;
    QPushButton *boutonQuitter;

    QVBoxLayout *coucheMP;
protected:
    void paintEvent(QPaintEvent *event);

public:
    pageMenuPrincipal(QWidget *parent = nullptr);
    ~pageMenuPrincipal();
    QPushButton* getBoutonQuitter() const { return boutonQuitter; }
    QPushButton* getBoutonSauvegarde() const { return boutonSauvegarde; }
    QPushButton* getBoutonBibli() const { return boutonBibli; }
    QPushButton* getBoutonDemarrer() const { return boutonDemarrer; }
};

#endif // PAGEMENUPRINCIPAL_H

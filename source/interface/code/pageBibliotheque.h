#ifndef PAGEBIBLIOTHEQUE_H
#define PAGEBIBLIOTHEQUE_H

#include <QScrollArea>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class pageBibliotheque : public QScrollArea {
    Q_OBJECT
private:
    QWidget *boutons;
    QVBoxLayout *layoutBibli;
    QPushButton *retourMenuSauv;

public:
    pageBibliotheque(QWidget *parent = nullptr);
    ~pageBibliotheque();
    QPushButton* getRetourMenuSauv(){return retourMenuSauv;}
};

#endif // PAGEBIBLIOTHEQUE_H

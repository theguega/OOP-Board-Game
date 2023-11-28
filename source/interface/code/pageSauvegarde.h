#ifndef PAGESAUVEGARDE_H
#define PAGESAUVEGARDE_H

#include <QScrollArea>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class pageSauvegarde : public QScrollArea {
    Q_OBJECT
private:
    int nSauvegardes;
    QWidget *boutons;
    QVBoxLayout *layoutSauvegardes;

    QPushButton *retourMenuSauv;

public:
    pageSauvegarde(QWidget *parent = nullptr);
    ~pageSauvegarde();
    QPushButton* getRetourMenuSauv(){return retourMenuSauv;}

public slots:
    void demarrerSauvegarde(int idBouton);
};

#endif // PAGESAUVEGARDE_H

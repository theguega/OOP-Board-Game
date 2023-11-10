#include <QScrollArea>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#ifndef PAGESAUVEGARDE_H
#define PAGESAUVEGARDE_H

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
};

#endif // PAGESAUVEGARDE_H

#ifndef PAGEBIBLIOTHEQUE_H
#define PAGEBIBLIOTHEQUE_H

#include <QScrollArea>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QTableView>

class pageBibliotheque : public QScrollArea {
    Q_OBJECT
private:
    QWidget *boutons;
    QVBoxLayout *layoutBibli;
    QPushButton *retourMenu;
    QTableView *tableView;

public:
    pageBibliotheque(QWidget *parent = nullptr);
    ~pageBibliotheque();
    QPushButton* getRetourMenu(){return retourMenu;}
    QTableView* getTableView(){return tableView;}
};

#endif // PAGEBIBLIOTHEQUE_H

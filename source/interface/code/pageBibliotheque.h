#ifndef PAGEBIBLIOTHEQUE_H
#define PAGEBIBLIOTHEQUE_H

#include <QScrollArea>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QHeaderView>
#include <QTableView>




class pageBibliotheque : public QWidget{
    Q_OBJECT
private:
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

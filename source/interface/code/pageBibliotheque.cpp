#include "pageBibliotheque.h"




pageBibliotheque::pageBibliotheque(QWidget *parent) : QWidget(parent){
    layoutBibli = new QVBoxLayout(this);

    retourMenu = new QPushButton("Retour Menu Principal", this);
    layoutBibli->addWidget(retourMenu);

    tableView = new QTableView(this);
    layoutBibli->addWidget(tableView);

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data/score.sqlite");

    if (!db.open()) {
        qDebug() << "Erreur lors de l'ouverture de la base de donnees";
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM score");
    tableView->setModel( model );
    tableView->verticalHeader()->setVisible(false);
    tableView->show();
}

pageBibliotheque::~pageBibliotheque() {
    delete retourMenu;
    delete layoutBibli;
    delete tableView;
}

#include "pageBibliotheque.h"

pageBibliotheque::pageBibliotheque(QWidget *parent) : QScrollArea(parent){
    boutons = new QWidget(this);
    layoutBibli = new QVBoxLayout(boutons);

    retourMenu = new QPushButton("Retour Menu Principal", this);
    layoutBibli->addWidget(retourMenu);

    tableView = new QTableView(this);
    layoutBibli->addWidget(tableView);

    tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layoutBibli->setSizeConstraint(QLayout::SetFixedSize);
    setWidget(boutons);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data/score.sqlite");

    if (!db.open()) {
        qDebug() << "Erreur lors de l'ouverture de la base de donnees";
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM score");
    tableView->setModel( model );
    tableView->show();
}

pageBibliotheque::~pageBibliotheque() {
    delete retourMenu;
    delete layoutBibli;
    delete tableView;
    delete boutons;
}

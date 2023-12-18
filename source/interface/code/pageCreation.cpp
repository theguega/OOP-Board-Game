#include <QComboBox>
#include <QOverload>
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include "pageCreation.h"

pageCreation::pageCreation(QWidget *parent) : QWidget(parent){
    choixPossibles1 = new QComboBox;
    choixPossibles2 = new QComboBox;    

    choix1 << "Nouvelle Personne" << "IA 1" << "IA 2";
    choix2 << "Nouvelle Personne" << "IA 1" << "IA 2";

    choixPossibles1 -> addItems(choix1);
    choixPossibles2 -> addItems(choix2);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data/score.sqlite");
    if (!db.open()) {
        qDebug() << "Erreur lors de l'ouverture de la base de données:" << db.lastError().text();
        throw std::runtime_error("Erreur lors de l'ouverture de la base de données: " + db.lastError().text().toStdString());
    }

    QSqlQuery query("SELECT * FROM score");
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        throw std::runtime_error("Erreur lors de l'ouverture de la base de données: " + db.lastError().text().toStdString());
    }

    while (query.next()) {
        // Récupération du nom depuis la première colonne
        QString nom = query.value(1).toString();
        choixPossibles1 -> addItem(nom);
        choixPossibles2 -> addItem(nom);
    }
    db.close();

    nom1Edit = new QLineEdit;
    nom2Edit = new QLineEdit;

    boutonValider = new QPushButton("Valider");
    retourMenu = new QPushButton("Retour Menu Principal");

    layout = new QVBoxLayout;
    layout -> addWidget(choixPossibles1);
    layout -> addWidget(nom1Edit);
    layout -> addWidget(choixPossibles2);
    layout -> addWidget(nom2Edit);
    layout -> addWidget(boutonValider);
    layout -> addWidget(retourMenu);

    setLayout(layout);

    index1 = 0;
    index2 = 0;

    QObject::connect(choixPossibles1, QOverload<int>::of(&QComboBox::activated), this, &pageCreation::comboBox1Active);
    QObject::connect(choixPossibles2, QOverload<int>::of(&QComboBox::activated), this, &pageCreation::comboBox2Active);
    QObject::connect(boutonValider, &QPushButton::clicked, this, &pageCreation::valider);

    pop = new popUpValider(nullptr, "valider");
    QObject::connect(pop -> getBoutonOui(), &QPushButton::clicked, this, &pageCreation::boutonOuiPresse);
    QObject::connect(pop -> getBoutonNon(), &QPushButton::clicked, this, &pageCreation::boutonNonPresse);
    pop -> hide();
}

void pageCreation::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QColor("#252525")); //On definie la couleur du pinceau en blanc

    painter.drawPolygon(rect()); //On colorie le polygone

}


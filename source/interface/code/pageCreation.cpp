#include <QComboBox>
#include <QOverload>
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include "pageCreation.h"

pageCreation::pageCreation(QWidget *parent) : QWidget(parent){

    choixPossibles1 = new QComboBox;
    choixPossibles2 = new QComboBox;

    choix1 << "Nouveaux Joueur";
    choix2 << "Nouveaux Joueur";

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

    pop = new popUpValider(nullptr, "valider", "", "tuto");
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

void pageCreation::boutonOuiPresse() { //Connecte le bouton oui du PopUpValider

    pop->hide();

    type type_tmp1 = type::HUMAIN;
    type type_tmp2 = type::HUMAIN;

    //Joueur 1 :
    if (index1==0) {
        nom1 = nom1Edit->text();
    } else {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("data/score.sqlite");
        if (!db.open()) {
            qDebug() << "Erreur lors de l'ouverture de la base de données:" << db.lastError().text();
            throw std::runtime_error("Erreur lors de l'ouverture de la base de données: " + db.lastError().text().toStdString());
        }

        QSqlQuery query("SELECT * FROM score LIMIT 1 OFFSET " + QString::number(index1-1));
        if (!query.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
            throw std::runtime_error("Erreur lors de l'ouverture de la base de données: " + db.lastError().text().toStdString());
        }

        while (query.next()) {
            // Récupération du nom depuis la première colonne
            nom1 = query.value(1).toString();
        }
        db.close();

        if(nom1=="Alain Telligence" || nom1=="Al Gorythme")
            type_tmp1 = type::IA;

    }

    //Joueur 2 :
    if (index2==0) {
        nom2 = nom2Edit->text();
    } else {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("data/score.sqlite");
        if (!db.open()) {
            qDebug() << "Erreur lors de l'ouverture de la base de données:" << db.lastError().text();
            throw std::runtime_error("Erreur lors de l'ouverture de la base de données: " + db.lastError().text().toStdString());
        }

        QSqlQuery query("SELECT * FROM score LIMIT 1 OFFSET " + QString::number(index2-1));
        if (!query.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
            throw std::runtime_error("Erreur lors de l'ouverture de la base de données: " + db.lastError().text().toStdString());
        }

        while (query.next()) {
            // Récupération du nom depuis la première colonne
            nom2 = query.value(1).toString();
        }
        db.close();

        if(nom2=="Alain Telligence" || nom2=="Al Gorythme")
            type_tmp2 = type::IA;
    }

    qDebug() << "Texte saisi : " << nom1 << " " << nom2;
    this -> hide();
    jeu = new pageJeu("New", nom1, type_tmp1, nom2, type_tmp2);
    jeu -> show();
    emit fermerToutesPages();
}

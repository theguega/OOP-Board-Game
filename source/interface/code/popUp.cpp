#include "popUp.h"

popUpValider::popUpValider(QWidget* parent, std::string info) : QWidget(parent){ //PopUp pour faire des validations
    oui = new QPushButton("oui"); //Bouton Oui
    non = new QPushButton("non"); //Bouton Non

    std::string tempPhrase = texte1 + info + texte3; //Def la question qui sera poser
    this->info = new QLabel;
    this->info->setText(QString::fromStdString(tempPhrase)); //Def le texte sur le QLabel

    boutonLayout = new QHBoxLayout;
    layout = new QVBoxLayout;

    // Ajout du QLabel pour afficher le GIF
    QLabel *gifLabel = new QLabel(this);
    gifLabel->setGeometry(50, 50, 300, 200); // Définit la taille et la position du label

    // Charge et affiche le GIF en utilisant QMovie
    QMovie *movie = new QMovie("gif/200w.gif"); // Remplacez par le chemin de votre GIF
    gifLabel->setMovie(movie); // Définit le film (movie) sur le QLabel



    boutonLayout->addWidget(oui);
    boutonLayout->addWidget(non);

    layout -> addWidget(gifLabel);

    movie->start(); // Démarre l'animation du GIF

    layout -> addWidget(this->info);
    layout -> addLayout(boutonLayout);
    layout -> setAlignment(Qt::AlignCenter);

    setLayout(layout);
}

popUpInfo::popUpInfo(QWidget* parent, std::string info) : QWidget(parent){ //PopUp pour montrer des infos
    this->info = new QLabel;
    this->info->setText(QString::fromStdString(info));

    layout = new QVBoxLayout;
    layout -> addWidget(this->info);

    setLayout(layout);
}

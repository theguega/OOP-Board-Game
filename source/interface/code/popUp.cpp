#include "popUp.h"

popUpValider::popUpValider(QWidget* parent, std::string info, std::string info2) : QWidget(parent){ //PopUp pour faire des validations
    oui = new QPushButton("oui"); //Bouton Oui
    non = new QPushButton("non"); //Bouton Non
    std::string tempPhrase = texte1 + info + texte3; //Def la question qui sera poser
    this->info = new QLabel;
    this->info2 = new QLabel;
    this->info->setText(QString::fromStdString(tempPhrase)); //Def le texte sur le QLabel
    this->info2->setText(QString::fromStdString(info2));
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

<<<<<<< HEAD
    layout -> addWidget(this->info2);
=======
    layout -> addWidget(gifLabel);

    movie->start(); // Démarre l'animation du GIF

>>>>>>> 2c94811a55c124851fb6b68406aa16ba15ad6615
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



modalPopup::modalPopup(QWidget* parent, const QString& info, const QString& info2)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* infoLabel = new QLabel(info, this);
    layout->addWidget(infoLabel);

    if (!info2.isEmpty())
    {
        QLabel* infoLabel2 = new QLabel(info2, this);
        layout->addWidget(infoLabel2);
    }

    ouiButton = new QPushButton("Oui", this);
    nonButton = new QPushButton("Non", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(ouiButton);
    buttonLayout->addWidget(nonButton);

    layout->addLayout(buttonLayout);

    connect(ouiButton, &QPushButton::clicked, this, &modalPopup::handleOuiButtonClicked);
    connect(nonButton, &QPushButton::clicked, this, &modalPopup::reject);

    setLayout(layout);
}


void modalPopup::handleOuiButtonClicked()
{
    // Perform actions specific to the "Oui" button click.
    accept(); // Close the dialog.
}

#include "popUp.h"

popUpValider::popUpValider(QWidget* parent, std::string info, std::string info2, std::string gif) : QWidget(parent) {
    oui = new QPushButton("oui"); // Bouton Oui
    non = new QPushButton("non"); // Bouton Non
    std::string tempPhrase = texte1 + info + texte3; // Définit la question qui sera posée
    this->info = new QLabel;
    this->info2 = new QLabel;
    this->info->setText(QString::fromStdString(tempPhrase)); // Set text on QLabel
    this->info->setAlignment(Qt::AlignCenter); // Center-align the text

    this->info2->setText(QString::fromStdString(info2));
    this->info2->setAlignment(Qt::AlignCenter); // Center-align the text
    boutonLayout = new QHBoxLayout;
    layout = new QVBoxLayout;

    // Ajout du QLabel pour afficher le GIF
    QLabel *gifLabel = new QLabel(this);
    gifLabel->setAlignment(Qt::AlignCenter); // Centre le label
    layout->addWidget(gifLabel); // Ajoute d'abord le label GIF au layout

    // Charge et affiche le GIF en utilisant QMovie
    QString gif_path = QString::fromStdString("gif/") + QString::fromStdString(gif) + QString::fromStdString(".gif");
    QMovie *movie = new QMovie(gif_path); // Remplacez par le chemin de votre GIF
    gifLabel->setMovie(movie); // Définit le film (movie) sur le QLabel

    boutonLayout->addWidget(oui);
    boutonLayout->addWidget(non);

    layout->addWidget(this->info2);
    layout->addWidget(this->info);

    layout->addLayout(boutonLayout);

    layout->setAlignment(Qt::AlignCenter);

    setLayout(layout);

    movie->start(); // Démarre l'animation du GIF
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


popUpChoixCouleur::popUpChoixCouleur(Controller* control, QWidget* parent) : QDialog(parent), control(control) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    signalMapper = new QSignalMapper(this);
    label = new QLabel("La capacité de la carte permet d'associer son bonus à la couleur de votre choix. Veuillez choisir une couleur parmi celles disponibles :", this);
    label->setWordWrap(true);
    layout->addWidget(label);
    // Example colors
    QStringList colors = {"blanc", "bleu", "rouge", "vert", "noir", "perle"};

    for (const QString& color : colors) {
        int value = 0;
        if (StringToCouleur(color.toStdString()) == Couleur::BLANC) {
            value = control->getJoueurCourant().getNbCartes(Couleur::BLANC);
        } else if (StringToCouleur(color.toStdString()) == Couleur::BLEU) {
            value = control->getJoueurCourant().getNbCartes(Couleur::BLEU);
        } else if (StringToCouleur(color.toStdString()) == Couleur::ROUGE) {
            value = control->getJoueurCourant().getNbCartes(Couleur::ROUGE);
        } else if (StringToCouleur(color.toStdString()) == Couleur::VERT) {
            value = control->getJoueurCourant().getNbCartes(Couleur::VERT);
        } else if (StringToCouleur(color.toStdString()) == Couleur::NOIR) {
            value = control->getJoueurCourant().getNbCartes(Couleur::NOIR);
        } else if (StringToCouleur(color.toStdString()) == Couleur::PERLE) {
            value = control->getJoueurCourant().getNbCartes(Couleur::PERLE);
        }
        if (value != 0) {
            QRadioButton* radioButton = new QRadioButton(color, this);
            layout->addWidget(radioButton);
            connect(radioButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(radioButton, color);
        }
    }

    QPushButton* okButton = new QPushButton("OK", this);
    layout->addWidget(okButton);
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(colorSelected(QString)));
}

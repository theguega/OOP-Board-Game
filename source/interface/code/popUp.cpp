#include "popUp.h"
#include "vueJeton.h"
#include <QFontDatabase>

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

popUpVictoire::popUpVictoire(QWidget* parent, std::string pseudo) : QWidget(parent) {
    std::string tempPhrase = "Le joueur " + pseudo + " a gagné SplendorDuel !";
    this->info = new QLabel;
    this->info->setText(QString::fromStdString(tempPhrase)); // Set text on QLabel
    this->info->setAlignment(Qt::AlignCenter); // Center-align the text

    int fontId = QFontDatabase::addApplicationFont(":/font/fonts/MedievalSharp-Regular.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont customFont(fontFamilies.at(0), 20);

    // Appliquer la police personnalisée au QLabel
    this->info->setFont(customFont);


    layout = new QVBoxLayout;

    // Ajout du QLabel pour afficher le GIF
    QLabel *gifLabel = new QLabel(this);
    gifLabel->setAlignment(Qt::AlignCenter); // Centre le label

    // Charge et affiche le GIF en utilisant QMovie
    QString gif_path = QString::fromStdString("gif/victoire.gif");
    QMovie *movie = new QMovie(gif_path); // Remplacez par le chemin de votre GIF
    gifLabel->setMovie(movie); // Définit le film (movie) sur le QLabel

    layout->addWidget(gifLabel);
    layout->addWidget(this->info);

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


/*popUpChoixCouleur::popUpChoixCouleur(Controller* control, QWidget* parent) : QDialog(parent), control(control) {
    layout = new QVBoxLayout;
    label = new QLabel("La capacité de la carte permet d'associer son bonus à la couleur de votre choix. Veuillez choisir une couleur parmi celles disponibles :", this);
    labelCoul = new QLabel("", this);
    label->setWordWrap(true);
    labelCoul->setWordWrap(true);
    layout->addWidget(label);
    layoutBoutons = new QHBoxLayout;

    for (const auto& color : Couleurs) {
        if(color!= Couleur::PERLE && color != Couleur::OR){
            int value = control->getJoueurCourant().getNbCartes(color);
            if (value != 0) {
                vueJeton* jeton = new vueJeton(nullptr, 40, new Jeton(color), nullptr);
                layoutBoutons->addWidget(jeton);
                QObject::connect(jeton, &vueJeton::clicked, [this, color]() {
                    choixCouleur(color); //Permet d'appeler la fonction boutonClique(int i) lorsque le bouton i est clique
                });
            }
        }
    }
    layout->addLayout(layoutBoutons);
    layout->addWidget(labelCoul);
    boutonValider = new QPushButton("Valider", this);
    layoutBoutons->addWidget(boutonValider);

    // Connecter le signal clicked du bouton "Valider" à la fonction validerCouleur()
    connect(boutonValider, &QPushButton::clicked, this, &popUpChoixCouleur::validerCouleur);
    setLayout(layout);
    setModal(true);
}


void popUpChoixCouleur::validerCouleur() {
    if (coul_select != Couleur::INDT) {
        // Émettre le signal signalCouleurValidee avec la couleur sélectionnée
        emit signalCouleurValidee(coul_select);
        close();
    } else {
        // Gérer le cas où aucune couleur n'est sélectionnée
        qDebug() << "Aucune couleur sélectionnée.";
        // Vous pouvez également afficher un message d'erreur ou effectuer d'autres actions ici
    }
}


void popUpChoixCouleur::choixCouleur(Couleur c){
    if(!aEteClique){
        aEteClique = true;
        coul_select = c;
        setLabelCoul();
        qDebug()<<"marche bien et couleur: "<<toStringCouleur(c);
    }
    aEteClique = false;
}*/

/*popUpChoixJetonAdv::popUpChoixJetonAdv(Controller* control, QWidget* parent) : QDialog(parent), control(control) {
    layout = new QVBoxLayout;
    label = new QLabel("La capacité de la carte permet d'associer son bonus à la couleur de votre choix. Veuillez choisir une couleur parmi celles disponibles :", this);
    label->setWordWrap(true);
    layout->addWidget(label);
    layoutBoutons = new QHBoxLayout;

    for (const auto& color : Couleurs) { //Penser à gérer le cas où l'adversaire n'a plus de cartes
        int value = control->getJoueurAdverse().getNbCartes(color);
        if (value != 0) {
            vueJeton* jeton = new vueJeton(nullptr, 40, new Jeton(color), nullptr);
            layoutBoutons->addWidget(jeton);
            QObject::connect(jeton, &vueJeton::clicked, [this, color]() {
                choixCouleur(color); //Permet d'appeler la fonction boutonClique(int i) lorsque le bouton i est clique
            });
        }
    }

    layout->addLayout(layoutBoutons);
    setLayout(layout);
}

void popUpChoixJetonAdv::choixCouleur(Couleur c){
    if(!aEteClique){
        aEteClique = true;
        qDebug()<<"marche bien et couleur: "<<toStringCouleur(c);
    }
}*/

#include "popUp.h"

popUpValider::popUpValider(QWidget* parent, std::string info) : QWidget(parent){ //PopUp pour faire des validations
    oui = new QPushButton("oui"); //Bouton Oui
    non = new QPushButton("non"); //Bouton Non

    std::string tempPhrase = texte1 + info + texte3; //Def la question qui sera poser
    this->info = new QLabel;
    this->info->setText(QString::fromStdString(tempPhrase)); //Def le texte sur le QLabel

    boutonLayout = new QHBoxLayout;
    layout = new QVBoxLayout;

    boutonLayout->addWidget(oui);
    boutonLayout->addWidget(non);

    layout -> addWidget(this->info);
    layout -> addLayout(boutonLayout);

    setLayout(layout);
}

popUpInfo::popUpInfo(QWidget* parent, std::string info) : QWidget(parent){ //PopUp pour montrer des infos
    this->info = new QLabel;
    this->info->setText(QString::fromStdString(info));

    layout = new QVBoxLayout;
    layout -> addWidget(this->info);

    setLayout(layout);
}

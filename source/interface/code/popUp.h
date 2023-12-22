#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <string>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialog>
#include "back-end/controller.hpp"
#include <QRadioButton>
#include <QDialogButtonBox>


#include <QMovie>

class popUpValider : public QWidget{
    Q_OBJECT
private:
    QPushButton* oui;
    QPushButton* non;
    std::string texte1 = "Voulez-vous ";
    std::string texte3 = " ?";

    QLabel* info; //Recupere les infos a donner dans la question
    QLabel* info2;

    QHBoxLayout* boutonLayout; //Layout avec les boutons
    QVBoxLayout* layout; //Layout principal
public:
    popUpValider(QWidget* parent, std::string info, std::string info2 = "", std::string gif = "quitter");
    QPushButton* getBoutonOui(){return oui;}
    QPushButton* getBoutonNon(){return non;}
};



class popUpInfo : public QWidget{
    Q_OBJECT
private:
    QLabel* info;
    QVBoxLayout* layout;
public:
    popUpInfo(QWidget* parent, std::string info);
};



class modalPopup : public QDialog
{
    Q_OBJECT

public:
    modalPopup(QWidget* parent = nullptr, const QString& info = "", const QString& info2 = "");

    QPushButton* getBoutonOui() const { return ouiButton; }
    QPushButton* getBoutonNon() const { return nonButton; }

private slots:
    void handleOuiButtonClicked();

private:
    QPushButton* ouiButton;
    QPushButton* nonButton;
};




/*class popUpChoixCouleur : public QDialog {
        Q_OBJECT
private:
    Controller* control;
    QLabel* label;
    Couleur coul_select = Couleur::INDT;
    bool aEteClique = false;
    QLabel* labelCoul;
    QPushButton* boutonValider;

    QVBoxLayout* layout;
    QHBoxLayout* layoutBoutons;
public:
    popUpChoixCouleur(Controller* control, QWidget* parent = nullptr);
    void choixCouleur(Couleur c);
    void setLabelCoul(){
        if(coul_select != Couleur::INDT)
            labelCoul->setText(QString::fromStdString("Couleur" + toStringCouleur(coul_select)));
    }

signals:
    void signalCouleurValidee(Couleur couleur);

private slots:
    void validerCouleur();
};*/





/*class popUpChoixJetonAdv : public QDialog {
    Q_OBJECT // Macro nécessaire pour utiliser les signaux et les slots de Qt
private:
    Controller* control;
    QLabel* label;
    Couleur coul_select;
    bool aEteClique = false;

    QVBoxLayout* layout;
    QHBoxLayout* layoutBoutons;

public:
    popUpChoixJetonAdv(Controller* control, QWidget* parent);
    void choixCouleur(Couleur c);
    Couleur getSelect() const {return coul_select;}
};*/






class popUpChoixAssociationBonus : public QDialog {
    Q_OBJECT

public:
    explicit popUpChoixAssociationBonus(Controller* control, QWidget *parent = nullptr) : QDialog(parent), control(control){
        setWindowTitle("Choisissez la couleur avec laquelle vous voulez associer le bonus de la carte");

        QVBoxLayout *layout = new QVBoxLayout(this);

        // Add radio buttons for options
        int valBlanc = control->getJoueurCourant().getNbCartes(Couleur::BLANC);
        int valBleu = control->getJoueurCourant().getNbCartes(Couleur::BLEU);
        int valVert = control->getJoueurCourant().getNbCartes(Couleur::VERT);
        int valRouge = control->getJoueurCourant().getNbCartes(Couleur::ROUGE);
        int valNoir = control->getJoueurCourant().getNbCartes(Couleur::NOIR);

        if (valBlanc != 0) {
            blanc = new QRadioButton("Blanc", this);
            layout->addWidget(blanc);
        }
        if (valBleu != 0) {
            bleu = new QRadioButton("Bleu", this);
            layout->addWidget(bleu);
        }
        if (valVert != 0) {
            vert = new QRadioButton("Vert", this);
            layout->addWidget(vert);
        }
        if (valRouge != 0) {
            rouge = new QRadioButton("Rouge", this);
            layout->addWidget(rouge);
        }
        if (valNoir != 0) {
            noir = new QRadioButton("Noir", this);
            layout->addWidget(noir);
        }

        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &popUpChoixAssociationBonus::accept);
    }

    Couleur getSelectedOption() const {
        if (blanc != nullptr && blanc->isChecked()) return Couleur::BLANC;
        if (bleu != nullptr && bleu->isChecked()) return Couleur::BLEU;
        if (vert != nullptr && vert->isChecked()) return Couleur::VERT;
        if (rouge != nullptr && rouge->isChecked()) return Couleur::ROUGE;
        if (noir != nullptr && noir->isChecked()) return Couleur::NOIR;
        return Couleur::INDT;
    }

private:
    QRadioButton *blanc = nullptr;
    QRadioButton *bleu = nullptr;
    QRadioButton *vert = nullptr;
    QRadioButton *rouge = nullptr;
    QRadioButton *noir = nullptr;
    QDialogButtonBox *buttonBox = nullptr;
    Controller* control = nullptr;
};




class popUpChoixJetonAdv : public QDialog {
    Q_OBJECT

public:
    explicit popUpChoixJetonAdv(Controller* control, QWidget *parent = nullptr) : QDialog(parent), control(control){
        setWindowTitle("Choisissez la couleur du jeton que vous voulez prendre à l'adversaire");

        QVBoxLayout *layout = new QVBoxLayout(this);

        // Add radio buttons for options
        int valBlanc = control->getJoueurAdverse().getNbJetons(Couleur::BLANC);
        int valBleu = control->getJoueurAdverse().getNbJetons(Couleur::BLEU);
        int valVert = control->getJoueurAdverse().getNbJetons(Couleur::VERT);
        int valRouge = control->getJoueurAdverse().getNbJetons(Couleur::ROUGE);
        int valNoir = control->getJoueurAdverse().getNbJetons(Couleur::NOIR);
        int valPerle = control->getJoueurAdverse().getNbJetons(Couleur::PERLE);

        if (valBlanc != 0) {
            blanc = new QRadioButton("Blanc", this);
            layout->addWidget(blanc);
        }
        if (valBleu != 0) {
            bleu = new QRadioButton("Bleu", this);
            layout->addWidget(bleu);
        }
        if (valVert != 0) {
            vert = new QRadioButton("Vert", this);
            layout->addWidget(vert);
        }
        if (valRouge != 0) {
            rouge = new QRadioButton("Rouge", this);
            layout->addWidget(rouge);
        }
        if (valNoir != 0) {
            noir = new QRadioButton("Noir", this);
            layout->addWidget(noir);
        }
        if (valPerle != 0) {
            perle = new QRadioButton("Perle", this);
            layout->addWidget(perle);
        }

        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &popUpChoixJetonAdv::accept);
    }

    Couleur getSelectedOption() const {
        if (blanc != nullptr && blanc->isChecked()) return Couleur::BLANC;
        if (bleu != nullptr && bleu->isChecked()) return Couleur::BLEU;
        if (vert != nullptr && vert->isChecked()) return Couleur::VERT;
        if (rouge != nullptr && rouge->isChecked()) return Couleur::ROUGE;
        if (noir != nullptr && noir->isChecked()) return Couleur::NOIR;
        if (perle != nullptr && perle->isChecked()) return Couleur::PERLE;
        return Couleur::INDT;
    }

private:
    QRadioButton *blanc = nullptr;
    QRadioButton *bleu = nullptr;
    QRadioButton *vert = nullptr;
    QRadioButton *rouge = nullptr;
    QRadioButton *noir = nullptr;
    QRadioButton *perle = nullptr;
    QDialogButtonBox *buttonBox = nullptr;
    Controller* control = nullptr;
};


class popUpChoixJetonRendre : public QDialog {
    Q_OBJECT

public:
    explicit popUpChoixJetonRendre(Controller* control, QWidget *parent = nullptr) : QDialog(parent), control(control){
        int nb_jetons = control-> getJoueurCourant().getNbJetons();
        string titre = "Vous avez plus de 10 jetons ! Nb de jetons:" + std::to_string(nb_jetons);
        setWindowTitle(QString::fromStdString(titre));
        setMinimumSize(400, 0);
        QVBoxLayout *layout = new QVBoxLayout(this);


        int valBlanc = control->getJoueurCourant().getNbJetons(Couleur::BLANC);
        int valBleu = control->getJoueurCourant().getNbJetons(Couleur::BLEU);
        int valVert = control->getJoueurCourant().getNbJetons(Couleur::VERT);
        int valRouge = control->getJoueurCourant().getNbJetons(Couleur::ROUGE);
        int valNoir = control->getJoueurCourant().getNbJetons(Couleur::NOIR);
        int valPerle = control->getJoueurCourant().getNbJetons(Couleur::PERLE);

        if (valBlanc != 0) {
            blanc = new QRadioButton("Blanc", this);
            layout->addWidget(blanc);
        }
        if (valBleu != 0) {
            bleu = new QRadioButton("Bleu", this);
            layout->addWidget(bleu);
        }
        if (valVert != 0) {
            vert = new QRadioButton("Vert", this);
            layout->addWidget(vert);
        }
        if (valRouge != 0) {
            rouge = new QRadioButton("Rouge", this);
            layout->addWidget(rouge);
        }
        if (valNoir != 0) {
            noir = new QRadioButton("Noir", this);
            layout->addWidget(noir);
        }
        if (valPerle != 0) {
            perle = new QRadioButton("Perle", this);
            layout->addWidget(perle);
        }

        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &popUpChoixJetonRendre::accept);
    }

    Couleur getSelectedOption() const {
        if (blanc != nullptr && blanc->isChecked()) return Couleur::BLANC;
        if (bleu != nullptr && bleu->isChecked()) return Couleur::BLEU;
        if (vert != nullptr && vert->isChecked()) return Couleur::VERT;
        if (rouge != nullptr && rouge->isChecked()) return Couleur::ROUGE;
        if (noir != nullptr && noir->isChecked()) return Couleur::NOIR;
        if (perle != nullptr && perle->isChecked()) return Couleur::PERLE;
        return Couleur::INDT;
    }

private:
    QRadioButton *blanc = nullptr;
    QRadioButton *bleu = nullptr;
    QRadioButton *vert = nullptr;
    QRadioButton *rouge = nullptr;
    QRadioButton *noir = nullptr;
    QRadioButton *perle = nullptr;
    QDialogButtonBox *buttonBox = nullptr;
    Controller* control = nullptr;
};
#endif

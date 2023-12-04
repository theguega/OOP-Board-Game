#ifndef PAGECREATION_H
#define PAGECREATION_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStringList>
#include <QPushButton>
#include <QString>
#include <interface/code/popUp.h>
#include <interface/code/pageJeu.h>

class pageCreation : public QWidget{
    Q_OBJECT
private:
    QComboBox* choixPossibles1; //Liste de choix de joueurs possibles
    QComboBox* choixPossibles2; //Liste de choix de joueurs possibles

    QStringList choix1; //Liste de QString avec les différents choix possbiles
    QStringList choix2; //Liste de QString avec les différents choix possbiles

    QLineEdit* nom1Edit; //Ligne permettant de rentrer les pseudos
    QLineEdit* nom2Edit; //Ligne permettant de rentrer les pseudos

    QString nom1; //Récupération des chaines des QLineEdit
    QString nom2; //Récupération des chaines des QLineEdit

    int index1; //Index du QComboBox (savoir quand on ajoute une personne)
    int index2;//Index du QComboBox (savoir quand on ajoute une personne)

    QPushButton* boutonValider; //Permet la validation du choix de création de la partie

    QVBoxLayout* layout; //Layout pour bien tout ranger
    QPushButton *retourMenu; //Bouton pour retourner au Menu Principal

    popUpValider* pop; //PopUp pour valider les choix de l'utilisateur

    pageJeu* jeu; //Future page de Jeu
protected:
    void comboBox1Active(int index){ //Affichage de la récupération du nom pour le joueur
        if (index != 0){
            nom1Edit -> hide();
        }
        else{
            nom1Edit -> show();
        }
        index1 = index;
    }
    void comboBox2Active(int index){ //Affichage de la récupération du nom pour le joueur
        if (index != 0){
            nom2Edit -> hide();
        }
        else{
            nom2Edit -> show();
        }
        index2 = index;
    }
    void valider(){ //Fonction quand le bouton valider est appuyé
        pop -> show();
    }
    void boutonOuiPresse(){ //Connecte le bouton oui du PopUpValider
        pop -> hide();
        if(index1 == 0){
            nom1 = nom1Edit->text();
        }
        if (index2 == 0){
            nom2 = nom2Edit -> text();
        }
        qDebug() << "Texte saisi : " << nom1 << " " << nom2;
        this -> hide();
        jeu -> show();
        emit fermerToutesPages();
    }
    void boutonNonPresse(){ //Connecte le bouton non du PopUpValider
        pop -> hide();
    }
public:
    pageCreation(QWidget* parent = nullptr);
    QPushButton* getRetourMenu(){return retourMenu;}
signals:
    void fermerToutesPages();
};


#endif // PAGECREATION_H

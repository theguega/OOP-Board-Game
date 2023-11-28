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
    QComboBox* choixPossibles1;
    QComboBox* choixPossibles2;

    QStringList choix1;
    QStringList choix2;

    QLineEdit* nom1Edit;
    QLineEdit* nom2Edit;

    QString nom1;
    QString nom2;

    int index1;
    int index2;

    QPushButton* boutonValider;

    QVBoxLayout* layout;
    QPushButton *retourMenu;

    popUpValider* pop;

    QWidget* parent;
    pageJeu* jeu;
public slots:
    void comboBox1Active(int index){
        if (index != 0){
            nom1Edit -> hide();
        }
        else{
            nom1Edit -> show();
        }
        index1 = index;
    }
    void comboBox2Active(int index){
        if (index != 0){
            nom2Edit -> hide();
        }
        else{
            nom2Edit -> show();
        }
        index2 = index;
    }
    void valider(){
        pop -> show();
    }
    void boutonOuiPresse(){
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
    void boutonNonPresse(){
        pop -> hide();
    }
public:
    pageCreation(QWidget* parent = nullptr);
    QPushButton* getRetourMenu(){return retourMenu;}
signals:
    void fermerToutesPages();
};


#endif // PAGECREATION_H

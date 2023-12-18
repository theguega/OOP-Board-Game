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
    popUpValider(QWidget* parent, std::string info, std::string info2 = "");
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


#endif

#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <string>
#include <QHBoxLayout>
#include <QVBoxLayout>

class popUpValider : public QWidget{
    Q_OBJECT
private:
    QPushButton* oui;
    QPushButton* non;
    std::string texte1 = "Voulez-vous ";
    std::string texte3 = " ?";

    QLabel* info;

    QHBoxLayout* boutonLayout;
    QVBoxLayout* layout;
public:
    popUpValider(QWidget* parent, std::string info);
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

#endif // POPUP_H

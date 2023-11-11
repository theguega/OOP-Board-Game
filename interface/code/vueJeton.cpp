#include <QWidget>
#include <QPushButton>
#include <jetons.hpp>
#include <vueJeton.h>

vueJeton::vueJeton(QWidget* parent, Jeton* jeton) : QPushButton(parent), jeton(jeton){

    switch(jeton->getcouleur()){
        case bleuclair:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: lightblue; }");
            break;

        case yellow:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: yellow; }");
            break;

        case vert:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: green; }");
            break;

        case rouge:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: red; }");
            break;

        case noir:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: black }");
            break;

        case argent:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: gray; }");
            break;

        case perle:
            setStyleSheet("QPushButton { border-radius: 50px; background-color: pink; }");
            break;
    }
}

void vueJeton::apparaitre(position pos){
    move((pos.getx(), pos.gety()));
    show();
}
void vueJeton::disparaitre() const{
    hide();
}

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#ifndef PAGEJEU_H
#define PAGEJEU_H

class pageJeu : public QWidget {
    Q_OBJECT
private:
    QPushButton *retourMenu;
    QVBoxLayout *coucheJ;

public:
    pageJeu(QWidget *parent = nullptr);
    void ajoutWidget(QWidget *objet);
    QPushButton* getRetourMenu(){return retourMenu;}
    ~pageJeu();
};

#endif // PAGEJEU_H


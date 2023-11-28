#ifndef TEST_H
#define TEST_H

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>

class carteTest : public QWidget {
public:
    carteTest(QWidget *parent = nullptr) : QWidget(parent) {
        setMouseTracking(true); // Activer le suivi de la souris pour détecter les mouvements même sans clic
    }

protected:
    void enterEvent(QEvent *event){
        Q_UNUSED(event);
        qDebug() << "La souris est entrée dans le widget.";
    }

    void leaveEvent(QEvent *event){
        Q_UNUSED(event);
        qDebug() << "La souris a quitté le widget.";
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    carteTest testWidget;
    testWidget.resize(300, 200);
    testWidget.show();

    return app.exec();
}
#endif // TEST_H

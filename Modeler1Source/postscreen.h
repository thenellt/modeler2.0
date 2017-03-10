#ifndef POSTSCREEN_H
#define POSTSCREEN_H

#include <QWidget>
#include <QTimer>
#include "qdebug.h"
#include "modeler.h"

namespace Ui {
class postScreen;
}

class postScreen : public QWidget
{
    Q_OBJECT

public:
    explicit postScreen(QWidget *parent = 0, parameters* = 0);
    ~postScreen();

signals:
    void quit();

public slots:
    void changedTo();

    void updateImage();

private slots:
    void on_exit_pressed();

    void on_previousYear_pressed();

    void on_nextYear_pressed();

    void on_animate_pressed();

private:
    int currentImage;
    Ui::postScreen *ui;
    parameters *setup;
    QTimer *animTimer;
};

#endif // POSTSCREEN_H

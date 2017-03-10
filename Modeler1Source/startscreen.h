#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QFileDialog>
#include "modeler.h"

namespace Ui {
class startScreen;
}

class startScreen : public QWidget
{
    Q_OBJECT

public:
    explicit startScreen(QWidget *parent = 0, parameters *param = 0);
    QWidget* getNewsimButton();
    ~startScreen();

private slots:
    void on_pushButton_pressed();

    void on_loadConfig_pressed();

signals:
    void indexChange(int i);

    void configLoaded();

private:
    bool loadConfigFile(QString);

    Ui::startScreen *ui;
    parameters *setup;
};

#endif // STARTSCREEN_H

#ifndef ADVANCEDOPTIONS_H
#define ADVANCEDOPTIONS_H

#include <QDialog>
#include "modeler.h"
#include "qdebug.h"

namespace Ui {
class advancedOptions;
}

class advancedOptions : public QDialog
{
    Q_OBJECT

public:
    explicit advancedOptions(QWidget *parent = 0, parameters* = 0);
    ~advancedOptions();

    void gainFocus(parameters*);

signals:
    void dialog_closed();

private slots:
    void on_done_pressed();

    void on_diffEnable_toggled(bool checked);

    void on_encounterEnable_toggled(bool checked);

    void on_thetaEnable_toggled(bool checked);

    void on_diffHelp_pressed();

    void on_encounterHelp_pressed();

    void on_thetaHelp_pressed();

    void on_diffValue_editingFinished();

    void on_encounterValue_editingFinished();

    void on_thetaValue_editingFinished();

    void on_sampleHelp_pressed();

    void on_sampleEnable_toggled(bool checked);

    void on_sampleValue_valueChanged(int arg1);

private:
    Ui::advancedOptions *ui;
    parameters *setup;
};

#endif // ADVANCEDOPTIONS_H

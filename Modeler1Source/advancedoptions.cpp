#include "advancedoptions.h"
#include "ui_advancedoptions.h"

/*
 * animalDiffRate = .02;
 *       //animalGrowthRate = .07;
 *       encounterRate = .02043;
 *       theta = 1;
 *
 */

advancedOptions::advancedOptions(QWidget *parent, parameters *setup) :
    QDialog(parent),
    ui(new Ui::advancedOptions)
{
    ui->setupUi(this);
    this->setup = setup;
}

advancedOptions::~advancedOptions()
{
    delete ui;
}

void advancedOptions::gainFocus(parameters *setup){
    this->setup = setup;
    ui->explanationText->setText("<body>Hit the square button to the left of each parameter "
                                 "for additional infomration about the parameter.</body>");

    if(setup->animalDiffRate != .02){
        ui->diffEnable->blockSignals(true);
        ui->diffEnable->setChecked(true);
        ui->diffEnable->blockSignals(false);
        ui->diffValue->setText(QString::number(setup->animalDiffRate, 'f', 5));
    }

    if(setup->encounterRate != .02043){
        ui->encounterEnable->blockSignals(true);
        ui->encounterEnable->setChecked(true);
        ui->encounterEnable->blockSignals(false);
        ui->encounterValue->setText(QString::number(setup->encounterRate, 'f', 5));
    }

    if(setup->theta != 1){
        ui->thetaEnable->blockSignals(true);
        ui->thetaEnable->setChecked(true);
        ui->thetaEnable->blockSignals(false);
        ui->thetaValue->setText(QString::number(setup->theta, 'f', 5));
    }

    if(setup->diffusionSamples != 1){
        ui->sampleEnable->blockSignals(true);
        ui->sampleEnable->setChecked(true);
        ui->sampleEnable->blockSignals(false);
        ui->sampleValue->setEnabled(true);
        qDebug() << "focused gained samples: " << setup->diffusionSamples;
        ui->sampleValue->setValue(setup->diffusionSamples);
    }

}

void advancedOptions::on_done_pressed()
{
    if(ui->diffEnable->isChecked()){
        on_diffValue_editingFinished();
    }
    else{
        setup->animalDiffRate = .02;
    }
    if(ui->encounterEnable->isChecked()){
        on_encounterValue_editingFinished();
    }
    else{
        setup->encounterRate = .02043;
    }
    if(ui->thetaEnable->isChecked()){
        on_thetaValue_editingFinished();
    }
    else{
        setup->theta = 1;
    }
    if(ui->sampleEnable->isChecked()){
        on_sampleValue_valueChanged(ui->sampleValue->value());
    }
    else{
        setup->diffusionSamples = 1;
    }

    qDebug() << "diff rate: " << setup->animalDiffRate;
    qDebug() << "encounter rate: " << setup->encounterRate;
    qDebug() << "theta: " << setup->theta;
    qDebug() << "samples: " << setup->diffusionSamples;

    emit dialog_closed();
    close();
}

void advancedOptions::on_diffEnable_toggled(bool checked)
{
    bool test;
    double value;

    if(checked){
        ui->diffValue->setEnabled(true);
        if(ui->diffValue->text().length() != 0){
            value = ui->diffValue->text().toDouble(&test);
            if(test){
                setup->animalDiffRate = value;
            }
            else{
                setup->animalDiffRate = .02;
            }
        }
    }
    else{
        ui->diffValue->setDisabled(true);
        setup->animalDiffRate = .02;
    }
}

void advancedOptions::on_encounterEnable_toggled(bool checked)
{
    bool test;
    double value;

    if(checked){
        ui->encounterValue->setEnabled(true);
        if(ui->encounterValue->text().length() != 0){
            value = ui->encounterValue->text().toDouble(&test);
            if(test){
                setup->encounterRate = value;
            }
            else{
                setup->encounterRate = .02043;
            }
        }
    }
    else{
        ui->encounterValue->setDisabled(true);
        setup->encounterRate = .02043;
    }
}

void advancedOptions::on_thetaEnable_toggled(bool checked)
{
    bool test;
    double value;

    if(checked){
        ui->thetaValue->setEnabled(true);
        if(ui->thetaValue->text().length() != 0){
            value = ui->thetaValue->text().toDouble(&test);
            if(test){
                setup->theta = value;
            }
            else{
                setup->theta = 1;
            }
        }
    }
    else{
        ui->thetaValue->setDisabled(true);
        setup->theta = 1;
    }
}

void advancedOptions::on_sampleEnable_toggled(bool checked)
{
    if(checked){
        ui->sampleValue->setEnabled(true);
        if(ui->sampleValue->value() > 0 && ui->sampleValue->value() < 21){
            setup->diffusionSamples = ui->sampleValue->value();
        }
        else{
            setup->diffusionSamples = 1;
        }
    }
    else{
        ui->sampleValue->setDisabled(true);
        setup->diffusionSamples = 1;
    }
}


void advancedOptions::on_diffHelp_pressed()
{
    ui->explanationText->setText("Placeholder diffusion rate help");
}

void advancedOptions::on_encounterHelp_pressed()
{
    ui->explanationText->setText("Placeholder encounterRate help");
}

void advancedOptions::on_thetaHelp_pressed()
{
    ui->explanationText->setText("Placeholder theta help");
}

void advancedOptions::on_sampleHelp_pressed()
{
    ui->explanationText->setText("Placeholder diffusion samples help");
}

void advancedOptions::on_diffValue_editingFinished()
{
    bool test;
    double value;

    value = ui->diffValue->text().toDouble(&test);

    if(test && ui->diffValue->text().length() != 0){
        setup->animalDiffRate = value;
        qDebug() << "animal diff rate set to: " << value;
    }
    else{
        setup->animalDiffRate = .02;
        qDebug() << "animal diff rate set default";
    }
}

void advancedOptions::on_encounterValue_editingFinished()
{
    bool test;
    double value;

    value = ui->encounterValue->text().toDouble(&test);

    if(test && ui->encounterValue->text().length() != 0){
        setup->encounterRate = value;
        qDebug() << "encounter rate set to: " << value;
    }
    else{
        setup->encounterRate = .02043;
        qDebug() << "encounter rate set default";
    }
}

void advancedOptions::on_thetaValue_editingFinished()
{
    bool test;
    double value;

    value = ui->thetaValue->text().toDouble(&test);

    if(test && ui->thetaValue->text().length() != 0){
        setup->theta = value;
        qDebug() << "theta set to: " << value;
    }
    else{
        setup->theta = 1;
        qDebug() << "theta set default";
    }
}

void advancedOptions::on_sampleValue_valueChanged(int arg1)
{
    if(arg1 > 0 && arg1 < 21){
        setup->diffusionSamples = arg1;
    }
    else{
        setup->diffusionSamples = 1;
    }
}

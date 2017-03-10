#include "setupoutput.h"
#include "ui_setupoutput.h"

setupOutput::setupOutput(QWidget *parent, parameters* setup) :
    QWidget(parent),
    ui(new Ui::setupOutput)
{
    ui->setupUi(this);
    this->setup = setup;

    ui->configCheck->setEnabled(true);
    ui->heatAll->setEnabled(false);
    ui->heatFinal->setEnabled(false);
    ui->configPopCheck->setEnabled(false);
    ui->csvAll->setEnabled(false);
    ui->csvFinal->setEnabled(false);
}

setupOutput::~setupOutput()
{
    delete ui;
}

void setupOutput::populateLoadedData(){
    if(setup->output[0] != 0){
        ui->heatmapCheck->blockSignals(true);
        ui->heatmapCheck->setChecked(true);
        ui->heatmapCheck->blockSignals(false);
        ui->heatAll->setEnabled(true);
        ui->heatFinal->setEnabled(true);
        ui->heatScale->setEnabled(true);
        if(setup->diffusionSamples != 1){
            ui->heatScale->blockSignals(true);
            ui->heatScale->setChecked(true);
            ui->heatScale->blockSignals(false);
            ui->heatScaleValue->blockSignals(true);
            ui->heatScaleValue->setValue(setup->output[4]);
            ui->heatScaleValue->blockSignals(false);
        }
        if(setup->output[0] == 1){
            ui->heatAll->setChecked(true);
            ui->heatFinal->setChecked(false);
        }
        else{
            ui->heatAll->setChecked(false);
            ui->heatFinal->setChecked(true);
        }
        ui->widthDisp->setText("Width: " + QString::number(setup->x * ui->heatScaleValue->value()) + "px");
        ui->heightDisp->setText("Height: " + QString::number(setup->y * ui->heatScaleValue->value()) + "px");
    }

    if(setup->output[1]){
        ui->csvCheck->blockSignals(true);
        ui->csvCheck->setChecked(true);
        ui->csvCheck->blockSignals(false);
        ui->csvAll->setEnabled(true);
        ui->csvFinal->setEnabled(true);
        if(setup->output[1] == 1){
            ui->csvFinal->setChecked(false);
            ui->csvAll->setChecked(true);
        }
        else{
            ui->csvFinal->setChecked(true);
            ui->csvAll->setChecked(false);
        }
    }

    if(setup->output[2]){
        ui->configCheck->setChecked(true);
        ui->configPopCheck->setEnabled(true);
    }
}

void setupOutput::setParameters(parameters *setup){
    this->setup = setup;
}

void setupOutput::on_heatmapCheck_toggled(bool checked)
{
    if(checked){
        ui->heatAll->setEnabled(true);
        ui->heatFinal->setEnabled(true);
        ui->heatScale->setEnabled(true);

        if(ui->heatScale->isChecked()){
            ui->heatScaleValue->setEnabled(true);
        }

        ui->widthDisp->setText("Width: " + QString::number(setup->x * ui->heatScaleValue->value()) + "px");
        ui->heightDisp->setText("Height: " + QString::number(setup->y * ui->heatScaleValue->value()) + "px");

        if(ui->heatAll->isChecked()){
            setup->output[0] = 1;
        }
        else{
            setup->output[0] = 2;
        }
    }
    else{
        ui->heatAll->setEnabled(false);
        ui->heatFinal->setEnabled(false);
        ui->heatScale->setEnabled(false);
        ui->heatScaleValue->setEnabled(false);

        ui->widthDisp->setText("Width: ");
        ui->heightDisp->setText("Height: ");

        setup->output[0] = 0;
    }
}

void setupOutput::on_heatFinal_toggled(bool checked)
{
    if(checked){
        setup->output[0] = 2;
    }
    else{
        setup->output[0] = 1;
    }
}

void setupOutput::on_csvCheck_toggled(bool checked)
{
    if(checked){
        ui->csvAll->setEnabled(true);
        ui->csvFinal->setEnabled(true);

        if(ui->csvAll->isChecked()){
            setup->output[1] = 1;
        }
        else{
            setup->output[1] = 2;
        }
    }
    else{
        ui->csvAll->setEnabled(false);
        ui->csvFinal->setEnabled(false);

        setup->output[1] = 0;
    }
}

void setupOutput::on_csvFinal_toggled(bool checked)
{
    if(checked){
        setup->output[1] = 2;
    }
    else{
        setup->output[1] = 1;
    }
}

void setupOutput::on_configCheck_toggled(bool checked)
{
    if(checked){
        ui->configPopCheck->setEnabled(true);
        if(ui->configPopCheck->isChecked()){
            setup->output[2] = 2;
        }
        else{
            setup->output[2] = 1;
        }
    }
    else{
        ui->configPopCheck->setEnabled(false);
        setup->output[2] = 0;
    }
}

void setupOutput::on_popCheck_toggled(bool checked)
{
    if(checked){
        setup->output[3] = 1;
    }
    else{
        setup->output[3] = 0;
    }
}

void setupOutput::on_run_pressed()
{
    emit indexChange(5);
}

void setupOutput::on_heatScale_toggled(bool checked)
{
    if(checked){
        ui->heatScaleValue->setEnabled(true);
        setup->output[4] = ui->heatScaleValue->value();
    }
    else{
        setup->output[4] = 1;
        ui->heatScaleValue->setDisabled(true);
    }
    qDebug() << "heatmap scale: " << setup->output[4];
}

void setupOutput::on_heatScaleValue_valueChanged(int arg1)
{
    qDebug() << "heatmap scale: " << ui->heatScaleValue->value();
    setup->output[4] = ui->heatScaleValue->value();

    ui->widthDisp->setText("Width: " + QString::number(setup->x * ui->heatScaleValue->value()) + "px");
    ui->heightDisp->setText("Height: " + QString::number(setup->y * ui->heatScaleValue->value()) + "px");

}

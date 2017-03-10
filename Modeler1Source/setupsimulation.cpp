#include "setupsimulation.h"
#include "ui_setupsimulation.h"

SetupSimulation::SetupSimulation(QWidget *parent, parameters *setup) :
    QWidget(parent),
    ui(new Ui::SetupSimulation)
{
    ui->setupUi(this);
    this->setup = setup;
    advanced = new advancedOptions(this, this->setup);
    connect(advanced, SIGNAL(dialog_closed()), this, SLOT(advDialogClosed()));
    advanced->setModal(false);
    advanced->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
    ready = false;
    dialogOpen = false;
    //connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(testButton()));
    ui->explanationText->setText("<body>Hit the square button to the left of each parameter "
                                 "for additional infomration about the parameter.</body>");
    //connect(ui->huntHelp, SIGNAL(pressed()), this, SLOT(sampleHelpButton()));

    checked = new bool[10];
    for(int i = 0; i < 10; i++){
        checked[i] = false;
    }

}

SetupSimulation::~SetupSimulation()
{
    delete checked;
    delete ui;
}

void SetupSimulation::populateLoadedData(){
    ui->durationValue->setText(QString::number(setup->years, 10));
    ui->carryValue->setText(QString::number(setup->carryCapacity, 10));
    ui->rangeValue->setText(QString::number(setup->huntRange, 10));
    ui->huntValue->setText(QString::number(setup->huntsPerYear, 10));
    ui->killValue->setText(QString::number(setup->killProb, 'f', 5));
    ui->growthValue->setText(QString::number(setup->animalGrowthRate, 'f', 5));
    ui->heightValue->setText(QString::number(setup->y, 10));
    ui->widthValue->setText(QString::number(setup->x, 10));
    for(int i = 0; i < 8; i++){
        checked[i] = true;
    }
    if(setup->geolocation){
        ui->latValue->setText(QString::number(setup->geoY, 'f', 5));
        ui->longValue->setText(QString::number(setup->geoX, 'f', 5));
        checked[8] = true;
        checked[9] = true;
    }
    if(checkParameters()){
        ui->submit->setEnabled(true);
    }
}

void SetupSimulation::setParameters(parameters* input){
    setup = input;
}

bool SetupSimulation::checkReady(){
    return ready;
}

int SetupSimulation::checkParameters(){
    bool good = true;
    if(!dialogOpen){
        for(int i = 0; i < 7; i++){
            if(!checked[i]){
                good = false;
            }
        }

        if(good && !checked[8] && !checked[9]){
            ui->submit->setEnabled(true);
            setup->geolocation = false;
            setup->setupComplete = true;
            ready = true;
            return 1;
        }
        else if(good && checked[8] && checked[9]){
            ui->submit->setEnabled(true);
            setup->geolocation = true;
            setup->setupComplete = true;
            ready = true;
            return 1;
        }
        else{
            ui->submit->setEnabled(false);
            setup->setupComplete = false;
            ready = false;
            return 0;
        }
    }
    return 0;
}

/*
void SetupSimulation::testButton(){
    std::cout << "TestButton called" << std::endl;

    if(ui->lineEdit->text().length() < 1){
        ui->label->setText((QString)("Input was empty!"));
    }
    else{
        ui->label->setText((QString)("It Worked!"));
    }

}
*/

void SetupSimulation::on_huntHelp_pressed()
{
    ui->explanationText->setText("This is the parameter for hunts per hunter per year.\n"
                                 "Typical values range between 40 and 80.");
}

void SetupSimulation::on_durationHelp_pressed()
{
    ui->explanationText->setText("Placeholder duration help");
}

void SetupSimulation::on_carryHelp_pressed()
{
    ui->explanationText->setText("Placeholder carry capacity help");
}

void SetupSimulation::on_rangeHelp_pressed()
{
    ui->explanationText->setText("Placeholder hunter range help");
}

void SetupSimulation::on_killHelp_pressed()
{
    ui->explanationText->setText("Placeholder kill probability help");
}

void SetupSimulation::on_dimensionsHelp_pressed()
{
    ui->explanationText->setText("Placeholder dimensions help");
}

void SetupSimulation::on_geoHelp_pressed()
{
    ui->explanationText->setText("Placeholder geolocation help");
}

void SetupSimulation::on_growthHelp_pressed()
{
    ui->explanationText->setText("Placeholder animal growth rate help");
}

void SetupSimulation::on_submit_pressed()
{
    std::cout << "trying to change to edit map" << std::endl;
    if(checkParameters()){
        emit indexChange(3);
    }
}

void SetupSimulation::on_durationValue_editingFinished()
{
    bool test = false;
    double value;

    value = ui->durationValue->text().toDouble(&test);

    if(test){
        checked[0] = true;
        std::cout << "number was good for duration:" << value << std::endl;
        setup->years = value;
        ui->duration->setText("<font color='black'>Simulation Duration (years):</font>");

    }
    else{
        checked[0] = false;
        ui->duration->setText("<font color='red'>Simulation Duration (years):</font>");
    }

    checkParameters();
}

void SetupSimulation::on_carryValue_editingFinished()
{
    bool test = false;
    double value;

    value = ui->carryValue->text().toDouble(&test);

    if(test){
        checked[1] = true;
        std::cout << "number was good for carry:" << value << std::endl;
        setup->carryCapacity = value;
        ui->carry->setText("<font color='black'>Carrying Capacity:</font>");
    }
    else{
        checked[1] = false;
        ui->carry->setText("<font color='red'>Carrying Capacity:</font>");
    }

    checkParameters();
}

void SetupSimulation::on_rangeValue_editingFinished()
{
    bool test = false;
    double value;

    value = ui->rangeValue->text().toDouble(&test);

    if(test){
        checked[2] = true;
        std::cout << "number was good for hunter range:" << value << std::endl;
        setup->huntRange = value;
        ui->range->setText("<font color='black'>Hunter Travel Range (km):</font>");
    }
    else{
        checked[2] = false;
        ui->range->setText("<font color='red'>Hunter Travel Range (km):</font>");
    }

    checkParameters();
}

void SetupSimulation::on_huntValue_editingFinished()
{
    bool test = false;
    double value;

    value = ui->huntValue->text().toDouble(&test);

    if(test){
        checked[3] = true;
        std::cout << "number was good for hunts per year:" << value << std::endl;
        setup->huntsPerYear = value;
        ui->hphy->setText("<font color='black'>Hunts per Hunter per Year:</font>");
    }
    else{
        checked[3] = false;
        ui->hphy->setText("<font color='red'>Hunts per Hunter per Year:</font>");
    }

    checkParameters();
}

void SetupSimulation::on_killValue_editingFinished()
{
    bool test = false;
    double value;

    value = ui->killValue->text().toDouble(&test);

    if(test){
        checked[4] = true;
        std::cout << "number was good for kill probability:" << value << std::endl;
        setup->killProb = value;
        ui->killRate->setText("<font color='black'>Hunter Kill Probability:</font>");
    }
    else{
        checked[4] = false;
        ui->killRate->setText("<font color='red'>Hunter Kill Probability:</font>");
    }

    checkParameters();
}


void SetupSimulation::on_heightValue_editingFinished()
{
    bool test = false;
    double value;

    value = ui->heightValue->text().toDouble(&test);

    if(test){
        checked[6] = true;
        std::cout << "number was good for height:" << value << std::endl;
        setup->y = value;
        ui->height->setText("<font color='black'>Height:</font>");
    }
    else{
        checked[6] = false;
        ui->height->setText("<font color='red'>Height:</font>");
    }

    checkParameters();
}

void SetupSimulation::on_widthValue_editingFinished()
{
    bool test = false;
    double value;

    value = ui->widthValue->text().toDouble(&test);

    if(test){
        checked[7] = true;
        std::cout << "number was good for width:" << value << std::endl;
        setup->x = value;
        ui->width->setText("<font color='black'>Width:</font>");
    }
    else{
        checked[7] = false;
        ui->width->setText("<font color='red'>Width:</font>");
    }

    checkParameters();
}

void SetupSimulation::on_latValue_editingFinished()
{
    qDebug() << "in latitude checker";
    bool test = false;
    double value;

    value = ui->latValue->text().toDouble(&test);

    if(test){
        checked[8] = true;
        std::cout << "number was good for latitude:" << value << std::endl;
        setup->geoY = value;
        ui->latitude->setText("<font color='black'>Latitude:</font>");
    }
    else{
        checked[8] = false;
        ui->latitude->setText("<font color='red'>Latitude:</font>");
    }

    checkParameters();
}

void SetupSimulation::on_longValue_editingFinished()
{
    qDebug() << "in longitude checker";
    bool test = false;
    double value;

    value = ui->longValue->text().toDouble(&test);

    if(test){
        checked[9] = true;
        std::cout << "number was good for longitude:" << value << std::endl;
        setup->geoX = value;
        ui->longitude->setText("<font color='black'>Longitude:</font>");
    }
    else{
        checked[9] = false;
        ui->longitude->setText("<font color='red'>Longitude:</font>");
    }

    checkParameters();
}

void SetupSimulation::on_growthValue_editingFinished()
{
    qDebug() << "in growth value checker";
    bool test = false;
    double value;

    value = ui->growthValue->text().toDouble(&test);

    if(test){
        std::cout << "number was good for animal growth rate:" << value << std::endl;
        setup->animalGrowthRate = value;
        checked[5] = true;
        ui->growthLabel->setText("<font color='black'>Animal Growth Rate:</font>");
    }
    else{
        checked[5] = true;
        ui->growthLabel->setText("<font color='red'>Animal Growth Rate:</font>");
    }

    checkParameters();
}

void SetupSimulation::on_advancedOptions_pressed()
{
    ui->advancedOptions->setEnabled(false);
    if(ui->submit->isEnabled()){
        qDebug() << "hello....";
        ui->submit->setDisabled(true);
    }
    qDebug() << "samples test 1: " << setup->diffusionSamples;
    advanced->gainFocus(setup);
    dialogOpen = true;
    qDebug() << "samples test 2: " << setup->diffusionSamples;
    advanced->show();

}

void SetupSimulation::advDialogClosed(){
    qDebug() << "got here to dialog closed";
    ui->advancedOptions->setEnabled(true);
    dialogOpen = false;
    checkParameters();
}

void SetupSimulation::on_durationValue_returnPressed()
{
    bool test = false;
    double value;

    value = ui->durationValue->text().toDouble(&test);

    if(test){
        checked[0] = true;
        std::cout << "number was good for duration:" << value << std::endl;
        setup->years = value;
        ui->duration->setText("<font color='black'>Simulation Duration (years):</font>");

    }
    else{
        checked[0] = false;
        ui->duration->setText("<font color='red'>Simulation Duration (years):</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}

void SetupSimulation::on_carryValue_returnPressed()
{
    bool test = false;
    double value;

    value = ui->carryValue->text().toDouble(&test);

    if(test){
        checked[1] = true;
        std::cout << "number was good for carry:" << value << std::endl;
        setup->carryCapacity = value;
        ui->carry->setText("<font color='black'>Carrying Capacity:</font>");
    }
    else{
        checked[1] = false;
        ui->carry->setText("<font color='red'>Carrying Capacity:</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}

void SetupSimulation::on_rangeValue_returnPressed()
{
    bool test = false;
    double value;

    value = ui->rangeValue->text().toDouble(&test);

    if(test){
        checked[2] = true;
        std::cout << "number was good for hunter range:" << value << std::endl;
        setup->huntRange = value;
        ui->range->setText("<font color='black'>Hunter Travel Range (km):</font>");
    }
    else{
        checked[2] = false;
        ui->range->setText("<font color='red'>Hunter Travel Range (km):</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}

void SetupSimulation::on_huntValue_returnPressed()
{
    bool test = false;
    double value;

    value = ui->huntValue->text().toDouble(&test);

    if(test){
        checked[3] = true;
        std::cout << "number was good for hunts per year:" << value << std::endl;
        setup->huntsPerYear = value;
        ui->hphy->setText("<font color='black'>Hunts per Hunter per Year:</font>");
    }
    else{
        checked[3] = false;
        ui->hphy->setText("<font color='red'>Hunts per Hunter per Year:</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}

void SetupSimulation::on_killValue_returnPressed()
{
    bool test = false;
    double value;

    value = ui->killValue->text().toDouble(&test);

    if(test){
        checked[4] = true;
        std::cout << "number was good for kill probability:" << value << std::endl;
        setup->killProb = value;
        ui->killRate->setText("<font color='black'>Hunter Kill Probability:</font>");
    }
    else{
        checked[4] = false;
        ui->killRate->setText("<font color='red'>Hunter Kill Probability:</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}

void SetupSimulation::on_heightValue_returnPressed()
{
    bool test = false;
    double value;

    value = ui->heightValue->text().toDouble(&test);

    if(test){
        checked[6] = true;
        std::cout << "number was good for height:" << value << std::endl;
        setup->y = value;
        ui->height->setText("<font color='black'>Height:</font>");
    }
    else{
        checked[6] = false;
        ui->height->setText("<font color='red'>Height:</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}

void SetupSimulation::on_widthValue_returnPressed()
{
    bool test = false;
    double value;

    value = ui->widthValue->text().toDouble(&test);

    if(test){
        checked[7] = true;
        std::cout << "number was good for width:" << value << std::endl;
        setup->x = value;
        ui->width->setText("<font color='black'>Width:</font>");
    }
    else{
        checked[7] = false;
        ui->width->setText("<font color='red'>Width:</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}

void SetupSimulation::on_latValue_returnPressed()
{
    qDebug() << "in latitude checker";
    bool test = false;
    double value;

    value = ui->latValue->text().toDouble(&test);

    if(test){
        checked[8] = true;
        std::cout << "number was good for latitude:" << value << std::endl;
        setup->geoY = value;
        ui->latitude->setText("<font color='black'>Latitude:</font>");
    }
    else{
        checked[8] = false;
        ui->latitude->setText("<font color='red'>Latitude:</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}

void SetupSimulation::on_longValue_returnPressed()
{
    qDebug() << "in longitude checker";
    bool test = false;
    double value;

    value = ui->longValue->text().toDouble(&test);

    if(test){
        checked[9] = true;
        std::cout << "number was good for longitude:" << value << std::endl;
        setup->geoX = value;
        ui->longitude->setText("<font color='black'>Longitude:</font>");
    }
    else{
        checked[9] = false;
        ui->longitude->setText("<font color='red'>Longitude:</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}



void SetupSimulation::on_growthValue_returnPressed()
{
    qDebug() << "in growth value checker";
    bool test = false;
    double value;

    value = ui->growthValue->text().toDouble(&test);

    if(test){
        std::cout << "number was good for animal growth rate:" << value << std::endl;
        checked[5] = true;
        setup->animalGrowthRate = value;
        ui->growthLabel->setText("<font color='black'>Animal Growth Rate:</font>");
    }
    else{
        checked[5] = false;
        ui->growthLabel->setText("<font color='red'>Animal Growth Rate:</font>");
    }

    if(checkParameters()){
        emit indexChange(3);
    }
}

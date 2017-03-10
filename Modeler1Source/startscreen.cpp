#include "startscreen.h"
#include "ui_startscreen.h"
#include <iostream>

startScreen::startScreen(QWidget *parent, parameters *setup) :
    QWidget(parent),
    ui(new Ui::startScreen)
{
    ui->setupUi(this);
    this->setup = setup;
    ui->loadConfig->setEnabled(true);
    std::cout << "inside startscreen constructor" << std::endl;
    //connect(ui->pushButton, SIGNAL(pressed()), parent, parent->SLOT()
}

startScreen::~startScreen()
{
    delete ui;
}

QWidget* startScreen::getNewsimButton(){
    return ui->pushButton;
}

void startScreen::on_pushButton_pressed()
{
    std::cout << "new simulation button was pressed" << std::endl;
    emit indexChange(1);
}

void startScreen::on_loadConfig_pressed()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select Project Config File"), "/home", tr("CFG (*.cfg)"));
    if(loadConfigFile(filename)){
        emit configLoaded();
    }
    else{
        //delete setup;
        setup = new parameters();
    }
}

bool startScreen::loadConfigFile(QString filename){
    int linecount = 0;
    bool good = true, numTest;
    QString line;
    qDebug() << "loadConfigFile filename: " << filename;
    QFile config(filename);
    if (!config.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }

    QTextStream testStream(config.readLine());
    QString firstTest;
    testStream >> firstTest;
    if(firstTest != "SimulationName:"){
        qDebug() << "initial config contents test failed";
        config.close();
        return false;
    }
    else{
        testStream >> firstTest;
        qDebug() << "project name read: " << firstTest;
        setup->name = firstTest.toStdString();
    }

    while(!config.atEnd() && good){
        int test, counter;
        double testD;
        QTextStream stream(config.readLine());
        QString first;
        QString second;
        stream >> first >> second;
        qDebug() << "line number: " << linecount << " first: " << first << " second: " << second;
        switch(linecount){
        case 0:
            qDebug() << "Duration: " << second;
            test = second.toInt(&numTest, 10);
            if(!numTest){
                qDebug() << "duration problem";
                good = false;
            }
            else if(test < 1){
                qDebug() << "duration invalid value";
                good = false;
            }
            else{
                setup->years = test;
            }
            break;
        case 1:
            qDebug() << "Capacity: " << second;
            test = second.toInt(&numTest, 10);
            if(!numTest){
                qDebug() << "capacity problem";
                good = false;
            }
            else{
                setup->carryCapacity = test;
            }
            break;
        case 2:
            qDebug() << "TravelRange: " << second;
            test = second.toInt(&numTest, 10);
            if(!numTest){
                qDebug() << "hunter travel range problem";
                good = false;
            }
            else{
                setup->huntRange = test;
            }
            break;
        case 3:
            qDebug() << "HuntsperYear: " << second;
            test = second.toInt(&numTest, 10);
            if(!numTest){
                qDebug() << "huntsperyear problem";
                good = false;
            }
            else{
                setup->huntsPerYear = test;
            }
            break;
        case 4:
            qDebug() << "Killprob: " << second;
            testD = second.toDouble(&numTest);
            if(testD <= 0){
                qDebug() << "killprob value problem";
                good = false;
            }
            else{
                setup->killProb = testD;
            }
            break;
        case 5:
            qDebug() << "animalgrowthrate: " << second;
            testD = second.toDouble(&numTest);
            if(testD <= 0){
                qDebug() << "growthrate value problem";
                good = false;
            }
            else{
                setup->animalGrowthRate = testD;
            }
            break;
        case 6:
            qDebug() << "height: " << second;
            test = second.toInt(&numTest, 10);
            if(!numTest){
                qDebug() << "height problem";
                good = false;
            }
            else if(test < 1){
                qDebug() << "height invalid value";
                good = false;
            }
            else{
                setup->y = test;
            }
            break;
        case 7:
            qDebug() << "width: " << second;
            test = second.toInt(&numTest, 10);
            if(!numTest){
                qDebug() << "width problem";
                good = false;
            }
            else if(test < 1){
                qDebug() << "width invalid value";
                good = false;
            }
            else{
                setup->x = test;
            }
            break;
        case 8:
            qDebug() << "Geolocation: " << second;
            if(second == "off"){
                setup->geolocation = false;
                linecount += 2;
            }
            else if(second == "on"){
                setup->geolocation = true;
                qDebug() << "reading lat and long...";
            }
            else{
                qDebug() << "something was wrong by line 9";
                good = false;
            }
            break;
        case 9:
            qDebug() << "latitude: " << second;
            testD = second.toDouble(&numTest);
            setup->geoY = testD;
            break;
        case 10:
            qDebug() << "longitude: " << second;
            testD = second.toDouble(&numTest);
            setup->geoX = testD;
            break;
        case 11:
            qDebug() << "animaldiffusionrate: " << second;
            testD = second.toDouble(&numTest);
            if(testD <= 0){
                qDebug() << "animaldiffusionrate value problem";
                good = false;
            }
            else{
                setup->animalDiffRate = testD;
            }
            break;
        case 12:
            qDebug() << "encounterrate: " << second;
            testD = second.toDouble(&numTest);
            if(testD <= 0){
                qDebug() << "encounterrate value problem";
                good = false;
            }
            else{
                setup->encounterRate = testD;
            }
            break;
        case 13:
            qDebug() << "theta: " << second;
            testD = second.toDouble(&numTest);
            if(testD <= 0){
                qDebug() << "theta value problem";
                good = false;
            }
            else{
                setup->theta = testD;
            }
            break;
        case 14:
            qDebug() << "diffusion samples: " << second;
            test = second.toInt(&numTest, 10);
            if(!numTest){
                qDebug() << "diffusion samples problem";
                good = false;
            }
            else if(test < 1){
                qDebug() << "diffusion samples invalid value";
                good = false;
            }
            else{
                setup->diffusionSamples = test;
                qDebug() << "samples: " << setup->diffusionSamples;
            }
            break;
        case 15:
            qDebug() << "output settings: " << second;
            counter = 0;
            test = second.toInt(&numTest, 10);
            if(numTest && (test > -1) && (test < 3)){
                setup->output[0] = test;
                counter++;
            }
            else{
                good = false;
                break;
            }
            while(counter < 4){
                stream >> second;
                qDebug() << "output at[" << counter << "]: " << second;
                test = second.toInt(&numTest, 10);
                if(numTest && (test > -1) && (test < 3)){
                    setup->output[counter] = test;
                    counter++;
                }
                else{
                    good = false;
                    break;
                }
            }
            stream >> second;
            qDebug() << "output at[" << counter << "]: " << second;
            test = second.toInt(&numTest, 10);
            if(numTest && (test  >= 1)){
                setup->output[4] = test;
            }
            else{
                good = false;
            }
            break;
        default:
            qDebug() << "shouldn't have reached default config read case...";
            good = false;
        }
        linecount++;
    }

    config.close();
    if(!good){
        return false;
    }

    return true;
}


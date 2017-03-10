#include "postscreen.h"
#include "ui_postscreen.h"

postScreen::postScreen(QWidget *parent, parameters *setup) :
    QWidget(parent),
    ui(new Ui::postScreen)
{
    animTimer = new QTimer(this);
    ui->setupUi(this);
    this->setup = setup;
    currentImage = 1;

    connect(animTimer, SIGNAL(timeout()), this, SLOT(updateImage()));

}

postScreen::~postScreen()
{
    delete ui;
}

void postScreen::changedTo(){
    int w = ui->imageLabel->width();
    int h = ui->imageLabel->height();
    ui->heightLabel->setText(QString::number(setup->y));
    ui->widthLabel->setText(QString::number(setup->x));
    qDebug() << "width: " << w << " height: " << h;
    qDebug() << "in changed to output preview screen";
    if(setup->output[0] == 1){
        QPixmap *image = new QPixmap(QString::fromStdString(setup->workingPath) + "/" + QString::fromStdString(setup->name) +
                                     "_heatmap" + QString::number(currentImage) + ".png", nullptr, Qt::AutoColor);
        ui->imageLabel->setPixmap((*image).scaled(w, h, Qt::KeepAspectRatio));
        delete image;
        ui->currentYear->setText("Current year: 1");
    }
    else if(setup->output[0] == 2){
        QPixmap *image = new QPixmap(QString::fromStdString(setup->workingPath) + "/" + QString::fromStdString(setup->name) +
                                     "_heatmap" + QString::number(setup->years) + ".png", nullptr, Qt::AutoColor);
        ui->imageLabel->setPixmap((*image).scaled(w, h, Qt::KeepAspectRatio));
        delete image;
        ui->nextYear->setDisabled(true);
        ui->previousYear->setDisabled(true);
        ui->animate->setDisabled(true);
        ui->currentYear->setText("Current year: final");
    }
    else if(setup->output[0] == 0){
        ui->nextYear->setDisabled(true);
        ui->previousYear->setDisabled(true);
        ui->animate->setDisabled(true);
    }
}

void postScreen::on_exit_pressed()
{
    emit quit();
}

void postScreen::on_previousYear_pressed()
{
    if(currentImage > 1){
        int w = ui->imageLabel->width();
        int h = ui->imageLabel->height();
        qDebug() << "width: " << w << " height: " << h;
        currentImage -= 1;
        if(currentImage == 1){
            ui->currentYear->setText("Current year: 1");
        }
        else{
            ui->currentYear->setText("Current year: " + QString::number(currentImage));
        }
        QPixmap *image = new QPixmap(QString::fromStdString(setup->workingPath) + "/" + QString::fromStdString(setup->name) +
                                     "_heatmap" + QString::number(currentImage) + ".png", nullptr, Qt::AutoColor);
        ui->imageLabel->setPixmap((*image).scaled(w, h, Qt::KeepAspectRatio));
        delete image;
    }
}

void postScreen::on_nextYear_pressed()
{
    if(currentImage < setup->years){
        int w = ui->imageLabel->width();
        int h = ui->imageLabel->height();
        qDebug() << "width: " << w << " height: " << h;
        currentImage += 1;
        if(currentImage == setup->years){
            ui->currentYear->setText("Current year: final");
        }
        else{
            ui->currentYear->setText("Current year: " + QString::number(currentImage));
        }
        QPixmap *image = new QPixmap(QString::fromStdString(setup->workingPath) + "/" + QString::fromStdString(setup->name) +
                                     "_heatmap" + QString::number(currentImage) + ".png", nullptr, Qt::AutoColor);
        ui->imageLabel->setPixmap((*image).scaled(w, h, Qt::KeepAspectRatio));
        delete image;
    }
}

void postScreen::updateImage()
{
    if(currentImage < setup->years){
        on_nextYear_pressed();
        animTimer->start(200);
    }
    else{
        ui->animate->setEnabled(true);
        ui->nextYear->setEnabled(true);
        ui->previousYear->setEnabled(true);
        animTimer->stop();
    }
}

void postScreen::on_animate_pressed()
{
    currentImage = 0;
    ui->animate->setDisabled(true);
    ui->nextYear->setDisabled(true);
    ui->previousYear->setDisabled(true);
    animTimer->start(200);
}

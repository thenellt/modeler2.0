#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filename = "";
    outputFolder = "";
    url = "";
    validFolder = false;
    fileName = false;
    hasUrl = false;

    point testPoint = test.getCenter();
    ui->testLabel->setText("Midpoint: " + QString::number((double)testPoint.x) + "," + QString::number((double)testPoint.y));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkFolder(){
    QDir::setCurrent(outputFolder);
    QFile file("~test.txt");
    if(file.open((QIODevice::WriteOnly | QIODevice::Text))){
            if(file.remove()){
                validFolder = true;
                qDebug() << "test file removed, dir:" << outputFolder;
            }
            else{
                qDebug() << "coudln't remove test file...";
            }
    }
}

void MainWindow::on_dlLocation_pressed()
{
    outputFolder = QFileDialog::getExistingDirectory(this, tr("Save Location:"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
            //directory(this, tr("Save Location:"));
    checkFolder();
}

void MainWindow::on_startDl_pressed()
{
    if(validFolder && fileName && hasUrl){
        qDebug() << "filename: " << filename << " folder: " << outputFolder << " url: " << urlS;
        downloadFile();
    }
    else{
        return;
    }
}

void MainWindow::on_filenameEdit_textChanged(const QString &arg1)
{
    filename = arg1;
    if(!filename.length()){
        fileName = false;
        qDebug() << "filename empty";
    }
    else{
        fileName = true;
    }
    qDebug() << "filename changed: " << filename;
}


void MainWindow::on_urlEdit_textChanged(const QString &arg1)
{
    urlS = arg1;
    if(!urlS.length()){
        hasUrl = false;
        qDebug() << "urlS empty";
    }
    else{
        hasUrl = true;
    }
    qDebug() << "urlS changed: " << urlS;
}

void MainWindow::downloadFile(){


    if (QFile::exists(filename)) {
        if (QMessageBox::question(this, tr("Overwrite Existing File"),
                                  tr("There already exists a file called %1 in "
                                     "the current directory. Overwrite?").arg(filename),
                                  QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
            == QMessageBox::No)
            return;
        QFile::remove(filename);
    }

    file = openFileForWrite(filename);
    if (!file)
        return;
    urlS = urlS.simplified();
    url = QUrl::fromUserInput(urlS);

    ui->startDl->setEnabled(false);
    startRequest();
}

void MainWindow::startRequest(){
    httpRequestAborted = false;

    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &MainWindow::httpReadyRead);

    qDebug() << "request started...";
}

void MainWindow::cancelDownload(){
    httpRequestAborted = true;
    reply->abort();
    qDebug() << "shit fucked up yo" << endl;
}

void MainWindow::httpFinished(){
    if (httpRequestAborted) {
        qDebug() << "httpFinished: download aborted";
        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    if (reply->error()) {
        qDebug() << "httpFinished: download error";
        qDebug() << "error: " << reply->errorString();
        //statusLabel->setText(tr("Download failed:\n%1.").arg(reply->errorString()));
        //downloadButton->setEnabled(true);
        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    file->close();

    //const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    reply->deleteLater();
    reply = Q_NULLPTR;
    qDebug() << "httpFinished: shit finished yo";
    ui->startDl->setEnabled(true);

}

void MainWindow::httpReadyRead(){
    if (file){
        file->write(reply->readAll());
        qDebug() << "wrote something...";
    }
}

QFile *MainWindow::openFileForWrite(const QString &fileName)
{
    QScopedPointer<QFile> file(new QFile(fileName));
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(QDir::toNativeSeparators(fileName),
                                      file->errorString()));
        return Q_NULLPTR;
    }
    return file.take();
}


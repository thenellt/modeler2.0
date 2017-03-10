#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QProgressDialog>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QMessageBox>

#include "map.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void checkFolder();
    void startRequest();

private slots:
    void on_dlLocation_pressed();
    void on_startDl_pressed();
    void on_filenameEdit_textChanged(const QString &arg1);
    void on_urlEdit_textChanged(const QString &arg1);

private slots:
    void downloadFile();
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();

private:
    Ui::MainWindow *ui;
    QString filename;
    QString outputFolder;
    QString urlS;
    bool validFolder;
    bool fileName;
    bool hasUrl;
    map test;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;
    bool httpRequestAborted;
    QFile *openFileForWrite(const QString &fileName);
};

#endif // MAINWINDOW_H

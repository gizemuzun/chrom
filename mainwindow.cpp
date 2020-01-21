#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"
#include <QTime>
#include <QThread>
#include <QDebug>
#include <QPainter>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startFlag = 0;
    lapCounter = 0;
    Worker *lobWorker = new Worker;
    lobWorker->moveToThread(&workerThread);
    connect(lobWorker,SIGNAL(resultReady(QString)),this,SLOT(workerFinish(QString)));
    connect(this,SIGNAL(startChrono()),lobWorker,SLOT(launchChrono()));
    connect(this, SIGNAL(resetChrono()), lobWorker, SLOT(resetChrono()));
    connect(&workerThread, SIGNAL (finished()), &workerThread, SLOT (deleteLater()));

    workerThread.start();

    QFile styleFile("style.qss");
    styleFile.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(styleFile.readAll());
    this->setStyleSheet(StyleSheet);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
    delete ui;
}

void MainWindow::on_startButton_2_clicked()
{
    if(startFlag == 0){
        ui->startButton_2->setText("Stop");
        emit(startChrono());
        startFlag = 1;
        stopFlag = 1;
    }else{
        ui->startButton_2->setText("Start");
        startFlag = 0;
        stopFlag = 0;
    }
}

void MainWindow::on_resetButton_2_clicked()
{
    ui->gobLCD_2->setText("00:00:00");
    emit(resetChrono());
}

void MainWindow::on_flagButton_2_clicked()
{
    lapCounter ++;
    ui->gobLapTextArea_2->appendPlainText(QString("%1) %2 ").arg(lapCounter).arg(ui->gobLCD_2->text()));
    ui->label_chro->setText(ui->gobLCD_2->text());
}

void MainWindow::workerFinish(QString data)
{
    ui->gobLCD_2->setText(data);
    if(startFlag == 1)emit(startChrono());
}

void MainWindow::on_clearLapsButton_2_clicked()
{
    ui->gobLapTextArea_2->clear();
    ui->label_chro->clear();
    lapCounter = 0;
}

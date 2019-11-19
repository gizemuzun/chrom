#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_2_clicked();
    void on_resetButton_2_clicked();
    void on_flagButton_2_clicked();
    void workerFinish(QString data);
    void on_clearLapsButton_2_clicked();

signals:
    void startChrono();
    void resetChrono();
    void killChronoThread();

private:
    Ui::MainWindow *ui;
    int startFlag;
    int stopFlag;
    int lapCounter;
};

#endif // MAINWINDOW_H

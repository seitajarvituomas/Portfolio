#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lcdNumberSec->setDigitCount(2);
    ui->lcdNumberMin->setDigitCount(2);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer->start(1000);
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::on_resetButton_clicked()
{
    timer->stop();
    seconds = 0;
    minutes = 0;

    ui->lcdNumberSec->display(seconds);
    ui->lcdNumberMin->display(minutes);
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

void MainWindow::timeout()
{
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
        }
    }

    ui->lcdNumberSec->display(seconds);
    ui->lcdNumberMin->display(minutes);
}




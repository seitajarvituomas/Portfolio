#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::count_bmi(unsigned int weight, unsigned int height)
{
    double height_in_meters = static_cast<double>(height) / 100.0;
    double bmi = static_cast<double>(weight)/(height_in_meters*height_in_meters);
    return bmi;
}


void MainWindow::on_countButton_clicked()
{
    double weight = ui->weightLineEdit->text().toDouble();
    double height = ui->heightLineEdit->text().toDouble();

    QString text;
    if (weight == 0 || height == 0) {
        text = "Cannot count.";
        ui->infoTextBrowser->clear();
    } else {
        double bmi = count_bmi(weight, height);
        text= QString::number(bmi);

        if (bmi > 25.0) {
            ui->infoTextBrowser->setText("You are overweight.");
        } else if (bmi < 18.5){
            ui->infoTextBrowser->setText("You are underweight.");
        } else {
            ui->infoTextBrowser->setText("Your weight is normal.");
        }
    }
    ui->resultLabel->setText(text);
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

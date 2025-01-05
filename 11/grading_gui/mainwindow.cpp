#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setRange(0, MAX_N_POINTS);
    ui->spinBoxG->setRange(0, MAX_N_POINTS);
    ui->spinBoxP->setRange(0, MAX_P_POINTS);
    ui->spinBoxE->setRange(0, 5);


    score_from_gui_exercises(ui->spinBoxG->value());

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_calculatePushButton_clicked()
{
    QString buttonText = "W-Score: " + QString::number(score_from_weekly_exercises(ui->spinBoxN->value(), ui->spinBoxG->value())) +
                         "\nP-Score: " + QString::number(score_from_projects(ui->spinBoxP->value())) +
                         "\nTotal grade: " + QString::number(calculate_total_grade(ui->spinBoxN->value(), ui->spinBoxG->value(),
                                                                                   ui->spinBoxP->value(), ui->spinBoxE->value()));
    ui->textBrowser->setText(buttonText);
}


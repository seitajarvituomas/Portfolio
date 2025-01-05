#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

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

void MainWindow::on_findPushButton_clicked()
{
    QString tiedoston_nimi = ui->fileLineEdit->text();

    std::ifstream tiedosto_olio(tiedoston_nimi.toStdString());

    if (!tiedosto_olio.is_open()) {
            ui->textBrowser->setText("File not found");
            return;
    } else {
        std::string the_word = ui->keyLineEdit->text().toStdString();

        if (the_word == "") {
            ui->textBrowser->setText("File found");
            return;

        } else {
            bool match_case = !ui->matchCheckBox->isChecked();

            if (match_case) {
                for (char& i : the_word) {
                    i = tolower(i);
                }
            }

            std::string rivi;
            bool find_word = false;
            while ( getline(tiedosto_olio, rivi) ) {
                if (rivi.find(the_word) != std::string::npos) {
                    if (match_case) {
                        for (char &l : rivi) {
                            l = tolower(l);
                        }
                    }
                    find_word = true;
                    break;
                }
            }

            tiedosto_olio.close();

            if (find_word) {
                ui->textBrowser->setText("Word found");
                return;
            } else {
                ui->textBrowser->setText("Word not found");
                return;
            }
        }
    }
}

void MainWindow::on_closePushButton_clicked()
{
    close();
}

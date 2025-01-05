#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double count_bmi(unsigned int weight, unsigned int height);

private slots:
    void on_countButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HH

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <string>
#include <iostream>
#include <fstream>
#include <QFileDialog>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_LoadFile_clicked();

    void on_DataToFile_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> energy, count;
    int NumOfLines; // Number of lines in the input data file
    string FileName; // Input filename
    double EnergyRangeSmall;
    double EnergyRangeLarge;
    int CountRangeSmall;
    int CountRangeLarge;

    void DataToFile();
};

#endif // MAINWINDOW_H

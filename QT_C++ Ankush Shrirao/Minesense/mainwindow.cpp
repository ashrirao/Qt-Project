#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    NumOfLines =1023;
    energy.resize(NumOfLines);
    count.resize(NumOfLines);
    EnergyRangeLarge =32 ;
    EnergyRangeSmall =-1 ;
    CountRangeLarge = 1026;
    CountRangeSmall =0 ;
    FileName= "Empty";

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*******************************
 ** on_pushButton_clicked() ******
 ** To update the graph  ******
*********************************/

void MainWindow::on_pushButton_clicked()
{
//Update Graph
if(FileName == "Empty"){
    ui->textEdit->setText("Please select the input data file first");

}else{
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(energy, count);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("Energy (keV)");
    ui->customPlot->yAxis->setLabel("Counts");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(EnergyRangeSmall, EnergyRangeLarge);
    ui->customPlot->yAxis->setRange(CountRangeSmall, CountRangeLarge);
    ui->customPlot->replot();
    ui->textEdit->setText("Graph has been updated");
}
}

/*******************************
 ** on_pushButton_2_clicked() ******
 ** To add new data  ******
*********************************/

void MainWindow::on_pushButton_2_clicked()
{
    //Add
    if(FileName == "Empty"){
        ui->textEdit->setText("Please select the input data file first");

    }else{
    int NewRow;
    double newCount=ui->count->text().toDouble();
    double newEnergy=ui->energy->text().toDouble();
    int index;
    ui->textEdit->setText(QString::number (newEnergy));
    for(index=0; index<NumOfLines;index++){

        if(energy[index] < newEnergy && energy [index +1] > newEnergy){
            ++index;
            double energyTemp = energy[index];
            double countTemp = count[index];
            energy[index] = newEnergy;
            count[index] = newCount;
            NewRow =index + 2;
            NumOfLines++ ;
            energy.resize(NumOfLines);
            count.resize(NumOfLines);
            for(int tempIndex = NumOfLines -1; tempIndex >index+1; tempIndex--){
                energy[tempIndex] = energy[tempIndex -1];
                count[tempIndex] = count[tempIndex -1];
            }
            energy[index +1] = energyTemp;
            count[index +1] = countTemp;

                break;
        }else if (energy[0] > newEnergy){
            NumOfLines++ ;
            energy.resize(NumOfLines);
            count.resize(NumOfLines);

            double energyTemp = energy[0];
            double countTemp = count[0];
            energy[0] = newEnergy;
            count[0] = newCount;
            NewRow =2;
            for(int tempIndex = NumOfLines -1; tempIndex >1; tempIndex--){
                energy[tempIndex] = energy[tempIndex -1];
                count[tempIndex] = count[tempIndex -1];
            }
            energy[1] = energyTemp;
            count[1] = countTemp;
            break;
        }else if(energy[NumOfLines-1] < newEnergy){
            NumOfLines++ ;
            energy.resize(NumOfLines);
            count.resize(NumOfLines);
            energy[NumOfLines -1]=newEnergy;
            count[NumOfLines -1] =newCount;
            NewRow =NumOfLines +1;
            break;
        }

    }
ui->textEdit->setText("Energy = " + QString::number(newEnergy) +
                      " and Count = " + QString::number(newCount)+
                      " have been successfully added on line number " +
                      QString::number(NewRow) +
                       "\n \n \nPlease update the file to view changes");
    }
}
/*******************************
 ** on_pushButton_3_clicked() ******
 ** To update the existing data  ******
*********************************/

void MainWindow::on_pushButton_3_clicked()
{
    if(FileName == "Empty"){
        ui->textEdit->setText("Please select the input data file first");

    }else{
    double newCount=ui->count->text().toDouble();
    double energyToUpdate=ui->energy->text().toDouble();
    int index = 0;
    bool available =false;
    //search index number in an array
    for(index=0; index<NumOfLines;index++){
        if(energyToUpdate == energy[index]){
            count [index] = newCount;
            available = true;
      break;
        }
    }
    if (available){
    ui->textEdit->setText("Energy = " + QString::number(energyToUpdate) +
                          " has been successfully updated to" +
                          " Energy = " + QString::number(energyToUpdate) +
                          " and Count = " + QString::number(newCount) +
                          "\n \n \nPlease update the file to view changes");

    }else{
        ui->textEdit->setText("Data not found");
    }
}
}

/*******************************
 ** on_pushButton_4_clicked() ******
 ** To delete the existing data  ******
*********************************/

void MainWindow::on_pushButton_4_clicked()
{
    if(FileName == "Empty"){
        ui->textEdit->setText("Please select the input data file first");

    }else{
    double energyToDelete=ui->energy->text().toDouble();
    int index = 0;
    bool available = false;
    //search index number in an array
    for(index=0; index<NumOfLines;index++){
        if(energyToDelete == energy[index]){
            available =true;
            for(index;index<NumOfLines -1;index ++)
            {
                energy[index] = energy[index + 1];
                count[index]  = count [index + 1];
            }
           NumOfLines-- ;
           energy.resize(NumOfLines);
           count.resize(NumOfLines);

           break;
        }

    }
    if (available){ui->textEdit->setText("Energy = " + QString::number(energyToDelete) +
                          " has been successfully deleted " +
                          "\n \n \nPlease update the file to view changes");
    }else{
        ui->textEdit->setText("Data not found");

    }
    }
}

/*******************************
 ** on_LoadFile_clicked())  ******
 ** Load the data file and ****
 ** initialize the arrays with ***
 **  the data from the data file  ******
*********************************/

void MainWindow::on_LoadFile_clicked()
{
FileName = (QFileDialog::getOpenFileName(this,tr("Load Data File"),"C://",
                                         "csv File (*.csv)")).toStdString();

string line;
int index =0;
ifstream datafile(FileName);
       if ( !datafile.is_open()) {
      ui->label->setText("Unable to open data file");
   }

getline(datafile, line);
while (index<NumOfLines){
getline(datafile, line,',');
energy[index] = stod (line);
getline(datafile, line);
count[index] = stod (line);
index++;
}


datafile.close();
ui->textEdit->setText(" File has been loaded successfully ");
}


/*******************************
 ** on_DataToFile_clicked()**
 ** Save the data to the output file**
*********************************/
void MainWindow::on_DataToFile_clicked()
{
    if(FileName == "Empty"){
        ui->textEdit->setText("Please select the input data file first");

    }else{

    ofstream OPdatafile(FileName);

    if ( ! OPdatafile.is_open()) {
          ui->label->setText("Unable to open file");
       }
           OPdatafile <<"Energy (keV),Counts"<<"\n";

           for(int i=0;i<NumOfLines;i++){
           OPdatafile <<energy[i]<<","<<count[i]<<"\n";
           }
OPdatafile.close();
ui->textEdit->setText("Data has been saved successfully to the file");
    }
}

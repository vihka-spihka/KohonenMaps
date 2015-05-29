#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    //QTabWidget *tabwidget = new QTabWidget(this);

    ui->tableWidget->setRowCount(10);   //строки
    ui->tableWidget->setColumnCount(7); //столбцы


    if(ui->inputFromFileRadioButton->isChecked())
    {
        on_inputFromFileRadioButton_clicked();
    }

    //not working
    connect(ui->tableWidget,SIGNAL(currentChanged(int)),this, SLOT(on_nextButton1_clicked(int)));
    connect(ui->buildButton, SIGNAL(clicked()), this, SLOT(accept()));


}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

//not working
void SettingsDialog::on_nextButton1_clicked(int index)
{
    QTabWidget *tabwidget = new QTabWidget(this);
    index = tabwidget->currentIndex();
    index++;
    tabwidget->setCurrentIndex(index);
    //tabwidget->widget(index);

}


bool SettingsDialog::on_buildButton_clicked(bool)
{
    close();
    return true;
}

void SettingsDialog::on_inputFromFileRadioButton_clicked()
{
    if(ui->inputFromFileRadioButton->isChecked())
    {
        ui->addColomnButton->setEnabled(false);
        ui->addRowButton->setEnabled(false);
        ui->borderCellCheckBox->setEnabled(false); //not working
        ui->borderClusterCheckBox->setEnabled(false); //not working
        ui->tableWidget->setEnabled(false);
        ui->chooseFileButton->setEnabled(true);
        //ui->inputFromFileRadioButton->setEnabled(true);

}
}

void SettingsDialog::on_inputSelfRadioButton_clicked()
{
    if(ui->inputSelfRadioButton->isChecked())
    {
        ui->addColomnButton->setEnabled(true);
        ui->addRowButton->setEnabled(true);
        ui->borderCellCheckBox->setEnabled(true);
        ui->borderClusterCheckBox->setEnabled(true);
        ui->tableWidget->setEnabled(true);
        ui->chooseFileButton->setEnabled(false);
    }
//не доделано
    if(ui->headlinesColomnsCheckBox->isChecked()){

      //первая строка таблицы модет содержать String, но при обучении не учитывается


    }
}

void SettingsDialog::on_addColomnButton_clicked()
{
    int colomn = ui->tableWidget->columnCount();
    colomn++;
    ui->tableWidget->setColumnCount(colomn);
}

void SettingsDialog::on_addRowButton_clicked()
{
    int row = ui->tableWidget->rowCount();
    row++;
    ui->tableWidget->setRowCount(row);
}

//not working
void SettingsDialog::on_chooseFileButton_clicked()
{
    //QFile mFile;
    QFileDialog *fileDlg = new QFileDialog(this);
    fileDlg->getOpenFileName(this,"Открыть документ","c:/", "Text files (*.txt);;XLS files (*.xls *xlsx)");
    //mFile = fileDlg->getOpenFileName(this,"Открыть документ","c:/", "Text files (*.txt)",QFileDialog::ReadOnly);
    //QTextStream stream(&mFile);

    ui->tableWidget->setEnabled(true);

    //for (int i=0; i<=mFile.size(), i++){
    //QString buffer = stream.readLine();
    //считывать по слову/числу в ячейки таблицы


    //QFile file("test.txt");
        /*if(mFile.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            while(!file.atEnd())
            {
                //Делим строку на слова разделенные пробелом
                QStringList lst = buffer.split("; ");
                  // выводим первых три слова
                //qDebug() << lst.at(0) << lst.at(1)<<lst.at(2);
            }

        }
        else
        {
            QMessageBox::information(this,"Ошибка","Невозможно использовать данный файл!");
            //qDebug()<< "don't open file";
        }*/

   // }



}

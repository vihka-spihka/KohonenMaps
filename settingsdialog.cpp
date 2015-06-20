#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{

    initValues();
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::clicked_save_inputs(){
    QString filePath = QFileDialog::getSaveFileName(this,"Сохранить файл","c:/","Text files (*.txt)");
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
   // QString strInFile;
    //QTextStream srt(strInFile);

    //out << str(strInFile);

    for (int i = 0; i < nameColumns.size(); i++){
        //out<<nameColumns;
        out<<",";
    }
    out<<"\n";
    for (int i = 0; i < nameRows.size(); i++){
        ui->tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(nameRows[i]));
    }

    for (int i = 0; i < nameRows.size(); i++)
        for (int j = 0; j < nameColumns.size(); j++) {
            ui->tableWidget->setItem(i,j, new QTableWidgetItem(QString::number(table[i][j])));
        }

    /*
  //Пример
  QString fr= QFileDialog::getSaveFileName(this,tr("Save"),"c:/",tr("CSV Files (*.csv)"));
  QFile file(fr);
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);
  out<<QObject::tr("Название;Автор;Год;Рейтинг\n");
   out.setCodec(QTextCodec::codecForName("windows-1251"));
for (int i=0;i<4;i++){
       for (int j=0;j<4;j++){
   out<<ui->tableWidget->item(i, j);
    out<<";";
        };
       out<<"\n";

  file.close();
*/
    file.close();
}

void SettingsDialog::on_chooseFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Открыть документ","c:/", "Text files (*.txt)");

    if (fileName != ""){ // Проверка чтобы файл существовал
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
                    QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                }
        else {
            QTextStream in(&file);
            //Конвертирование полученных данных
            ConverterInputData converter(fileName, in.readAll());

            nameRows = converter.getNameRows();
            nameColumns = converter.getNameColumns();
            table = converter.getTable();

            file.flush();//добавила сброс инфы с жесткого диска
            file.close();

            fillingTableWidget();
            ui->tableWidget->setEnabled(true);
        }
    }
}

// Заполнение виджета таблицы значениями, которые хранятся в векторах
void SettingsDialog::fillingTableWidget(){
    ui->tableWidget->setColumnCount(nameColumns.size());
    ui->tableWidget->setRowCount(nameRows.size());

    ui->spinBox_4->setValue(nameRows.size());
    ui->spinBox_5->setValue(nameColumns.size());

    for (int i = 0; i < nameColumns.size(); i++){
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(nameColumns[i]));
    }
    for (int i = 0; i < nameRows.size(); i++){
        ui->tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(nameRows[i]));
    }

    for (int i = 0; i < nameRows.size(); i++)
        for (int j = 0; j < nameColumns.size(); j++) {
            ui->tableWidget->setItem(i,j, new QTableWidgetItem(QString::number(table[i][j])));
        }
}

void SettingsDialog::on_nextButton1_clicked()
{
    if(ui->tableWidget->rowCount() >0 && ui->tableWidget->columnCount() >2){

        convertTableToVectors();

    int index = ui->tabWidget->currentIndex();
    index++;
    ui->tabWidget->setCurrentIndex(index);
    ui->tabWidget->setTabEnabled(1, true);
    }
    else
        QMessageBox::warning(this,"Ошибка!","Слишком мало столбцов или строк!");
}

void SettingsDialog::on_backButton1_clicked()
{
    int index = ui->tabWidget->currentIndex();
    index--;
    ui->tabWidget->setCurrentIndex(index);
}

void SettingsDialog::on_nextButton2_clicked()
{
    ui->tabWidget->setTabEnabled(2, true);
    int index = ui->tabWidget->currentIndex();
    index++;
    ui->tabWidget->setCurrentIndex(index);
}

void SettingsDialog::on_backButton2_clicked()
{
    int index = ui->tabWidget->currentIndex();
    index--;
    ui->tabWidget->setCurrentIndex(index);
}

void SettingsDialog::on_buildButton_clicked()
{
    emit closeWindow();
    this->close();

}

void SettingsDialog::on_spinBox_4_valueChanged(int arg1)
{
    int var = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(arg1);
    if (var < arg1) {
        bool ok;
    ui->tableWidget->setVerticalHeaderItem(
                ui->tableWidget->rowCount()-1,
                new QTableWidgetItem(
                    QInputDialog::getText(
                        this,
                        "Ввод названия строки",
                        "Название строки",
                        QLineEdit::Normal,
                        "Строка#" + QString::number(arg1),
                        &ok)));
        if (!ok) {
            ui->tableWidget->setRowCount(var);
            ui->spinBox_4->setValue(var);
        }
    }
}

void SettingsDialog::on_spinBox_5_valueChanged(int arg1)
{

    int var = ui->tableWidget->columnCount();
    ui->tableWidget->setColumnCount(arg1);
    if (var < arg1) {
        bool ok;
        ui->tableWidget->setHorizontalHeaderItem(
                ui->tableWidget->columnCount()-1,
                new QTableWidgetItem(
                    QInputDialog::getText(
                        this,
                        "Ввод названия столбца",
                        "Название столбца",
                        QLineEdit::Normal,
                        "Столбец#" + QString::number(arg1),
                        &ok)));
        if (!ok) {
            ui->tableWidget->setColumnCount(var);
            ui->spinBox_5->setValue(var);
        }
    }
}

void SettingsDialog::connects(){
}

void SettingsDialog::initValues(){

    ui->setupUi(this);
    ui->tableWidget->setRowCount(0);   //строки
    ui->tableWidget->setColumnCount(0); //столбцы
    ui->doubleSpinBox_5->setEnabled(false);
    ui->checkBox->setEnabled(false);

    checkedStopPoint = false;
    countRowsOutputLayout = 20;
    countColumnsOutputLayout = 20;
    countAge = 1000;
    stopPoint = 0.0;
    minimumTrainingRange = 1;
    maximumTrainingRange = 20;
    endTrainingSpeed = 0.1;
    startTrainingSpeed = 0.9;
    minWeight = 0;
    maxWeight = 255;
    hexOrSquare = false;
    stepOrAfterTrain = true;
    sizeStep = 100;
    visulization = false;

}

//Конвертирование данных таблицы в вектора
void SettingsDialog::convertTableToVectors(){
    nameRows.clear();
    nameColumns.clear();
    table.clear();

    for (int i = 0; i < ui->tableWidget->columnCount(); i++)
            nameColumns.push_back(ui->tableWidget->horizontalHeaderItem(i)-> text());

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
            nameRows.push_back(ui->tableWidget->verticalHeaderItem(i)->text());

    for (int i = 0; i < ui->tableWidget->rowCount(); i++){
            table.resize(table.size()+1);
            for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
                //if (table[i]='')
                  //      QMessageBox::warning(this,"lol","fuuuuck");
                table[i].push_back(ui->tableWidget->item(i,j)->text().toDouble());

            }
        }

    fillingTableWidget();

}

// count rows output layout
void SettingsDialog::on_spinBox_valueChanged(int arg1)
{
    countRowsOutputLayout = arg1;
}

// количество столбцов выходного слоя
void SettingsDialog::on_spinBox_2_valueChanged(int arg1)
{
    countColumnsOutputLayout = arg1;
}

// количество эпох
void SettingsDialog::on_spinBox_3_valueChanged(int arg1)
{
    countAge = arg1;
}
// значение точки останова
void SettingsDialog::on_doubleSpinBox_5_valueChanged(double arg1)
{
    stopPoint = arg1;
}
// Минимальный радиус обучения
void SettingsDialog::on_spinBox_6_valueChanged(int arg1)
{
    maximumTrainingRange = arg1;
}
// Максимальный радиус обучения
void SettingsDialog::on_spinBox_7_valueChanged(int arg1)
{
    minimumTrainingRange = arg1;
}
// Стартовая скорость обучения
void SettingsDialog::on_doubleSpinBox_valueChanged(double arg1)
{
    startTrainingSpeed = arg1;
}

void SettingsDialog::on_doubleSpinBox_2_valueChanged(double arg1)
{
    endTrainingSpeed = arg1;
}

// Минимальный вес
void SettingsDialog::on_doubleSpinBox_4_valueChanged(double arg1)
{
    minWeight = arg1;
}

void SettingsDialog::on_doubleSpinBox_3_valueChanged(double arg1)
{
    maxWeight = arg1;
}

void SettingsDialog::on_fourShapeRadioButton_toggled(bool checked)
{
        hexOrSquare = !checked;
}

void SettingsDialog::on_sixShapeRadioButton_toggled(bool checked)
{
        hexOrSquare = checked;
}

void SettingsDialog::on_stepDemoRadioButton_toggled(bool checked)
{
    stepOrAfterTrain = checked;
    ui->spinBox_9->setEnabled(checked);
}

void SettingsDialog::on_finishedDemoRadioButton_toggled(bool checked)
{
    stepOrAfterTrain = !checked;
    ui->checkBox->setEnabled(checked);
}

bool SettingsDialog::getStepOrAfterTrain() const
{
    return stepOrAfterTrain;
}

bool SettingsDialog::getHexOrSquare() const
{
    return hexOrSquare;
}

double SettingsDialog::getEndTrainingSpeed() const
{
    return endTrainingSpeed;
}

double SettingsDialog::getStartTrainingSpeed() const
{
    return startTrainingSpeed;
}

int SettingsDialog::getMaximumTrainingRange() const
{
    return maximumTrainingRange;
}

int SettingsDialog::getMinimumTrainingRange() const
{
    return minimumTrainingRange;
}

double SettingsDialog::getStopPoint() const
{
    return stopPoint;
}

double SettingsDialog::getMaxWeight() const
{
    return maxWeight;
}

double SettingsDialog::getMinWeight() const
{
    return minWeight;
}

int SettingsDialog::getCountAge() const
{
    return countAge;
}

int SettingsDialog::getCountColumnsOutputLayout() const
{
    return countColumnsOutputLayout;
}

int SettingsDialog::getCountRowsOutputLayout() const
{
    return countRowsOutputLayout;
}

vector<vector<double> > SettingsDialog::getTable() const
{
    return table;
}

vector<QString> SettingsDialog::getNameColumns() const
{
    return nameColumns;
}

vector<QString> SettingsDialog::getNameRows() const
{
    return nameRows;
}

void SettingsDialog::on_spinBox_9_valueChanged(int arg1)
{
    sizeStep = arg1;
}

int SettingsDialog::getSizeStep() const
{
    return sizeStep;
}

void SettingsDialog::on_checkBox_toggled(bool checked)
{
    visulization = checked;
}

bool SettingsDialog::getVisulization() const
{
    return visulization;
}


void SettingsDialog::on_cb_stopPoint_toggled(bool checked)
{
    ui->doubleSpinBox_5->setEnabled(checked);
    checkedStopPoint = checked;
}
bool SettingsDialog::getCheckedStopPoint() const
{
    return checkedStopPoint;
}


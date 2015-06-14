#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include <QMessageBox>
#include "ui_settingsdialog.h"
#include "vector"
#include <QDebug>
#include "converterinputdata.h"

using namespace std;

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);

    ~SettingsDialog();

    vector<QString> getNameRows() const;

    vector<QString> getNameColumns() const;

    vector<vector<double> > getTable() const;

    int getCountRowsOutputLayout() const;

    int getCountColumnsOutputLayout() const;

    int getCountAge() const;

    double getMinWeight() const;

    double getMaxWeight() const;

    double getStopPoint() const;

    int getMinimumTrainingRange() const;

    int getMaximumTrainingRange() const;

    double getStartTrainingSpeed() const;

    double getEndTrainingSpeed() const;

    double getWidthCell() const;

    bool getHexOrSquare() const;

    bool getStepOrAfterTrain() const;

    int getSizeStep() const;

    bool getVisulization() const;

    bool getCheckedStopPoint() const;

private slots:

    void on_chooseFileButton_clicked();

    void on_nextButton1_clicked();

    void on_backButton1_clicked();

    void on_nextButton2_clicked();

    void on_backButton2_clicked();

    void on_buildButton_clicked();

    void fillingTableWidget(); // функция заполняет таблицу, если ввод данных был из файла

    void on_spinBox_5_valueChanged(int arg1); // SetRowsCount

    void on_spinBox_4_valueChanged(int arg1); //SetColumnsCount

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_doubleSpinBox_5_valueChanged(double arg1);

    void on_spinBox_6_valueChanged(int arg1);

    void on_spinBox_7_valueChanged(int arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_fourShapeRadioButton_toggled(bool checked);

    void on_sixShapeRadioButton_toggled(bool checked);

    void on_stepDemoRadioButton_toggled(bool checked);

    void on_finishedDemoRadioButton_toggled(bool checked);

    void on_spinBox_9_valueChanged(int arg1);

    void on_checkBox_toggled(bool checked);

    void on_cb_stopPoint_toggled(bool checked);

signals:
    void closeWindow();

private:
    Ui::SettingsDialog *ui;

    vector <QString> nameRows;
    vector <QString> nameColumns;
    vector < vector <double> > table;

    int countRowsOutputLayout;
    int countColumnsOutputLayout;
    int countAge;
    double minWeight;
    double maxWeight;
    double stopPoint;
    int minimumTrainingRange;
    int maximumTrainingRange;
    double startTrainingSpeed;
    double endTrainingSpeed;
    int sizeStep;

    bool hexOrSquare; // Шестиугольная или прямоугольная карта будет. 1 - hex, 0 - square
    bool stepOrAfterTrain; // Пошагово или после обучения результат. 1 - step, 0 - after train
    bool visulization; // Показ изменений на карте при обучении
    bool checkedStopPoint; // 1- использовать точку останова
    void convertTableToVectors(); // конвертация таблицы в вектора

    void connects();
    void initValues();


};

#endif // SETTINGSDIALOG_H

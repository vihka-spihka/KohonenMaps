#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <vector>
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

signals:
    void newNetwork (double maxSpeedTraining,
                    double minSpeedTraining,
                    int minRange,
                    int maxRange,
                    double minCoegWeight,
                    double maxCoegWeight,
                    int numAge,
                    int numColumns,
                    int numRows,
                    vector<vector<double> > inputLayout);

private slots:

    void on_inputFromFileRadioButton_clicked();

    void on_inputSelfRadioButton_clicked();

    void on_addColomnButton_clicked();

    void on_addRowButton_clicked();

    void on_chooseFileButton_clicked();

    void on_headlinesColomnsCheckBox_clicked();

    void on_nextButton1_clicked();

    void on_backButton1_clicked();

    void on_nextButton2_clicked();

    void on_backButton2_clicked();

    void on_buildButton_clicked();

public slots:
    bool on_buildButton_clicked(bool);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H

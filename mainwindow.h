#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsdialog.h"
#include "network.h"

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
    void on_action_about_triggered();

    void on_action_info_triggered();

    void on_action_exit_triggered();

    void on_action_new_triggered();

    void nextStepButtonEnable();    //кнопка "След шаг" доступна

    void backToSettingsButtonEnable();  //кнопка "Назад к настройкам" доступна

    void newNetwork(double maxSpeedTraining,
                    double minSpeedTraining,
                    int minRange,
                    int maxRange,
                    double minCoegWeight,
                    double maxCoegWeight,
                    int numAge,
                    int numColumns,
                    int numRows,
                    vector<vector<double> > inputLayout);

private:
    Ui::MainWindow *ui;
    Network* network;
    SettingsDialog* setDlg;
};

#endif // MAINWINDOW_H

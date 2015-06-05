#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsdialog.h"
#include "network.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>

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

    void on_nextStepButton_clicked();

    void addRectangles();
    void changeRectangles();
    void nextStep();
    void addHexagons();

    void changeHexagons();
signals:



private:
    Ui::MainWindow *ui;
    Network* network;
    SettingsDialog* setDlg;
    QGraphicsScene *scene;
    QTimer *timer;
    int numIteration;
    int numRows;
    int numColumns;
    double widthCell;
    vector <vector <QGraphicsRectItem*> > vectorRectangles;
    vector <vector <QGraphicsPolygonItem*> > vectorHexagons;
    vector <vector <vector <double> > > vectorColors;
};

#endif // MAINWINDOW_H

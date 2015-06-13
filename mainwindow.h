#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsdialog.h"
#include "network.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>
#include <QScrollBar>

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

    void newNetwork();

    void on_nextStepButton_clicked();

    void addRectangles();

    void changeRectangles();

    void addHexagons();

    void changeHexagons();

    void stepByStepCalc();

    void withoutStepCalc();

    void changeItems();

    void on_backToSettingsButton_clicked();

    void on_pushButton_clicked();

signals:

private:

    void lastIteration();
    void resizeWidthCells();

    Ui::MainWindow *ui;
    Network* network;
    SettingsDialog* setDlg;
    QGraphicsScene *scene;
    QTimer *timer;

    int numIteration;
    int curIteration;
    int numRows;
    int numColumns;

    vector <vector <QGraphicsRectItem*> > vectorRectangles;
    vector <vector <QGraphicsPolygonItem*> > vectorHexagons;
    vector <vector <vector <double> > > vectorColors;

    vector <QString> nameRows;
    vector <QString> nameColumns;
    vector < vector <double> > inputLayout;

    int countAge;
    double minWeight;
    double maxWeight;
    double stopPoint;
    int minimumTrainingRange;
    int maximumTrainingRange;
    double startTrainingSpeed;
    double endTrainingSpeed;
    double widthCell;
    int sizeStep;
    bool hexOrSquare; // Шестиугольная или прямоугольная карта будет. 1 - hex, 0 - square
    bool stepOrAfterTrain; // Пошагово или после обучения результат. 1 - step, 0 - after train
    bool visulization; // Визуализация при непрерывном вычислении
    bool pause;

};

#endif // MAINWINDOW_H

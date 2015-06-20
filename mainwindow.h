#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QColor>
#include <QString>
#include <viewmaps.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void set_l_curAge(QString str);
    void set_l_curIteration(QString str);
    void set_l_curRange(QString str);
    void set_l_curTrainingSpeed(QString str);
    void set_l_nameInput(QString str);
    void set_l_coordX(QString str);
    void set_l_coordY(QString str);
    void set_l_nameFirstAttr(QString str);
    void set_l_nameSecondAttr(QString str);
    void set_l_nameThirdAttr(QString str);
    void set_l_valueFirstAttr(QString str);
    void set_l_valueSecondAttr(QString str);
    void set_l_valueThirdAttr(QString str);

    void setMaxMin_pb_iterator(int max, int min);
    void setValue_pb_iterator(int value);

    void setEnable_save_map(bool checked);
    void setEnable_save_inputs(bool checked);

    void setEnabled_b_nextStep(bool checked);
    void setEnabled_b_pause(bool checked);

    void setText_b_nextStep(QString str);

    void slotClicked_b_nextStep();
    void slotClicked_b_pause();
    void slotClicked_b_settings();

    void on_action_new_triggered();

    void on_action_about_triggered();

    void on_action_info_triggered();

    void on_action_exit_triggered();
    void on_action_saveMap();
    void on_action_saveInputs();

    void setEnabled_a_saveMap(bool checked);
    void setEnabled_a_saveInputs(bool checked);

    viewMaps* getGVMaps();

private slots:

    void resizeEvent(QResizeEvent* event);


   /* void on_action_about_triggered();
     
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

    void on_pushButton_clicked();*/
    

signals:
    
    void signalClicked_b_nextStep();
    void signalClicked_b_pause();
    void signalClicked_b_settings();
    void signalResizeWindow();
    void signalClicked_a_saveMap();
    void signalClicked_a_saveInputs();
    void signalClicked_a_info();
    void signalClicked_a_about();
    void signalClicked_a_exit();

    
private:
    
    void connects();
    Ui::MainWindow *ui;
    viewMaps *view;

    /*void lastIteration();
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
    bool pause;*/

};

#endif // MAINWINDOW_H

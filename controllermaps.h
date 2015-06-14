#ifndef CONTROLLERMAPS_H
#define CONTROLLERMAPS_H

#include "network.h"
#include "mainwindow.h"
#include "settingsdialog.h"
#include "viewmaps.h"
#include <QTime>
#include <QWidget>
#include <QTimer>

class controllerMaps : public QWidget
{
     Q_OBJECT

public:

    explicit controllerMaps(QWidget *parent = 0);

public slots:

    void show();

    void clicked_b_nextStep();
    void clicked_b_settings();
    void clicked_b_pause();
    void clicked_setDlg_buildMaps();
    
private slots:

    void updateWidthCells();
    void updateColorsTimer();
    void withoutStepCalc();
    void findInfoCell(int row, int column);

private:

    void connects();
    void stepCalc();
    void addItemsOnGraphicsView();
    void convertValueToColors();
    void updateInformation();
    bool compateExWAndCurW();
    
    MainWindow *window;
    SettingsDialog *dialog;
    Network *network;
    viewMaps *gv_maps;
    QTimer *timer;


    vector <QString> nameRows;
    vector <QString> nameColumns;
    vector < vector <double> > inputLayout;
    vector <vector <vector <int> > > colors;
    vector <vector <vector <double> > > exW;
    vector <vector <vector <double> > > currentW;


    int countIteration;
    int currentIteration;
    int countRows;
    int countColumns;

    int countAge;
    int minTrainingRange;
    int maxTrainingRange;
    int sizeStep;
    int countImages;

    bool viewHexagons;
    bool viewRectangles;
    bool calcStep;
    bool calcAfterTraining;
    bool visulization; // Визуализация при непрерывном вычислении
    bool pause;
    bool checkedStopPoint;

    double minWeight;
    double maxWeight;
    double stopPoint;
    double startTrainingSpeed;
    double endTrainingSpeed;
};

#endif // CONTROLLERMAPS_H

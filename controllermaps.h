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
    
private:
    void connects();
    
    MainWindow *window;
    SettingsDialog *dialog;
    Network *network;
    viewMaps *gv_maps;
    QTimer *timer;
    //vector <viewMaps*> gv_maps;
};

#endif // CONTROLLERMAPS_H

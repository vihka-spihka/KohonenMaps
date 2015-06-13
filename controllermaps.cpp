#include "controllermaps.h"

controllerMaps::controllerMaps(QWidget *parent) : QWidget(parent)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    
    window = new MainWindow(this);
    dialog = new SettingsDialog(this);
}

void controllerMaps::show(){
    window->show();
}

void controllerMaps::connects(){

    connect(window, SIGNAL(signalClicked_b_nextStep()),SLOT(clicked_b_nextStep()));
    connect(window, SIGNAL(signalClicked_b_pause()), SLOT(clicked_b_pause()));
    connect(window, SIGNAL(signalClicked_b_settings()), SLOT(clicked_b_settings()));
    connect(dialog, SIGNAL(closeWindow()), SLOT(clicked_setDlg_buildMaps()));

}

void controllerMaps::clicked_b_settings(){
    qDebug () << "click1";
    dialog->show();
}

void controllerMaps::clicked_b_nextStep(){

}

void controllerMaps::clicked_b_pause(){

}

void controllerMaps::clicked_setDlg_buildMaps(){

}


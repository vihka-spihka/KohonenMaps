#include "controllermaps.h"

controllerMaps::controllerMaps(QWidget *parent) : QWidget(parent)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    
    window = new MainWindow(this);
    dialog = new SettingsDialog(window);
    gv_maps = window->getGVMaps();
    timer = new QTimer();

    connects();
}

void controllerMaps::show(){
    window->show();
}

void controllerMaps::connects(){

    connect(window, SIGNAL(signalClicked_b_nextStep()),SLOT(clicked_b_nextStep()));
    connect(window, SIGNAL(signalClicked_b_pause()), SLOT(clicked_b_pause()));
    connect(window, SIGNAL(signalClicked_b_settings()), SLOT(clicked_b_settings()));
    connect(dialog, SIGNAL(closeWindow()), SLOT(clicked_setDlg_buildMaps()));
    connect(window, SIGNAL(signalResizeWindow()), this, SLOT(updateWidthCells()));
    connect(timer, SIGNAL(timeout()), SLOT(updateColorsTimer()));
}

void controllerMaps::clicked_b_settings(){
    dialog->show();
}

void controllerMaps::clicked_b_nextStep(){

    if (calcStep) {
        stepCalc();
    }
    else if (calcAfterTraining) {
        pause = false;
        window->setEnabled_b_nextStep(false);
        window->setEnabled_b_pause(true);
        withoutStepCalc();
    }

}

void controllerMaps::clicked_b_pause(){
    pause = true;
    window->setEnabled_b_nextStep(true);
    window->setEnabled_b_pause(false);
    timer->stop();
    updateColorsTimer();
}

void controllerMaps::clicked_setDlg_buildMaps(){

    countAge = dialog->getCountAge();
    countColumns = dialog->getCountColumnsOutputLayout();
    countRows = dialog->getCountRowsOutputLayout();
    minTrainingRange = dialog->getMinimumTrainingRange();
    maxTrainingRange = dialog->getMaximumTrainingRange();
    minWeight = dialog->getMinWeight();
    maxWeight = dialog->getMaxWeight();
    sizeStep = dialog->getSizeStep();
    startTrainingSpeed = dialog->getStartTrainingSpeed();
    endTrainingSpeed = dialog->getEndTrainingSpeed();
    visulization = dialog->getVisulization();
    stopPoint = dialog->getStopPoint();

    viewHexagons = dialog->getHexOrSquare();
    viewRectangles = !dialog->getHexOrSquare();
    calcStep = dialog->getStepOrAfterTrain();
    calcAfterTraining = !dialog->getStepOrAfterTrain();

    inputLayout = dialog->getTable();
    nameRows = dialog->getNameRows();
    nameColumns = dialog->getNameColumns();

    currentIteration = 1;
    countImages = inputLayout.size();
    countIteration = countImages * countAge;
    pause = false;
    timer->stop();

    window->setMaxMin_pb_iterator(countIteration, 1);
    window->setValue_pb_iterator(1);

    network = new Network(
                startTrainingSpeed,
                endTrainingSpeed,
                minTrainingRange,
                maxTrainingRange,
                minWeight,
                maxWeight,
                countAge,
                countRows,
                countColumns,
                inputLayout);

    if (calcStep) {
        window->setText_b_nextStep("Следующий шаг");
        window->setEnabled_b_nextStep(true);
        window->setEnabled_b_pause(false);
    }
    else if (calcAfterTraining) {
        window->setText_b_nextStep("Старт");
        window->setEnabled_b_nextStep(true);
        window->setEnabled_b_pause(false);
    }


    addItemsOnGraphicsView();
}

void controllerMaps::convertValueToColors(){
    currentW = network->getW();
    for (int i = 0; i < countRows; i++) {
        for (int j = 0; j < countColumns; j++) {
            for (int k = 0; k < countImages; k++) {
                colors[i][j][k] = 255*((currentW[i][j][k]-minWeight)/(maxWeight-minWeight)); 
            }
        }
    }
}

void controllerMaps::addItemsOnGraphicsView(){

    colors.resize(countRows);
    for(int i = 0; i < countRows; i++) {
        colors[i].resize(countColumns);
        for(int j = 0; j < countColumns; j++){
            colors[i][j].resize(countImages);
            for (int k = 0; k < countImages; k++)
                colors[i][j][k] = 255;
        }
    }

    gv_maps->setColors(colors);

    if (viewHexagons)
        gv_maps->setViewHexagons();
    else if (viewRectangles)
        gv_maps->setViewRectangles();
}

void controllerMaps::stepCalc(){

    int varSize = currentIteration + sizeStep;
    if (currentIteration < countIteration){
        while (currentIteration % varSize) {
            network->nextStep();
            currentIteration++;
            updateInformation();
        }
        convertValueToColors();
        gv_maps->updateColors(colors);
    }
}

void controllerMaps::withoutStepCalc(){
    if (currentIteration <= countIteration && !pause){
        network->nextStep();
        updateInformation();
        timer->start(1);
    }
    else {
        window->setEnabled_b_nextStep(false);
        window->setEnabled_b_pause(false);
    }

}

void controllerMaps::updateColorsTimer(){
    if (visulization || currentIteration == countIteration || pause) {
        convertValueToColors();
        gv_maps->updateColors(colors);
    }
    currentIteration++;
    withoutStepCalc();
}

void controllerMaps::updateWidthCells(){
    if (colors.size())
        gv_maps->updateWidthCells();
}

void controllerMaps::updateInformation(){

    window->setValue_pb_iterator(currentIteration);
    window->set_l_curAge(QString::number(network->getCurAge()+1));
    window->set_l_curIteration(QString::number(currentIteration-1));
    window->set_l_curRange(QString::number(network->getCurRange()));
    window->set_l_curTrainingSpeed(QString::number(network->getCurSpeedTraining()));
}

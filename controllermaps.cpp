#include <QImage>
#include <QPainter>
#include <QTextStream>
#include <QFile>

#include "controllermaps.h"
#include "viewmaps.h"

controllerMaps::controllerMaps(QWidget *parent) : QWidget(parent)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    
    window = new MainWindow(this);
    dialog = new SettingsDialog(window);
    instruction = new InstructionDialog(window);
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
    connect(gv_maps, SIGNAL(selectedItem(int,int)),SLOT(findInfoCell(int,int)));
    connect(instruction,SIGNAL(closeWindow()),SLOT(clicked_b_close_info()));
    connect(window,SIGNAL(signalClicked_a_info()),SLOT(clicked_a_info()));
    connect(window,SIGNAL(signalClicked_a_about()),SLOT(clicked_a_about()));
    connect(window,SIGNAL(signalClicked_a_exit()),SLOT(clicked_a_exit()));
    connect(window, SIGNAL(signalClicked_a_saveMap()),gv_maps,SLOT(clicked_a_save_map()));
    connect(window,SIGNAL(signalClicked_a_saveInputs()),SLOT(clicked_a_save_inputs()));
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
    checkedStopPoint = dialog->getCheckedStopPoint();

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

    exW = network->getW();

    if (calcStep) {
        window->setText_b_nextStep("Следующий шаг");
        window->setEnabled_b_nextStep(true);
        window->setEnabled_b_pause(false);
        window->setEnabled_a_saveInputs(true);
        window->setEnabled_a_saveMap(true);

    }
    else if (calcAfterTraining) {
        window->setText_b_nextStep("Старт");
        window->setEnabled_b_nextStep(true);
        window->setEnabled_b_pause(false);        
        window->setEnabled_a_saveInputs(true);
        window->setEnabled_a_saveMap(true);
    }

    findInfoCell(0,0);
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

    if (checkedStopPoint) {
        if (!compateExWAndCurW()) {
            if (currentIteration < countIteration ){
                while (currentIteration % varSize) {
                    network->nextStep();
                    currentIteration++;
                    updateInformation();
                }
                convertValueToColors();
                gv_maps->updateColors(colors);
            }
        }
    }
    else {
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
}

bool controllerMaps::compateExWAndCurW(){
    if (currentIteration == 1)
        return false;
    currentW = network->getW();
    for (int i = 0; i < currentW.size(); i++)
        for (int j = 0; j < currentW[i].size(); j++)
            for (int k = 0; k < currentW[i][j].size(); k++) {
                if (fabs(exW[i][j][k]-currentW[i][j][k]) >= stopPoint) {
                    exW = currentW;
                    return false;
                }
            }
    return true;

}

void controllerMaps::withoutStepCalc(){
    if (checkedStopPoint) {
        if (!compateExWAndCurW()) {
            if (currentIteration <= countIteration){
                if (!pause){
                    network->nextStep();
                    updateInformation();
                    timer->start(1);
                }
            }
            else {
                timer->stop();
                window->setEnabled_b_nextStep(false);
                window->setEnabled_b_pause(false);
                window->setEnable_save_map(true);
                window->setEnable_save_inputs(true);
            }
        }
        else{
            timer->stop();
            window->setEnabled_b_nextStep(false);
            window->setEnabled_b_pause(false);
            window->setEnable_save_map(true);
            window->setEnable_save_inputs(true);

        }
    }
    else {
        if (currentIteration <= countIteration){
            if (!pause){
                network->nextStep();
                updateInformation();
                timer->start(1);
            }
        }
        else {
            window->setEnabled_b_nextStep(false);
            window->setEnabled_b_pause(false);
            window->setEnable_save_map(true);
            window->setEnable_save_inputs(true);
        }
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

void controllerMaps::findInfoCell(int row, int column){
    vector <double> value_images_cell = network->getW()[row][column];

    window->set_l_nameFirstAttr(nameColumns[0]);
    window->set_l_nameSecondAttr(nameColumns[1]);
    window->set_l_nameThirdAttr(nameColumns[2]);
    window->set_l_valueFirstAttr(QString::number(value_images_cell[0]));
    window->set_l_valueSecondAttr(QString::number(value_images_cell[1]));
    window->set_l_valueThirdAttr(QString::number(value_images_cell[2]));
    window->set_l_coordX(QString::number(row+1));
    window->set_l_coordY(QString::number(column+1));
    window->set_l_nameInput(nameRows[network->getIdentLayout(row, column)]);
}

void controllerMaps::clicked_b_close_info(){
    instruction->close();
}

void controllerMaps::clicked_a_info(){
    instruction->show();
}

void controllerMaps::clicked_a_about(){

}

void controllerMaps::clicked_a_exit(){
    window->close();
}

void controllerMaps::clicked_a_save_map(){

}

void controllerMaps::clicked_a_save_inputs(){

    QString fileName = QFileDialog::getSaveFileName(window, tr("Сохранить файл"), "",
        "Text Files (*.txt)");

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                // error message
            } else {
                QTextStream stream(&file);
                stream << convertDataToString();
                stream.flush();
                file.close();
            }
        }

    /*//QString filePath = QFileDialog::getSaveFileName(this,"Сохранить файл","c:/","Text files (*.txt)");
    //QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    for (int i = 0; i < nameColumns.size(); i++){
        //out<<nameColumns;
        out<<",";
    }
    out<<"\n";
    for (int i = 0; i < nameRows.size(); i++){
        ui->tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(nameRows[i]));
    }

    for (int i = 0; i < nameRows.size(); i++)
        for (int j = 0; j < nameColumns.size(); j++) {
            ui->tableWidget->setItem(i,j, new QTableWidgetItem(QString::number(table[i][j])));
        }

    file.close();*/
}

QString controllerMaps::convertDataToString(){
    QString str = "";

    for(int i = 0; i < nameColumns.size(); i++){
        if (i == nameColumns.size()-1)
            str += nameColumns[i] + QString("\n");
        else
            str += nameColumns[i] + QString(",");
    }

    for (int i = 0; i < nameRows.size(); i++){
        str += nameRows[i] + QString(",");
        for (int j = 0; j < nameColumns.size(); j++){
            if (j == nameColumns.size()-1)
                str += QString::number(inputLayout[i][j]) + QString("\n");
            else
                str += QString::number(inputLayout[i][j]) + QString(",");
        }
    }
    return str;
}

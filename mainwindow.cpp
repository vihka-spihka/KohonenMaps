#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Готов к работе!");

    ui->nextStepButton->setEnabled(false);
    setDlg = new SettingsDialog(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    timer = new QTimer(this);
    qDebug() << ui->graphicsView->width();
    curIteration = 1;

    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());

    connect(setDlg, SIGNAL(closeWindow()),SLOT(newNetwork()));
    connect(timer, SIGNAL(timeout()), this, SLOT(changeItems()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_about_triggered()    //показать справку
{
    QMessageBox::information(this,"О программе","<h4>Выпускная квалификационная работа на тему: </h4><i>Разработка программного эмулятора карты Кохонена для использования в учебном процессе.</i>\n<b>Автор:</b> Князева В.К., ФКТИ, группа 1303");
}

void MainWindow::on_action_info_triggered() //показать инструкцию
{
    //InstructionDialog *instruction = new InstructionDialog(this);
    //instruction->show();
}

void MainWindow::on_action_exit_triggered() //выход из программы
{
    close();
}

void MainWindow::on_action_new_triggered()  //создать новую карту Кохонена
{
    setDlg->show();
}

void MainWindow::nextStepButtonEnable(){
    ui->nextStepButton->setEnabled(true);
    ui->backToSettingsButton->setEnabled(true);
}

void MainWindow::newNetwork(){

    this->numColumns = setDlg->getCountColumnsOutputLayout();
    this->numRows = setDlg->getCountRowsOutputLayout();
    this->inputLayout = setDlg->getTable();
    this->widthCell = setDlg->getWidthCell();
    this->countAge = setDlg->getCountAge();
    this->minWeight = setDlg->getMinWeight();
    this->maxWeight = setDlg->getMaxWeight();
    this->stopPoint = setDlg->getStopPoint();
    this->maximumTrainingRange = setDlg->getMaximumTrainingRange();
    this->minimumTrainingRange = setDlg->getMinimumTrainingRange();
    this->startTrainingSpeed = setDlg->getStartTrainingSpeed();
    this->endTrainingSpeed = setDlg->getEndTrainingSpeed();
    this->hexOrSquare = setDlg->getHexOrSquare();
    this->stepOrAfterTrain = setDlg->getStepOrAfterTrain();
    this->sizeStep = setDlg->getSizeStep();
    this->visulization = setDlg->getVisulization();


    network = new Network(startTrainingSpeed,
                          endTrainingSpeed,
                          minimumTrainingRange,
                          maximumTrainingRange,
                          minWeight,
                          maxWeight,
                          countAge,
                          numColumns,
                          numRows,
                          inputLayout);

    numIteration = countAge * inputLayout.size();
    ui->progressBar->setMinimum(1);
    ui->progressBar->setMaximum(numIteration);

    ui->nextStepButton->setEnabled(true);
    curIteration = 1;

    if (hexOrSquare)
        addHexagons();
    else
        addRectangles();

}

void MainWindow::addHexagons(){
    scene->clear();
    double varRows = 0;
    vectorHexagons.resize(numRows);
    for(int i = 0; i < numRows; i++){
        double varColumns;
            if(i % 2)
                varColumns = 0;
            else
                varColumns = widthCell/2;
        vectorHexagons[i].resize(numColumns);
        for(int j = 0; j < numColumns; j++){
            vectorHexagons[i][j] = scene->addPolygon(QPolygonF(
            QVector<QPointF> ()
                        << QPointF(varRows+widthCell/3,varColumns)
                        << QPointF(varRows,varColumns+widthCell/2)
                        << QPointF(varRows+widthCell/3,varColumns+widthCell)
                        << QPointF(varRows+2*widthCell/3,varColumns+widthCell)
                        << QPointF(varRows+widthCell,varColumns+widthCell/2)
                        << QPointF(varRows+2*widthCell/3,varColumns)
                      ),QPen(Qt::NoPen));


            varColumns+=widthCell;
        }
        varRows+=2*widthCell/3;
    }
}

void MainWindow::addRectangles(){
    scene->clear();
    int varRows = 0;
    vectorRectangles.resize(numRows);
    for (int i = 0; i < numRows; i++) {
        int varColumns = 0;
        vectorRectangles[i].resize(numColumns);
        for(int j = 0; j < numColumns; j++){
            vectorRectangles[i][j] = scene->addRect(varRows, varColumns, widthCell, widthCell, QPen(Qt::NoPen),QBrush(Qt::red));
            //vectorRectangles[i][j]->setPen(QPen(Qt::black, 0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin));

            varColumns+=widthCell;
        }
        varRows+=widthCell;
    }
}

void MainWindow::changeRectangles(){
    vectorColors = network->getW();
    for (int i = 0; i < numRows; i++) {
        for(int j = 0; j < numColumns; j++){
           vectorRectangles[i][j]->setBrush(QBrush(QColor(
                                      vectorColors[i][j][0],
                                      vectorColors[i][j][1],
                                      vectorColors[i][j][2])));
        }
    }
}

void MainWindow::changeHexagons(){
    vectorColors = network->getW();
    for (int i = 0; i < numRows; i++) {
        for(int j = 0; j < numColumns; j++){
           vectorHexagons[i][j]->setBrush(QBrush(QColor(
                                      vectorColors[i][j][0],
                                      vectorColors[i][j][1],
                                      vectorColors[i][j][2])));
        }
    }
}

void MainWindow::on_nextStepButton_clicked()
{
    if (stepOrAfterTrain)
        stepByStepCalc();
    else {
        ui->nextStepButton->setEnabled(false);
        withoutStepCalc();
    }
}

void MainWindow::stepByStepCalc(){
    if ((curIteration+inputLayout.size()) >= numIteration)
        lastIteration();
    else {
        int var = curIteration + sizeStep;

        while (curIteration % var) {
            network->nextStep();
            ui->curAge->setText(QString::number(network->getCurAge() + 1));
            ui->curIter->setText(QString::number(curIteration));
            ui->curSpeedTraining->setText(QString::number(network->getCurSpeedTraining()));
            ui->curRange->setText(QString::number(network->getCurRange()));
            ui->progressBar->setValue(curIteration);
            curIteration++;
            if (curIteration == numIteration) {
                ui->nextStepButton->setEnabled(false);
                break;
            }
        }

        if (hexOrSquare)
            changeHexagons();
        else
            changeRectangles();
    }
}

void MainWindow::withoutStepCalc(){
    if (curIteration < numIteration-inputLayout.size()){

        ui->curAge->setText(QString::number(network->getCurAge()));
        ui->curIter->setText(QString::number(curIteration));
        ui->curSpeedTraining->setText(QString::number(network->getCurSpeedTraining()));
        ui->curRange->setText(QString::number(network->getCurRange()));
        ui->progressBar->setValue(curIteration);

        network->nextStep();
        timer->start(1);
    }
    else
        lastIteration();
}

void MainWindow::changeItems(){
    if (hexOrSquare) {
        if (visulization)
            changeHexagons();
        curIteration++;
        withoutStepCalc();
    }
    else {
        if (visulization)
            changeRectangles();
        curIteration++;
        withoutStepCalc();
    }
}
void MainWindow::lastIteration(){
    if (hexOrSquare)
        changeHexagons();
    else
        changeRectangles();
}

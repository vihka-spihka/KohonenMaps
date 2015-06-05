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

    ui->backToSettingsButton->setEnabled(false);
    setDlg = new SettingsDialog(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    timer = new QTimer(this);
    qDebug() << ui->graphicsView->width();

    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());

     connect(setDlg,
            SIGNAL(newNetwork(double,double,int,int,double,double,int,int,int,vector<vector<double> >)),
            this,
            SLOT(newNetwork(double,double,int,int,double,double,int,int,int,vector<vector<double> >)));
    connect(timer, SIGNAL(timeout()), this, SLOT(changeHexagons()));
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

void MainWindow::backToSettingsButtonEnable(){
    //SettingsDialog *settingsDlg = new SettingsDialog(this);
    //if(settingsDlg->on_buildButton_clicked(true))
    //{
      //  ui->nextStepButton->setEnabled(true);
        //ui->backToSettingsButton->setEnabled(true);
    //}
}

void MainWindow::newNetwork(double maxSpeedTraining, double minSpeedTraining, int minRange, int maxRange, double minCoegWeight, double maxCoegWeight, int numAge, int numColumns, int numRows, vector<vector<double> > inputLayout){

    network = new Network(maxSpeedTraining,
                          minSpeedTraining,
                          minRange,
                          maxRange,
                          minCoegWeight,
                          maxCoegWeight,
                          numAge,
                          numColumns,
                          numRows,
                          inputLayout);

    this->numRows = numRows;
    this->numColumns = numColumns;
    numIteration = numAge * inputLayout.size();
    widthCell = 10;
    //addRectangles();
    addHexagons();

}
void MainWindow::addHexagons(){
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
void MainWindow::nextStep(){
    if(numIteration > 0) {
        network->nextStep();
        qDebug() << "Iteration: " << numIteration;
        qDebug() << "Age: " << network->getCurAge();


        timer->start(1);
        numIteration--;
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
    numIteration--;
    nextStep();
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

    numIteration--;
    nextStep();
}


void MainWindow::on_nextStepButton_clicked()
{
    nextStep();
}

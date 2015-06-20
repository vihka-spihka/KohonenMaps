#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    view = ui->gv_maps;
    ui->action_saveMap->setEnabled(false);
    ui->action_saveInputs->setEnabled(false);
    ui->b_nextStep->setEnabled(false);
    ui->b_pause->setEnabled(false);

    connects();

}

void MainWindow::connects(){
    
    connect(ui->b_nextStep, SIGNAL(clicked(bool)), SLOT(slotClicked_b_nextStep()));
    connect(ui->b_pause, SIGNAL(clicked(bool)), SLOT(slotClicked_b_pause()));
    connect(ui->b_settings, SIGNAL(clicked()), this, SIGNAL(signalClicked_b_settings()));
    connect(ui->action_new,SIGNAL(triggered()),this,SIGNAL(signalClicked_b_settings()));
    connect(ui->action_saveMap,SIGNAL(triggered()),this,SIGNAL(signalClicked_a_saveMap()));
    connect(ui->action_saveInputs, SIGNAL(triggered()),this,SIGNAL(signalClicked_a_saveInputs()));
    connect(ui->action_info,SIGNAL(triggered()),this,SIGNAL(signalClicked_a_info()));
    connect(ui->action_about,SIGNAL(triggered()),this,SIGNAL(signalClicked_a_about()));
    connect(ui->action_exit,SIGNAL(triggered()),this,SIGNAL(signalClicked_a_exit()));
}

void MainWindow::resizeEvent(QResizeEvent *event){

    QMainWindow::resizeEvent(event);

    emit signalResizeWindow();
}

void MainWindow::slotClicked_b_pause(){
    emit signalClicked_b_pause();
}

void MainWindow::slotClicked_b_nextStep(){
    
    emit signalClicked_b_nextStep();
}

void MainWindow::slotClicked_b_settings(){

    emit signalClicked_b_settings();
}

void MainWindow::set_l_curAge(QString str) {
    ui->l_curAge->setText(str);
}

void MainWindow::set_l_curIteration(QString str){
    ui->l_curIteration->setText(str);
}

void MainWindow::set_l_curRange(QString str){
    ui->l_curRange->setText(str);
}

void MainWindow::set_l_curTrainingSpeed(QString str){
    ui->l_curSpeedTraining->setText(str);
}

void MainWindow::set_l_nameInput(QString str){
    ui->l_nameInput->setText(str);
}

void MainWindow::set_l_coordX(QString str)
{
    ui->l_coordX->setText(str);
}

void MainWindow::set_l_coordY(QString str){
    ui->l_coordY->setText(str);
}

void MainWindow::set_l_nameFirstAttr(QString str){
    ui->l_nameFirstAttr->setText(str);
}

void MainWindow::set_l_nameSecondAttr(QString str){
    ui->l_nameSecondAttr->setText(str);
}

void MainWindow::set_l_nameThirdAttr(QString str){
    ui->l_nameThirdAttr->setText(str);
}

void MainWindow::set_l_valueFirstAttr(QString str){
    ui->l_valueFirstAttr->setText(str);
}

void MainWindow::set_l_valueSecondAttr(QString str){
    ui->l_valueSecondAttr->setText(str);
}

void MainWindow::set_l_valueThirdAttr(QString str){
    ui->l_valueThirdAttr->setText(str);
}

void MainWindow::setMaxMin_pb_iterator(int max, int min)
{
    ui->pb_iteration->setMaximum(max);
    ui->pb_iteration->setMinimum(min);
}

void MainWindow::setValue_pb_iterator(int value)
{
    ui->pb_iteration->setValue(value);
}

void MainWindow::setEnabled_b_nextStep(bool checked){
    ui->b_nextStep->setEnabled(checked);
}

void MainWindow::setEnabled_b_pause(bool checked){
    ui->b_pause->setEnabled(checked);
}

void MainWindow::setEnable_save_map(bool checked){
      ui->action_saveMap->setEnabled(checked);
}

void MainWindow::setEnable_save_inputs(bool checked){
    ui->action_saveInputs->setEnabled(checked);
}

void MainWindow::setText_b_nextStep(QString str){
    ui->b_nextStep->setText(str);
}

viewMaps* MainWindow::getGVMaps(){
    return view;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_saveMap(){
    emit signalClicked_a_saveMap();
}

void MainWindow::on_action_saveInputs(){
    emit signalClicked_a_saveInputs();
}

void MainWindow::on_action_about_triggered()    //показать справку
{
    emit signalClicked_a_about();
    QMessageBox::information(this,"О программе","<h4>Выпускная квалификационная работа на тему: </h4><i>Разработка программного эмулятора карты Кохонена для использования в учебном процессе.</i>\n<b>Автор:</b> Князева В.К., ФКТИ, группа 1303");
}

void MainWindow::on_action_info_triggered() //показать инструкцию
{
   emit signalClicked_a_info();
}

void MainWindow::on_action_exit_triggered() //выход из программы
{
    emit signalClicked_a_exit();
}

void MainWindow::on_action_new_triggered()  //создать новую карту Кохонена
{
    emit signalClicked_b_settings();
}

/*
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
    pause = false;

    if (stepOrAfterTrain) {
        ui->nextStepButton->setText("Следующий шаг");
        ui->pushButton->setEnabled(false);
    }
    else {
        ui->nextStepButton->setText("Старт");
        ui->pushButton->setEnabled(true);
    }

    resizeWidthCells();

    if (hexOrSquare)
        addHexagons();
    else
        addRectangles();

}

void MainWindow::resizeWidthCells(){

    double var_h = (this->height()-100)/numRows;
    double var_v = (this->width()-20)/numColumns;

    double min_w, max_w;

    if (var_h > var_v) {
        min_w = var_v;
        max_w = var_h;
    }
    else {
        max_w = var_v;
        min_w = var_h;
    }

    this->widthCell = min_w;
    double iterator = (max_w-min_w)/100;

    for (double value = min_w; value < max_w; value+=iterator){


        double temp_length_height = value*numColumns;
        double temp_length_width = value*numRows;

        double diff_height = (this->height()-100) - temp_length_height;
        double diff_width = (this->width()-20) - temp_length_width;

        if (diff_height <= 0 || diff_width <= 0) {
            this->widthCell = value;
            break;
        }
    }
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
    scene->setSceneRect(0,0,widthCell*numColumns, widthCell*numRows);
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

            varColumns+=widthCell;
        }
        varRows+=widthCell;
    }
    scene->setSceneRect(0,0,widthCell*numColumns, widthCell*numRows);
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
    connect(this, SIGNAL())
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
        ui->pushButton->setEnabled(true);
        pause = false;
        withoutStepCalc();
    }
}

void MainWindow::stepByStepCalc(){
    if (curIteration >= numIteration-inputLayout.size())
        lastIteration();
    else {
        int var = curIteration + sizeStep;

        while (curIteration % var) {
            network->nextStep();
            ui->curAge->setText(QString::number(network->getCurAge() + 1) + "/" +QString::number(countAge));
            ui->curIter->setText(QString::number(curIteration)+"/"+QString::number(numIteration));
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
    if (curIteration < numIteration-inputLayout.size() && !pause){

        ui->curAge->setText(QString::number(network->getCurAge() + 1) + "/" +QString::number(countAge));
        ui->curIter->setText(QString::number(curIteration)+"/"+QString::number(numIteration));
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
    ui->pushButton->setEnabled(false);
    ui->nextStepButton->setEnabled(false);
    if (hexOrSquare)
        changeHexagons();
    else
        changeRectangles();
}

void MainWindow::on_backToSettingsButton_clicked()
{
    setDlg->show();
}

void MainWindow::on_pushButton_clicked()
{
    pause = true;
    timer->stop();
    ui->nextStepButton->setEnabled(true);
    ui->pushButton->setEnabled(false);
}*/

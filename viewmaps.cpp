#include "viewmaps.h"
#include <QFile>
#include <QFileDialog>
#include <QMouseEvent>
#include "QDebug"

viewMaps::viewMaps(QWidget *parent) : QGraphicsView(parent)
{
    this->setParent(parent);
    this->scene = new QGraphicsScene();
    this->setScene(this->scene);

    this->widthCell = 5;
    this->countColumns = 0;
    this->countRows = 0;

    this->viewHexagons = false;
    this->viewRectangles = true;
}

void viewMaps::setWidthCell(double value)
{
    widthCell = value;
    updateWidthCells();
}

void viewMaps::clicked_a_save_map(){

    QImage image(scene->width(), scene->height(), QImage::Format_ARGB32_Premultiplied);
    image.fill(NULL);
    QPainter painter(&image);
    scene->render(&painter);
    QString filePath = QFileDialog::getSaveFileName(this,"Сохраненить файл", "c:/", "Image files (*.png)");
    //QString fileName = QFileDialog::getOpenFileName(this,"Открыть документ","c:/", "Text files (*.txt)");
    image.save(filePath);
}

void viewMaps::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton){
        if (this->scene->itemAt(event->pos(),QTransform())) {
            itemSelected->setSelected(false);
            itemSelected = this->scene->itemAt(event->pos(), QTransform());
            itemSelected->setSelected(true);

            for (int i = 0; i < pos_x_items.size(); i++) {
                for (int j = 0; j < pos_x_items[i].size(); j++) {
                    if (pos_x_items[i][j] == itemSelected->x()) {
                        //qDebug() << "x" << i << j;
                        if (pos_y_items[i][j] == itemSelected->y()){

                          //  qDebug() << "y" << i << j;
                            emit selectedItem(i, j);

                        }
                    }
                }
            }
        }
    }
}

void viewMaps::setViewHexagons(){
    this->viewHexagons = true;
    this->viewRectangles = false;
    rectangles.clear();
    addHexagons();
}

void viewMaps::setViewRectangles(){
    this->viewHexagons = false;
    this->viewRectangles = true;
    hexagons.clear();
    addRectangles();
}

void viewMaps::updateWidthCells(){
    resizeWidthCells();
    if (viewHexagons){
        updateWidthCellsHexagons();
    }
    else if (viewRectangles){
        updateWidthCellsRectangles();
    }
}

void viewMaps::updateWidthCellsHexagons(){
    double varRows = 0;
    hexagons.resize(countRows);

    for (int i = 0; i < hexagons.size(); i++){

        double varColumns;
            if(i % 2)
                varColumns = 0;
            else
                varColumns = widthCell/2;
        hexagons[i].resize(countColumns);

        for (int j = 0; j < hexagons[i].size(); j++){
            hexagons[i][j]->setPolygon( QPolygonF( QVector<QPointF> ()
                                    << QPointF(widthCell/3,0)
                                    << QPointF(0,0+widthCell/2)
                                    << QPointF(0+widthCell/3,0+widthCell)
                                    << QPointF(0+2*widthCell/3,0+widthCell)
                                    << QPointF(0+widthCell,0+widthCell/2)
                                    << QPointF(0+2*widthCell/3,0)));

            varColumns+=widthCell;
            hexagons[i][j]->setPos(varRows, varColumns);
        }
        varRows+=2*widthCell/3;
    }
     this->scene->setSceneRect(0,0,widthCell*countColumns, widthCell*countRows);
    
}

int viewMaps::getColumnsSelectedItems() const
{
    return columnsSelectedItems;
}

int viewMaps::getRowSelectedItems() const
{
    return rowSelectedItems;
}

void viewMaps::updateWidthCellsRectangles(){
    int varRows = 0;
    rectangles.resize(countRows);
    for (int i = 0; i < countRows; i++) {
        int varColumns = 0;
        rectangles[i].resize(countColumns);
        for(int j = 0; j < countColumns; j++){
            rectangles[i][j]->setRect(
                        0,
                        0,
                        widthCell,
                        widthCell);

            varColumns+=widthCell;
            rectangles[i][j]->setPos(varRows, varColumns);
        }
        varRows+=widthCell;
    }
    this->scene->setSceneRect(0,0,widthCell*countColumns, widthCell*countRows);
}

void viewMaps::addHexagons(){
    scene->clear();
    int varRows = 0;
    hexagons.resize(countRows);
    pos_x_items.resize(countRows);
    pos_y_items.resize(countRows);
    for(int i = 0; i < countRows; i++){
        int varColumns;
            if(i % 2)
                varColumns = 0;
            else
                varColumns = widthCell/2;
        hexagons[i].resize(countColumns);
        pos_x_items[i].resize(countColumns);
        pos_y_items[i].resize(countColumns);
        for(int j = 0; j < countColumns; j++){
            hexagons[i][j] = scene->addPolygon(QPolygonF(
            QVector<QPointF> ()
                        << QPointF(widthCell/3,0)
                        << QPointF(0,0+widthCell/2)
                        << QPointF(0+widthCell/3,0+widthCell)
                        << QPointF(0+2*widthCell/3,0+widthCell)
                        << QPointF(0+widthCell,0+widthCell/2)
                        << QPointF(0+2*widthCell/3,0)
                      ),QPen(Qt::NoPen));

            hexagons[i][j]->setPos(varRows, varColumns);
            hexagons[i][j]->setFlags(QGraphicsItem::ItemIsSelectable);
            pos_x_items[i][j] = varRows;
            pos_y_items[i][j] = varColumns;

            varColumns+=widthCell;
        }
        varRows+=2*widthCell/3;
    }
    itemSelected = hexagons[0][0];
    rowSelectedItems = 0;
    columnsSelectedItems = 0;
    itemSelected->setSelected(true);
    this->scene->setSceneRect(0,0,widthCell*countColumns, widthCell*countRows);
    updateHexagons();
}

void viewMaps::addRectangles(){
    this->scene->clear();
    int varRows = 0;
    rectangles.resize(countRows);
    pos_x_items.resize(countRows);
    pos_y_items.resize(countRows);
    for (int i = 0; i < countRows; i++) {
        int varColumns = 0;
        rectangles[i].resize(countColumns);
        pos_x_items[i].resize(countColumns);
        pos_y_items[i].resize(countColumns);
        for(int j = 0; j < countColumns; j++){
            rectangles[i][j] = scene->addRect(
                        0,
                        0,
                        widthCell,
                        widthCell,
                        QPen(Qt::NoPen));
            rectangles[i][j]->setPos(varRows, varColumns);
            rectangles[i][j]->setFlags(QGraphicsItem::ItemIsSelectable);
            pos_x_items[i][j] = varRows;
            pos_y_items[i][j] = varColumns;
            varColumns+=widthCell;
        }
        varRows+=widthCell;
    }
    itemSelected = rectangles[0][0];
    rowSelectedItems = 0;
    columnsSelectedItems = 0;
    itemSelected->setSelected(true);

    this->scene->setSceneRect(0,0,widthCell*countColumns, widthCell*countRows);
    updateRectangles();
}

void viewMaps::updateColors(vector<vector<vector<int> > > &value)
{

    colors = value;
    countRows = value.size();
    countColumns = value[0].size();

    if (viewHexagons)
        updateHexagons();
    else if (viewRectangles)
        updateRectangles();
}

void viewMaps::setColors(vector<vector<vector<int> > > &value)
{
    colors = value;

    countRows = value.size();
    countColumns = value[0].size();

    resizeWidthCells();
}

void viewMaps::resizeWidthCells(){


    double var_h = (this->parentWidget()->height()-100)/countRows;
    double var_v = (this->parentWidget()->width()-200)/countColumns;

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


        double temp_length_height = value*countColumns;
        double temp_length_width = value*countRows;

        double diff_height = (this->parentWidget()->height()-100) - temp_length_height;
        double diff_width = (this->parentWidget()->width()-200) - temp_length_width;

        if (diff_height <= 0 || diff_width <= 0) {
            if (widthCell > 5)
                this->widthCell = value;
            else
                this->widthCell = 5;
            break;
        }
    }
    this->scene->setSceneRect(0,0,widthCell*countColumns, widthCell*countRows);
}

void viewMaps::updateRectangles(){
    for (int i = 0; i < countRows; i++) {
        for(int j = 0; j < countColumns; j++){
           rectangles[i][j]->setBrush(QBrush(QColor(
                                      colors[i][j][0],
                                      colors[i][j][1],
                                      colors[i][j][2])));
        }
    }
}

void viewMaps::updateHexagons(){
    for (int i = 0; i < countRows; i++) {
        for(int j = 0; j < countColumns; j++){
           hexagons[i][j]->setBrush(QBrush(QColor(
                                      colors[i][j][0],
                                      colors[i][j][1],
                                      colors[i][j][2])));
        }
    }
}



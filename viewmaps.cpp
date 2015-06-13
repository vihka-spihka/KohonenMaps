#include "viewmaps.h"

viewMaps::viewMaps(QWidget *parent, QGraphicsView *view)
{
    this->setParent(parent);
    this->scene = new QGraphicsScene();
    view->setScene(this->scene);

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
                                    << QPointF(varRows+widthCell/3,varColumns)
                                    << QPointF(varRows,varColumns+widthCell/2)
                                    << QPointF(varRows+widthCell/3,varColumns+widthCell)
                                    << QPointF(varRows+2*widthCell/3,varColumns+widthCell)
                                    << QPointF(varRows+widthCell,varColumns+widthCell/2)
                                    << QPointF(varRows+2*widthCell/3,varColumns)));

            varColumns+=widthCell;
        }
        varRows+=2*widthCell/3;
    }
     this->scene->setSceneRect(0,0,widthCell*countColumns, widthCell*countRows);
    
}

void viewMaps::updateWidthCellsRectangles(){
    int varRows = 0;
    rectangles.resize(countRows);
    for (int i = 0; i < countRows; i++) {
        int varColumns = 0;
        rectangles[i].resize(countColumns);
        for(int j = 0; j < countColumns; j++){
            rectangles[i][j]->setRect(
                        varRows,
                        varColumns,
                        widthCell,
                        widthCell);

            varColumns+=widthCell;
        }
        varRows+=widthCell;
    }
    this->scene->setSceneRect(0,0,widthCell*countColumns, widthCell*countRows);
}

void viewMaps::addHexagons(){
    scene->clear();
    double varRows = 0;
    hexagons.resize(countRows);
    for(int i = 0; i < countRows; i++){
        double varColumns;
            if(i % 2)
                varColumns = 0;
            else
                varColumns = widthCell/2;
        hexagons[i].resize(countColumns);
        for(int j = 0; j < countColumns; j++){
            hexagons[i][j] = scene->addPolygon(QPolygonF(
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
    this->scene->setSceneRect(0,0,widthCell*countColumns, widthCell*countRows);
    updateHexagons();
}

void viewMaps::addRectangles(){
    this->scene->clear();
    int varRows = 0;
    rectangles.resize(countRows);
    for (int i = 0; i < countRows; i++) {
        int varColumns = 0;
        rectangles[i].resize(countColumns);
        for(int j = 0; j < countColumns; j++){
            rectangles[i][j] = scene->addRect(
                        varRows,
                        varColumns,
                        widthCell,
                        widthCell,
                        QPen(Qt::NoPen));
            
            varColumns+=widthCell;
        }
        varRows+=widthCell;
    }
    this->scene->setSceneRect(0,0,widthCell*countColumns, widthCell*countRows);
    updateRectangles();
}

void viewMaps::updateColors(const vector<vector<vector<int> > > &value)
{
    colors = value;
    countRows = value.size();
    countColumns = value[0].size();

    resizeWidthCells();

    if (viewHexagons)
        updateHexagons();
    else if (viewRectangles)
        updateRectangles();
}

void viewMaps::setColors(const vector<vector<vector<int> > > &value)
{
    colors = value;
    countRows = value.size();
    countColumns = value[0].size();

    resizeWidthCells();
}

void viewMaps::resizeWidthCells(){

    double var_h = (this->parentWidget()->height()-100)/countRows;
    double var_v = (this->parentWidget()->width()-20)/countColumns;

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

        double diff_height = (this->height()-100) - temp_length_height;
        double diff_width = (this->width()-20) - temp_length_width;

        if (diff_height <= 0 || diff_width <= 0) {
            this->widthCell = value;
            break;
        }
    }
    updateWidthCells();
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


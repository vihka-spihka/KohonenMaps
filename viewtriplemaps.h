#ifndef VIEWTRIPLEMAPS_H
#define VIEWTRIPLEMAPS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <vector>
using namespace std;

class viewMaps : public QGraphicsView
{
public:
    viewMaps();
    
public slots:

    void resizeWidthCells();                                // Функция автоматического подбора размера ширины ячейки (работает при каждом обновлении цвета)
    void updateColors(
            const vector<vector<vector<int> > > &value);    // Функция обновления цвета в ячейках
    void setColors(
            const vector<vector<vector<int> > > &value);    // Функция изначального "задавания" цвета в ячейках. Первая функция после инициализации
    void setViewHexagons();                                 // Выбор гексагонального вида ячеек
    void setViewRectangles();                               // Выбор прямоугольного вида ячеек
    void setWidthCell(double value);                        // Явное задавание размера ячеек
    
private:

    void updateRectangles();    // Обноавление прямоугольников
    void updateHexagons();      // Обновление шестиугольников
    void addRectangles();       // Добавление прямоугольников
    void addHexagons();         // Добавление шестиугольников

    int countRows;              // Количество строк
    int countColumns;           // Количество столбцов
    bool viewHexagons;          // Гексагональное ли отображение? 1 - да, 0 - нет
    bool viewRectangles;        // Прямоугольное ли отображение? 1 - да, 0 - нет
    double widthCell;           // Ширина ячейки

    vector <vector <QGraphicsRectItem*> > rectangles;   // Карта прямоугольников
    vector <vector <QGraphicsPolygonItem*> > hexagons;  // Карта шестиугольников
    vector <vector <vector <int> > > colors;            // Вектор цветов
    QGraphicsScene* scene;                              // Сцена
};

#endif // VIEWTRIPLEMAPS_H

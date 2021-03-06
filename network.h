#ifndef NETWORK_H
#define NETWORK_H

#include "vector"
#include "neuron.h"
#include "math.h"

using namespace std;

class Network
{
public:
    Network(
            double maxSpeedTraining,    //Максимальная скорость обучения <1
            double minSpeedTraining,    //Минимальная скорость обучения >0.1
            int minRange,               // Минимальный радиус >=1
            int maxRange,               // Максимальный радиус
            double minCoegWeight,       // Максимальное ограничение на весовой коэффициент
            double maxCoegWeight,       // Минимальное ограничение на весовой коэффициент
            int numAge,                 // Количество эпох
            int numColumns,             // Количество столбцов выходного слоя
            int numRows,                // Количество строк выходного слоя
            //vector <string> nameRows, // Имена стобцов (да да косяк)
            //vector <string> nameColumns, // Имена строк (да да косяк) входного слоя
            vector < vector <double> > inputLayout // Таблица значений входного слоя
            );

    void nextStep(); // Выполнение алгоритма за одну итерацию
    double getCurSpeedTraining(); //Получение текущей скорости обучения
    int getCurRange(); // Получение текущего радиуса
    int getCurAge(); // Получение текущей эпохи
    int getCurIter(); // Получение текущей итерации
    int getCurXWin(); //Получение позиции нейрона-победителя - X
    int getCurYWin(); //Получение позиции нейрона-победителя - Y
    int getIdentLayout(int row, int column); // Получение идентфикатора входного примера, к которому ближе всего нейрон
    vector <double> getCurInputData(); //Получение текущих входных данных
    vector <vector <vector <double> > > getW(); // Получение состояний выходного слоя после ввода текущих входных данных
    //string getCurNameRows();

private:
    void showData(); //Дебаг функция - показ параметров сети
    void calcSpeedTraining(); // Подсчет текущей скорости обучения
    void calcRange(); //Подсчет радиуса соседства
    void calcIter(); //Подсчет текущей итерации и эпохи
    void createOutputLayout(); //Создание (заполнение) выходного слоя нейронов
    void inputData(); //Ввод текущих данных в матрицу
    void findWinnerNeuron(); //Поиск нейрона победителя
    void changeW(); //Изменение весовых коэффициентов
    void showW(); //Дебаг функция - показ выходных коэффициентов

    double maxSpeedTraining;
    double minSpeedTraining;
    double minCoegWeight;
    double maxCoegWeight;

    //Текущие значения
    double curSpeedTraining;
    int curRange;
    int curAge;
    int curIter;
    int curXWin;
    int curYWin;

    //Предыдущие на одну итерацию значения. Нужны для вывода данных
    double ex_curSpeedTraining;
    int ex_curRange;
    int ex_curAge;
    int ex_curIter;

    int minRange;
    int maxRange;
    int numAge;
    int numColumns;
    int numRows;


    //vector <string> nameRows;
    //vector <string> nameColumns;
    vector <bool> vectorCurIter;
    vector < vector <double> > inputLayout;
    vector < vector <Neuron*> > outputLayout; //2мерный вектор указателей на объект нейрон (к createNeuron)
};

#endif // NETWORK_H

#include "neuron.h"

#include "QTime"

Neuron::Neuron(int numRows, int x, int y, double maxCoegWeight, double minCoegWeight){
    this->x = x; //положение вых нейрона
    this->y = y; //положение вых нейрона
    this->numRows = numRows; //размерность входных векторов (кол-во вх нейронов)
    this->maxCoegWeight = maxCoegWeight; //максимальный коэффициент веса
    this->minCoegWeight = minCoegWeight;

    createW(); //создаем веса
}

void Neuron::createW(){ //создаем 1 вектор весов нейрона выходного слоя
    for (int i = 0; i < numRows; i++) { //идем по строкам
        double var = (double)qrand()/RAND_MAX; //возвращает результат с максимальной точностью (числа после ,)
        W.push_back(var*(maxCoegWeight-minCoegWeight) + minCoegWeight); //создаем рандомное double число
    }
};
void Neuron::inputData(vector <double> X){
    this->X = X; //входной вектор
};
double Neuron::getDistance(){ //определяем расстояния до каждого нейрона выходного слоя (связано с функцией findWinnerNeuron)
    double var = 0;
    for(int i = 0; i < X.size(); i++) //проходим по всем элементам вектора Х
        var += ((X[i]-W[i])*(X[i]-W[i])); //высчитываем расстояния дл каждого нейрона выходного слоя
    return var;
};
void Neuron::changeW(double speedTraining, int range) { //изменяем веса нейрона
    for(int i = 0; i < W.size(); i++) { //проходимся по каждому элементу вектора весов нейрона
        double var = W[i] + speedTraining*range*(X[i]-W[i]); //изменяем его веса
        if (var <= minCoegWeight) //если i-ый вес оказался меньше разрешенного,
            W[i] = minCoegWeight; //присваеваем ему мин разрешенное значение
        else if (var >= maxCoegWeight) //если i-ый вес оказался больше максимального разрешенного,
            W[i] = maxCoegWeight; // присваеваем ему максимальный разрешенный
        else
            W[i] = var; //если все хорошо, просто записываем новый вес вместо старого i-ого
    }
};
vector <double> Neuron::getW(){ //получаем веса
    return W;
}

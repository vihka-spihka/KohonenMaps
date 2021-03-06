#include "network.h"
#include "QDebug"

Network::Network(
        double maxSpeedTraining,
        double minSpeedTraining,
        int minRange,
        int maxRange,
        double minCoegWeight,
        double maxCoegWeight,
        int numAge,
        int numColumns,
        int numRows,
        //vector<string> nameRows,
        //vector<string> nameColumns,
        vector<vector<double> > inputLayout
        ){

    this->maxSpeedTraining = maxSpeedTraining;
    this->minSpeedTraining = minSpeedTraining;
    this->minRange = minRange;
    this->maxRange = maxRange;
    this->minCoegWeight = minCoegWeight;
    this->maxCoegWeight = maxCoegWeight;
    this->numAge = numAge;
    this->numColumns = numColumns;
    this->numRows = numRows;
    //this->nameRows = nameRows;
    //this->nameColumns = nameColumns;
    this->inputLayout = inputLayout;
    this->vectorCurIter.resize(inputLayout.size());

    this->curAge = 0; //номер эпохи на данный момент
    this->curIter = 0; //номер итерации на данный момент
    this->curSpeedTraining = 0; //скорость обучения на данный момент
    this->curRange = 0; //радиус соседства на данный момент
    this->curXWin = 0; //координата Х нейрона-победителя на данный момент
    this->curYWin = 0; //координата У нейрона-победителя на данный момент

    this->ex_curAge = 0; //номер предыдущей эпохи
    this->ex_curIter = 0; //номер предыдущей итерации
    this->ex_curRange = 0; //предыдущее значение радиуса
    this->ex_curSpeedTraining = 0; //предыдущее значение скорости обучения

    createOutputLayout();

};

int Network::getIdentLayout(int row, int column){
    return outputLayout[row][column]->getIdentLayout(inputLayout);
}

int Network::getCurAge(){
    return ex_curAge;
};
double Network::getCurSpeedTraining(){
    return ex_curSpeedTraining;
}
int Network::getCurIter(){
    return ex_curIter;
}
int Network::getCurRange(){
    return ex_curRange;
}
int Network::getCurXWin(){
    return curXWin;
}
int Network::getCurYWin(){
    return curYWin;
}
vector <vector <vector <double> > > Network::getW(){
    vector <vector <vector <double> > > var; //вектор двухмерных векторов, которые в себе хранят одномерные вектора
    var.resize(outputLayout.size()); //кол-во двухмерных векторов
    for(int i = 0; i < outputLayout.size(); i++){
        var[i].resize(outputLayout[i].size());
        for(int j = 0; j < outputLayout[i].size(); j++){
            vector <double > temp = outputLayout[i][j]->getW(); //полученный вектор весов
            var[i][j].resize(temp.size()); //подгоняем размер до размера вектора весовых коэф.
            for (int k = 0; k < temp.size(); k++){ //одномерный вектор. проходим по нему
                var[i][j][k] = temp[k]; //присваеваем значения
            }
        }
    }
    return var;
}
vector <double> Network::getCurInputData(){ //получение вх данных с предыд. итерации (вектор вх данных же не один)
    return inputLayout[ex_curIter];
}

/*string Network::getCurNameRows(){
    return nameColumns[ex_curIter];
}\*/
void showOneStrVector(vector <string> array){
    //for (int i = 0; i < array.size(); i++)
        //qDebug() << array[i] << " ";
}
void showTwoDoubleVector(vector < vector <double> > array){
    for (int i = 0; i < array.size(); i++) {
        for(int j = 0; j < array[i].size(); j++)
            qDebug() << array [i][j] << " ";
        qDebug() << "\n";
    }
}
void Network::showW(){
    for(int i = 0; i < outputLayout.size(); i++){
        for(int j = 0; j < outputLayout[i].size(); j++){
            vector <double> var = outputLayout[i][j]->getW();
            for (int k = 0; k < var.size(); k++)
                qDebug() << int(var[k]) << ",";
            qDebug() << " | ";
        }
        qDebug() << "\n";
    }
}
void Network::showData(){
    qDebug() << "\n maxSpeedTraining = " << maxSpeedTraining;
    qDebug() << "\n minSpeedTraining = " << minSpeedTraining;
    qDebug() << "\n minRange = " << minRange;
    qDebug() << "\n maxRange = " << maxRange;
    qDebug() << "\n minCoegWeight = " << minCoegWeight;
    qDebug() << "\n maxCoegWeight = " << maxCoegWeight;
    qDebug() << "\n numAge = " << numAge;
    qDebug() << "\n numColumns = " << numColumns;
    qDebug() << "\n numRows = " << numRows;

    //qDebug() << "\nnameRows\n";
    //showOneStrVector(nameRows);

    //qDebug() << "\nnameColumns\n";
    //howOneStrVector(nameColumns);

    qDebug() << "\ninputLayout\n";
    showTwoDoubleVector(inputLayout);
}
void Network::createOutputLayout(){

    outputLayout.resize(numRows); //изменяем кол-во строк вых слоя
    for(int i = 0; i < numRows; i++)
        outputLayout[i].resize(numColumns); //изменяем кол-во столбцов вых слоя для каждой строки

    for(int i = 0; i < numRows; i++) //проходим поэтапно по строкам
        for(int j = 0; j < numColumns; j++) //на j-ой строке проходим по столбцам
            outputLayout[i][j] = new Neuron( //создаем объект класса нейрон
                        inputLayout[0].size(), //кол-во входных нейронов или кол-во в векторе W для 1-ого нейрона
                        i, // координата по Х
                        j, //координата по У
                        maxCoegWeight,
                        minCoegWeight);
}
void Network::nextStep(){
    calcRange();
    calcSpeedTraining();
    inputData();
    findWinnerNeuron();
    changeW();
    calcIter();
}
void Network::inputData(){
    for(int i = 0; i < outputLayout.size(); i++) { //от 0 до кол-ва строк
        for(int j = 0; j < outputLayout[i].size(); j++) { //от 0 до кол-ва элементов в i-ой строке
            outputLayout[i][j]->inputData(inputLayout[curIter]); //будут входные данные со сходного слоя на данной итерации
        }
    }

}
void Network::findWinnerNeuron(){
    vector <vector <double> > var;
    var.resize(outputLayout.size()); //подгоняем до размеров выходного слоя
    for (int i = 0; i < outputLayout.size(); i++) {
        var[i].resize(outputLayout[i].size());
        for(int j = 0; j < outputLayout[i].size(); j++) {
            var[i][j] = outputLayout[i][j]->getDistance(); //создаем 2мерный ветор расстояний до соответсттвующих нейронов выходного слоя
        }
    }

    int x_min = qrand() % outputLayout.size();
    int y_min = qrand() % outputLayout[0].size();

    double min = var[x_min][y_min]; //берем за минимальный нейрон 0,0

    for (int i = 0; i < var.size(); i++)
        for(int j = 0; j < var[i].size(); j++)
            if (var[i][j] <= min) { //если текущий элемент меньше минимума то он им становится
                min = var[i][j];
                x_min = i;
                y_min = j;
            }
     curXWin = x_min;
     curYWin = y_min;
}
void Network::changeW(){ //определяем: изменение каких именно нейронов будет происходить
    int x = curXWin;
    int y = curYWin;
    for(int i = -curRange; i < curRange+1; i++){ //поиск соседей
        for (int j = -curRange; j < curRange+1; j++){
            if( ((x+i) < outputLayout.size() && (x+i) >= 0) && //если по Х нейрон находится в рамках сети
                ((y+j) < outputLayout[0].size() && (y+j) >= 0)) {
                int dist = i*i+j*j;
                double var = exp(double(-dist)/double((2*curRange*curRange)));
                /*if (abs(i) > abs(j)) //если по строкам (асболютное значение по модулю) дальше, чем по столбцам,
                    range = (curRange+1)-abs(i); // то радиус соседства= номеру строки
                if (abs(j) > abs(i)) //если по столбцам дальше, чем по строкам,
                    range = (curRange+1)-abs(j); //то радиус=номеру столбца
                if (abs(i) == abs(j)) //если номер строки и столбца равны
                    range = (curRange+1)-abs(i); //то неважно, что брать, пусть будет i*/
                outputLayout[x+i][y+j]->changeW(curSpeedTraining, var); //у нейронов в зоне радиуса обучения меняем весы
            }
        }
    }
};
void Network::calcSpeedTraining(){
    ex_curSpeedTraining = curSpeedTraining;
    curSpeedTraining = maxSpeedTraining*
                    pow(minSpeedTraining/maxSpeedTraining,double(curAge)/double(numAge));
}
void Network::calcIter(){
    ex_curIter = curIter;
    ex_curAge = curAge;

    bool var = true;
    while(var){
        curIter = qrand() % inputLayout.size();
        if (vectorCurIter[curIter] == false) {
            var = false;
            vectorCurIter[curIter] = true;
        }
    }
    bool temp = true;
    for (int i = 0; i < vectorCurIter.size(); i++)
        if (vectorCurIter[i] == false)
            temp = false;

   /* curIter = (curIter+1) % inputLayout.size(); //ищем остаток от деления
    if(curIter == 0) //если дошли до конца входного слоя нейронов, повышаем кол-во эпох
        curAge++;*/
    if (temp) {
        curAge++;
        for(int i = 0; i < vectorCurIter.size(); i++)
            vectorCurIter[i] = false;
    }
};
void Network::calcRange(){
    ex_curRange = curRange;
    curRange = double(maxRange)*
                pow(double(minRange)/double(maxRange),double(curAge)/double(numAge));
}


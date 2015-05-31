#include "network.h"

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

    this->curAge = 0;
    this->curIter = 0;
    this->curSpeedTraining = 0;
    this->curRange = 0;
    this->curXWin = 0;
    this->curYWin = 0;

    this->ex_curAge = 0;
    this->ex_curIter = 0;
    this->ex_curRange = 0;
    this->ex_curSpeedTraining = 0;


    showData();

    createOutputLayout();

};

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
    vector <vector <vector <double> > > var;
    var.resize(outputLayout.size());
    for(int i = 0; i < outputLayout.size(); i++){
        var[i].resize(outputLayout[i].size());
        for(int j = 0; j < outputLayout[i].size(); j++){
            vector <double > temp = outputLayout[i][j]->getW();
            var[i][j].resize(temp.size());
            for (int k = 0; k < temp.size(); k++){
                var[i][j][k] = temp[k];
            }
        }
    }
    return var;
}
vector <double> Network::getCurInputData(){
    return inputLayout[ex_curIter];
}

/*string Network::getCurNameRows(){
    return nameColumns[ex_curIter];
}\*/
void showOneStrVector(vector <string> array){
    for (int i = 0; i < array.size(); i++)
        cout << array[i] << " ";
}
void showTwoDoubleVector(vector < vector <double> > array){
    for (int i = 0; i < array.size(); i++) {
        for(int j = 0; j < array[i].size(); j++)
            cout << array [i][j] << " ";
        cout << "\n";
    }
}
void Network::showW(){
    for(int i = 0; i < outputLayout.size(); i++){
        for(int j = 0; j < outputLayout[i].size(); j++){
            vector <double> var = outputLayout[i][j]->getW();
            for (int k = 0; k < var.size(); k++)
                cout << int(var[k]) << ",";
            cout << " | ";
        }
        cout << "\n";
    }
}
void Network::showData(){
    cout << "\n maxSpeedTraining = " << maxSpeedTraining;
    cout << "\n minSpeedTraining = " << minSpeedTraining;
    cout << "\n minRange = " << minRange;
    cout << "\n maxRange = " << maxRange;
    cout << "\n minCoegWeight = " << minCoegWeight;
    cout << "\n maxCoegWeight = " << maxCoegWeight;
    cout << "\n numAge = " << numAge;
    cout << "\n numColumns = " << numColumns;
    cout << "\n numRows = " << numRows;

    //cout << "\nnameRows\n";
    //showOneStrVector(nameRows);

    //cout << "\nnameColumns\n";
    //howOneStrVector(nameColumns);

    cout << "\ninputLayout\n";
    showTwoDoubleVector(inputLayout);
}
void Network::createOutputLayout(){

    outputLayout.resize(numRows);
    for(int i = 0; i < numRows; i++)
        outputLayout[i].resize(numColumns);

    for(int i = 0; i < numRows; i++)
        for(int j = 0; j < numColumns; j++)
            outputLayout[i][j] = new Neuron(
                        inputLayout[0].size(),
                        i,
                        j,
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
    for(int i = 0; i < outputLayout.size(); i++) {
        for(int j = 0; j < outputLayout[i].size(); j++) {
            outputLayout[i][j]->inputData(inputLayout[curIter]);
        }
    }

}
void Network::findWinnerNeuron(){
    vector <vector <double> > var;
    var.resize(outputLayout.size());
    for (int i = 0; i < outputLayout.size(); i++) {
        var[i].resize(outputLayout[i].size());
        for(int j = 0; j < outputLayout[i].size(); j++) {
            var[i][j] = outputLayout[i][j]->getDistance();
        }
    }

    double min = var[0][0];
    double x_min = 0;
    double y_min = 0;

    for (int i = 0; i < var.size(); i++)
        for(int j = 0; j < var[i].size(); j++)
            if (var[i][j] < min) {
                min = var[i][j];
                x_min = i;
                y_min = j;
            }
     curXWin = x_min;
     curYWin = y_min;
}
void Network::changeW(){
    int x = curXWin;
    int y = curYWin;
    for(int i = -curRange; i < curRange+1; i++){
        for (int j = -curRange; j < curRange+1; j++){
            if( ((x+i) < outputLayout.size() && (x+i) >= 0) &&
                ((y+j) < outputLayout[0].size() && (y+j) >= 0)
              ) {
                int range = 1;
                if (i == 0 && j == 0)
                    range = 1;
                if (abs(i) > abs(j))
                    range = abs(i);
                if (abs(j) > abs(i))
                    range = abs(j);
                if (abs(i) == abs(j))
                    range = abs(i);
                outputLayout[x+i][y+j]->changeW(curSpeedTraining, range);
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
    curIter = (curIter+1) % inputLayout.size();
    if(curIter == 0)
        curAge++;
};
void Network::calcRange(){
    ex_curRange = curRange;
    curRange = double(maxRange)*
                pow(double(minRange)/double(maxRange),double(curAge)/double(numAge));
}


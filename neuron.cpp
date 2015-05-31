#include "neuron.h"

#include "QTime"

Neuron::Neuron(int numRows, int x, int y, double maxCoegWeight, double minCoegWeight){
    this->x = x;
    this->y = y;
    this->numRows = numRows;
    this->maxCoegWeight = maxCoegWeight;
    this->minCoegWeight = minCoegWeight;

    createW();
}

void Neuron::createW(){
    for (int i = 0; i < numRows; i++) {
        double var = (double)qrand()/RAND_MAX;
        W.push_back(var*(maxCoegWeight-minCoegWeight) + minCoegWeight);
    }
};
void Neuron::inputData(vector <double> X){
    this->X = X;
};
double Neuron::getDistance(){
    double var = 0;
    for(int i = 0; i < X.size(); i++)
        var += ((X[i]-W[i])*(X[i]-W[i]));
    return var;
};
void Neuron::changeW(double speedTraining, int range) {
    for(int i = 0; i < W.size(); i++) {
        double var = W[i] + speedTraining*range*(X[i]-W[i]);
        if (var <= minCoegWeight)
            W[i] = minCoegWeight;
        else if (var >= maxCoegWeight)
            W[i] = maxCoegWeight;
        else
            W[i] = var;
    }
};
vector <double> Neuron::getW(){
    return W;
}

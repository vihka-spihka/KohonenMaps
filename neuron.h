#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include "iostream"
#include "math.h"

using namespace std;

class Neuron
{
public:
    Neuron(
            int numRows,
            int x,
            int y,
            double maxCoegWeight,
            double minCoegWeight
            );

    void inputData(vector <double> &X);
    void changeW(double speedTraining, double range);
    double getDistance();
    vector <double> getW();
    int getIdentLayout(vector <vector <double> > &arrayX);
private:
    double calcDistance(vector <double> array);
    void createW();
    int x;
    int y;
    int numRows;

    double maxCoegWeight;
    double minCoegWeight;

    vector <double> W;
    vector <double> X;

};

#endif // NEURON_H

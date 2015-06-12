#ifndef CONVERTERINPUTDATA_H
#define CONVERTERINPUTDATA_H

#include <vector>
#include <QTextStream>
#include <QString>
#include <QDebug>

using namespace std;

class ConverterInputData
{

public:
    ConverterInputData(QString fileName, QString fileString);

    vector <QString> getNameColumns();
    vector <QString> getNameRows();
    vector < vector <double> > getTable();
private:
    QString fileName;
    QString fileString;

    vector <QString> nameColumns;
    vector <QString> nameRows;
    vector < vector <double> > table;

    int determiningFormatFile(); // Функция определения формата файла
    void convertFromTxt();
};

#endif // CONVERTERINPUTDATA_H

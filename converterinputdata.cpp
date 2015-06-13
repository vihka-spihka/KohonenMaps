#include "converterinputdata.h"

ConverterInputData::ConverterInputData(QString fileName, QString fileString)
{
    this->fileName = fileName;
    this->fileString = fileString;

    switch (determiningFormatFile()) {
    case 1: // txt
        convertFromTxt();
        break;
    default:
        qDebug() << "Все плохо";
        break;
    }
}

// Функция для определения формата файла.
// Она проходит по названию с конца и если натыкается на точку,
// то останавливается и возвращает найденный формат
int ConverterInputData::determiningFormatFile(){
    QString var = "";

    for (int i = fileName.size()-1; i > 0; i--){
        if (fileName[i] == QChar('.'))
            break;
        else
            var.push_front(fileName[i]);
    }
    if (var == "txt")
        return 1;
    else
        return 0;
}
// Конвертирование из txt файла
void ConverterInputData::convertFromTxt(){
    // Разделителем будет запятая
    int i = 0; // итератор прохода по всему тексту
    QString var = "";

    nameRows.resize(0);
    nameColumns.resize(0);
    table.resize(1);

    // Получение названия стобцов
    for (; i < fileString.size(); i++){
        if (fileString[i] == QChar(',')) {
            nameColumns.push_back(var);
            var = "";
            continue;
        }
        if (fileString[i] == QChar('\n')){
            nameColumns.push_back(var);
            i++;
            break;
        }
        var.push_back(fileString[i]);
    }

    // Получение названия строк и таблицы

    bool nRows = true; // Если true, то имя присвоится nameRows иначе table
    int iterRow = 0;
    var = "";

    for (; i < fileString.size(); i++){
        if (fileString[i] == QChar(',')){
            if (nRows) {
                nRows = false;
                nameRows.push_back(var);
            }
            else {
                table[iterRow].push_back(var.toDouble());
            }
            var = "";
            continue;
        }
        if (fileString[i] == QChar('\n')){
            table[iterRow].push_back(var.toDouble());
            table.resize(table.size()+1);
            iterRow++;
            nRows = true;
            var = "";
            continue;
        }
        var.push_back(fileString[i]);
    }
}

vector <QString> ConverterInputData::getNameColumns(){
    return nameColumns;
};
vector <QString> ConverterInputData::getNameRows(){
    return nameRows;
};
vector < vector <double> > ConverterInputData::getTable(){
    return table;
};

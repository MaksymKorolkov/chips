#include "matrix.h"
#include "qdebug.h"
#include "regression.h"

#include <QDir>
#include <QFile>
#include <QtGlobal>

regression::regression(){

}

double** x = new double*[16];
double** y = new double*[16];

void readFile(){
    QString data;
    QFile file(":/data.csv");
    QStringList rowOfData;
    QStringList rowData;
    data.clear();
    rowOfData.clear();
    rowData.clear();
    if (file.open(QFile::ReadOnly)) {
        data = file.readAll();
        data = data.left(data.size() - 1);
        rowOfData = data.split("\n");
        file.close();
        for (int i = 0; i < rowOfData.size(); i++) {
            rowOfData[i] = rowOfData[i].left(rowOfData[i].size() - 1);
            rowData = rowOfData.at(i).split(",");
            x[i] = new double[4]{rowData[0].toDouble(), rowData[1].toDouble(), rowData[2].toDouble(), rowData[3].toDouble()};
            y[i] = new double[1]{rowData[4].toDouble()};
        }
    }
}

double* regression::getTetta(){
    readFile();
    Matrix X(x, 16, 4);
    Matrix Y(y, 16, 1);
    Matrix tetta = (X.transpose() * X).inversion() * X.transpose() * Y;
    double* res = new double[4];
    for (int i = 0; i < 4; i++){
        qInfo("%s", ("Коефіцієнт " + std::to_string(i) + " = " + std::to_string(tetta.data[i][0])).c_str());
        res[i] = tetta.data[i][0];
    }
    double* y1 = new double[16];
    double averageY = 0;
    double sum1 = 0, sum0 = 0;
    for (int i = 0; i < 16; i++) {
        averageY += y[i][0] / 16;
        y1[i] = res[0] + res[1]*x[i][1] + res[2]*x[i][2] + res[3]*x[i][3];
    }
    for (int i = 0; i < 16; i++){
        sum0 += (y[i][0] - y1[i])*(y[i][0] - y1[i]);
        sum1 += (y[i][0] - averageY)*(y[i][0] - averageY);
    }
    double factor = 1 - sum0/sum1;
    qInfo("%s", ("Коефіцієнт детермінації: " + std::to_string(factor)).c_str());
    return res;
}

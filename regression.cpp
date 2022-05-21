#include "matrix.h"
#include "qdebug.h"
#include "regression.h"

#include <QDir>
#include <QFile>
#include <QtGlobal>

regression::regression(){

}

double* regression::getTetta(){
    double** x = new double*[16];
    double** y = new double*[16];
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
    Matrix X(x, 16, 4);
    Matrix Y(y, 16, 1);
    Matrix tetta = (X.transpose() * X).inversion() * X.transpose() * Y;
    double* res = new double[4];
    for (int i = 0; i < 4; i++){
        //qInfo("%s", std::to_string(tetta.data[i][0]).c_str());
        res[i] = tetta.data[i][0];
    }
    return res;
}

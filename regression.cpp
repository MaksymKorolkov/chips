#include "matrix.h"
#include "regression.h"

#include <string>

regression::regression(){

}
double** x = new double*[16];
double** y = new double*[16];
static void setXY(){
    x[0] = new double[4]{1, 4, 2, 100};
    x[1] = new double[4]{1, 4.8,2.5,98.4};
    x[2] = new double[4]{1, 3.8,1.6,101.2};
    x[3] = new double[4]{1, 8.7,0.7,103.5};
    x[4] = new double[4]{1, 8.2,0.5,104.1};
    x[5] = new double[4]{1, 9.7,2,107};
    x[6] = new double[4]{1, 14.7,2.1,107.4};
    x[7] = new double[4]{1, 18.7,2.8,108.5};
    x[8] = new double[4]{1, 19.8,2.4,108.3};
    x[9] = new double[4]{1, 10.6,-0.1,109.2};
    x[10] = new double[4]{1, 8.6,0.7,110.1};
    x[11] = new double[4]{1, 6.5,2.2,110.7};
    x[12] = new double[4]{1, 12.6,1,110.3};
    x[13] = new double[4]{1, 6.5,0.5,111.8};
    x[14] = new double[4]{1, 5.8,1.7,112.3};
    x[15] = new double[4]{1, 5.7,1.1,112.9};
    y[0] = new double[1]{126};
    y[1] = new double[1]{137};
    y[2] = new double[1]{148};
    y[3] = new double[1]{191};
    y[4] = new double[1]{274};
    y[5] = new double[1]{370};
    y[6] = new double[1]{432};
    y[7] = new double[1]{445};
    y[8] = new double[1]{367};
    y[9] = new double[1]{367};
    y[10] = new double[1]{321};
    y[11] = new double[1]{307};
    y[12] = new double[1]{331};
    y[13] = new double[1]{345};
    y[14] = new double[1]{364};
    y[15] = new double[1]{384};
}

double* regression::getTetta(){
    setXY();
    Matrix X(x, 16, 4);
    Matrix Y(y, 16, 1);
    Matrix tetta = (X.transpose() * X).inversion() * X.transpose() * Y;
    double* res = new double[4];
    for (int i = 0; i < 4; i++) res[i] = tetta.data[i][0];
    return res;
}

double regression::getException(){
    setXY();
    Matrix X(x, 16, 4);
    Matrix Y(y, 16, 1);
    Matrix tetta =  (X.transpose() * X).inversion() * X.transpose() * Y;
    Matrix E = Y - X * tetta;
    double sum = 0;
    for (int i = 0; i < 16; i++) sum += E.data[i][0];
    return sum/16;
}

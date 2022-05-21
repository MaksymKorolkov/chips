#include "matrix.h"

Matrix::Matrix(int rows, int cols) : rowSize(rows), columnSize(cols) {
    allocateSpace();
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            data[i][j] = 0;
        }
    }
}

Matrix::Matrix(double** a, int rows, int cols) : rowSize(rows), columnSize(cols) {
    allocateSpace();
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            data[i][j] = a[i][j];
        }
    }
}

Matrix::Matrix(const Matrix& m) : rowSize(m.rowSize), columnSize(m.columnSize) {
    allocateSpace();
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            data[i][j] = m.data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m) {
        return *this;
    }
    if (rowSize != m.rowSize || columnSize != m.columnSize) {
        for (int i = 0; i < rowSize; i++) {
            delete[] data[i];
        }
        delete[] data;
        rowSize = m.rowSize;
        columnSize = m.columnSize;
        allocateSpace();
    }
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            data[i][j] = m.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            data[i][j] -= m.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    Matrix temp(rowSize, m.columnSize);
    for (int i = 0; i < temp.rowSize; i++) {
        for (int j = 0; j < temp.columnSize; j++) {
            for (int k = 0; k < columnSize; k++) {
                temp.data[i][j] += (data[i][k] * m.data[k][j]);
            }
        }
    }
    return (*this = temp);
}

Matrix Matrix::transpose() {
    Matrix res(columnSize, rowSize);
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            res.data[j][i] = data[i][j];
        }
    }
    return res;
}

Matrix Matrix::inversion() {
    double temp;
    double **A = data;
    double **E = createIdentity(columnSize).data;
    for (int k = 0; k < columnSize; k++) {
        temp = A[k][k];
        for (int j = 0; j < columnSize; j++){
            A[k][j] /= temp;
            E[k][j] /= temp;
        }
        for (int i = k + 1; i < columnSize; i++){
            temp = A[i][k];
            for (int j = 0; j < columnSize; j++) {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }
    for (int k = columnSize - 1; k > 0; k--) {
        for (int i = k - 1; i >= 0; i--) {
            temp = A[i][k];
            for (int j = 0; j < columnSize; j++) {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }
    return Matrix(E, columnSize, columnSize);
}

Matrix Matrix::createIdentity(int size) {
    Matrix temp(size, size);
    for (int i = 0; i < temp.rowSize; i++) {
        for (int j = 0; j < temp.columnSize; j++) {
            if (i == j) {
                temp.data[i][j] = 1;
            } else {
                temp.data[i][j] = 0;
            }
        }
    }
    return temp;
}

void Matrix::allocateSpace() {
    data = new double*[rowSize];
    for (int i = 0; i < rowSize; i++) {
        data[i] = new double[columnSize];
    }
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    Matrix temp(m1);
    return (temp -= m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    Matrix temp(m1);
    return (temp *= m2);
}

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
    Matrix(double**, int, int);
    Matrix(int, int);
    Matrix(const Matrix&);
    Matrix transpose();
    Matrix inversion();
    Matrix& operator=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const Matrix&);
    static Matrix createIdentity(int);
    int rowSize;
    int columnSize;
    double **data;
private:
    void allocateSpace();
};
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
#endif // MATRIX_H

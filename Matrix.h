//
// Created by Luca Sbragi on 05/04/2020.
//

#ifndef UNTITLED4_MATRIX_H
#define UNTITLED4_MATRIX_H

#include <cmath>

template <typename T>
class Matrix{
private:
    int rows, columns;
    T*A;

public:
    Matrix(int r, int c);
    ~Matrix();
    std::string toString();
    void setValue(int x, int y, T value);
    T getValue(int x, int y);
    Matrix<T> getCol(int y);
    Matrix<T> getRow(int x);
    void setCol(int y, Matrix<T> &cols);
    void setCol(int y, T* value);
    void setRow(int x, Matrix<T> &rows);
    void setRow(int x, T* value);
    bool isSquared();
    Matrix<T> transposed();
    T det(int car);
    void stampa();
    Matrix<T> inverse();

    bool operator==(const Matrix<T> &m);
    Matrix<T> &operator=(const Matrix<T> &m);
    Matrix<T> operator+(const Matrix<T>& m);
    Matrix<T> &operator+(const T num);
    Matrix<T> operator*(const Matrix<T>& m);
    Matrix<T> &operator*(const T num);
};

template<typename T>
Matrix<T>::Matrix(int r, int c) {
    rows = r;
    columns = c;
    A = new T[rows*columns];
    for(int i = 0; i < rows*columns; i++){
        A[i] = 0;
    }
}

template<typename T>
Matrix<T>::~Matrix() {
    if(A != 0){
        delete[] A;
    }
}

template<typename T>
std::string Matrix<T>::toString() {
    std::string ret;
    for(int i = 0; i < rows; i++){
        ret += " ";
        for(int j = 0; j < columns; j++){
            ret += std::to_string(A[i + j*rows]);
        }
    }
    return ret;
}

template<typename T>
bool Matrix<T>::isSquared() {
    if(rows == columns) {
        std::cout << "La matrice A e' quadrata" << std::endl;
        return true;
    }else {
        std::cout << "La matrice A non e' quadrata\n" << std::endl;
        return false;
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &m) {
    if(this != &m){
        if(rows == m.rows && columns == m.columns){
            for(int i = 0; i < rows*columns; i++){
                A[i] = m.A[i];
            }
        } else{
            throw std::domain_error("Rows and Columns doesn't match");
        }
    }
    return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> &m) {
  if(rows == m.rows && columns == m.columns){
      for(int i = 0; i < rows * columns; i++){
          if(A[i] != m.A[i]){
              return false;
          }
      }
      return true;
  }
    return false;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m) {
    if(rows == m.rows && columns == m.columns){
        Matrix<T> sum(rows, columns);
        for(int i = 0; i < rows*columns; i++){
            sum.A[i] = A[i] + m.A[i];
        }
        return sum;
    } else{
        throw std::domain_error("Rows and Columns doesn't match");
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator+(const T num) {
    for(int i = 0; i < rows*columns; i++){
        A[i] += num;
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &m) {
    if(columns == m.rows){
        Matrix<T> prodMatrix(rows, columns);
        T tmp = 0;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < m.columns; j++){
                for(int k = 0; k < columns; k++){
                    tmp += A[i + k*rows] * m.A[k + j*rows];
                }
                prodMatrix.A[i + j*rows] = tmp;
                tmp = 0;
            }
        }
        return prodMatrix;
    } else{
        throw std::domain_error("Rows and columns doesn't match");
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator*(const T num) {
    for(int i = 0; i < rows*columns; i++){
        A[i] *= num;
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::transposed() {
    Matrix<T> transMatrix(rows, columns);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            transMatrix.setValue(j, i, getValue(i, j));
        }
    }
    return transMatrix;
}


template<typename T>
T Matrix<T>::det(int car) {
    Matrix<T> sub_m(rows, columns);
    T determinant = 0;
    if(isSquared() == false)
        std::cout<<"Determinante impossibile da creare!"<<std::endl;
    if(car == 1) {
        determinant = A[0];
        std::cout << "Il determinante e': " << determinant;
    }else if(car == 2){
        determinant = A[0]*A[3] - A[1]*A[2];
        std::cout << "Il determinante e': " << determinant;
    } else{
        for(int row = 0; row < rows; row++){
            for(int i = 0; i < rows-1; i++){
                for(int j = 0; j < columns-1; j++){
                    int sub_row = (i < row ? i : i+1);
                    int sub_col = j + 1;
                    sub_m.A[i + j*(car-1)] = A[sub_row + sub_col*rows];
                }
            }
            if(row % 2 == 0){
                determinant += A[row + 0*rows] * sub_m.det(car-1);
            }else{
                determinant -= A[row + 0*rows] * sub_m.det(car-1);
            }
        }
        std::cout << "\n----------Il determinante finale e': ----------\n";
        std::cout << determinant;
    }
    return determinant;
}

template<typename T>
void Matrix<T>::stampa() {
    std::cout << "\n----------Stampa matrice: ----------\n\n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            std::cout << A[i + j*rows] <<"\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n----------Fine stampa----------\n";
}

template<typename T>
Matrix<T> Matrix<T>::inverse() {
    Matrix<T> gaussMatrix(rows, 2*columns);
    Matrix<T> inversematrix(rows, columns);
    if(!this->isSquared() || this->det(rows) == 0) {
        std::cout << "\nInversa impossibile da creare!\n";
    } else{
        std::cout << "\n----------APPLICO IL METODO DI GAUSS----------\n\n";

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                gaussMatrix.A[i + j*rows] = A[i + j*rows];
            }
        }

        for(int i = 0; i < rows; i++){
            for(int k = rows; k < 2*columns; k++){
                if(i == k - rows){
                    gaussMatrix.A[i + k*rows] = 1;
                } else{
                    gaussMatrix.A[i +k*rows] = 0;
                }
            }
        }

        T *tmp = new T[2*rows];

        for(int j = 0; j < rows-1; j++){
            for(int i = j+1; i < rows; i++) {
                if(gaussMatrix.A[j + j*rows] == 0){
                    T *tmp2 = new T[2*rows];
                    T *tmp3 = new T[2*rows];
                    if(gaussMatrix.A[i + j*rows] != 0){
                        for(int k = 0; k < 2*rows; k++){
                            tmp2[k] = gaussMatrix.A[j + k*rows];
                            tmp3[k] = gaussMatrix.A[i + k*rows];
                        }
                        for(int k = 0; k < 2*rows; k++){
                            gaussMatrix.A[i + k*rows] = tmp2[k];
                            gaussMatrix.A[j + k*rows] = tmp3[k];
                        }
                    }
                }
                if (gaussMatrix.A[i + j*rows] != 0) {
                    T mol = gaussMatrix.A[i + j*rows] / gaussMatrix.A[j + j*rows];
                    for (int k = 0; k < 2 * rows; k++) {
                        tmp[k] = mol * gaussMatrix.A[j + k*rows];
                    }
                    for (int k = 0; k < 2 * rows; k++){
                        gaussMatrix.A[i + k*rows] -= tmp[k];
                    }
                }if(gaussMatrix.A[i + i*rows] == 0){
                    T *tmp2;
                    T *tmp3;
                    tmp2 = new T[2*rows];
                    tmp3 = new T[2*rows];
                }
            }
        }
        std::cout << "Faccio l'eliminazione di Gauss sotto la diagonale:\n";
        for(int i = 0; i < rows; i++){
            for(int k = 0; k < 2*rows; k++){
                std::cout << gaussMatrix.A[i + k*rows] << "\t";
            }
            std::cout << "\n";
        }
        for(int j = rows-1; j > 0; j--) {
            for (int i = j-1; i >= 0; i--){
                if (gaussMatrix.A[i + j*rows] != 0) {
                    T mol = gaussMatrix.A[i + j*rows] / gaussMatrix.A[j + j*rows];
                    for (int k = 0; k < 2 * rows; k++){
                        tmp[k] = mol * gaussMatrix.A[j + k*rows];
                    }
                    for (int k = 0; k < 2 * rows; k++){
                        gaussMatrix.A[i + k*rows] -= tmp[k];
                    }
                }
            }
        }

        std::cout << "Faccio l'eliminazione di Gauss sopra la diagonale:\n";
        for(int i = 0; i < rows; i++){
            for(int k = 0; k < 2*rows; k++){
                std::cout << gaussMatrix.A[i + k*rows] << "\t";
            }
            std::cout << "\n";
        }

        for(int i = 0; i < rows; i++) {
            if (gaussMatrix.A[i + i*rows] != 1) {
                T mol = gaussMatrix.A[i + i*rows];
                for (int k = 0; k < 2 * rows; k++) {
                    gaussMatrix.A[i + k*rows] = gaussMatrix.A[i + k*rows] / mol;
                }
            }
        }

        std::cout << "Divido per i pivots\n";
        for(int i = 0; i < rows; i++){
            for(int k = 0; k < 2*rows; k++){
                std::cout << gaussMatrix.A[i + k*rows] << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n----------FINE METODO DI GAUSS-----------\n";

        int k = 0;
        for(int i = 0; i < rows; i++) {
            for(int j = rows; j < 2*rows; j++,k++){
                inversematrix.A[i + k*rows]=gaussMatrix.A[i + j*rows];
            }
            k = 0;
        }
        inversematrix.stampa();
    }
    return inversematrix;
}

template<typename T>
T Matrix<T>::getValue(int x, int y) {
    if(x >= 0 && x < rows && y >= 0 && y < rows){
        return A[x + y*rows];
    } else{
        throw std::out_of_range("Out of range");
    }
}

template<typename T>
void Matrix<T>::setValue(int x, int y, T value) {
    if(x >= 0 && x < rows && y >= 0 && y < columns){
        A[x + y*rows] = value;
    } else{
        throw std::out_of_range("Out of range");
    }
}

template<typename T>
Matrix<T> Matrix<T>::getCol(int y) {
    Matrix<T> col(rows, 1);
    for(int i = 0; i < rows; i++){
        col.setValue(i, 0, getValue(i, y));
    }
    return col;
}

template<typename T>
Matrix<T> Matrix<T>::getRow(int x) {
    Matrix<T> row(1, columns);
    for(int j = 0; j < columns; j++){
        row. setValue(0, j, getValue(x, j));
    }
    return row;
}

template<typename T>
void Matrix<T>::setCol(int y, Matrix<T> &colMatrix) {
    if(colMatrix.columns == 1 && y >= 0 && y < columns){
        if(rows == colMatrix.rows){
            for(int i = 0; i < rows; i++){
                setValue(i, y, colMatrix.getValue(i, 0));
            }
        } else{
            throw std::domain_error("Matrix hasn't got the same rows");
        }
    } else{
        throw std::domain_error("Column index is invalid");
    }
}

template<typename T>
void Matrix<T>::setRow(int x, Matrix<T> &rowMatrix) {
    if(rowMatrix.rows == 1 && x >= 0 && x < rows){
        if(columns == rowMatrix.columns){
            for(int j = 0; j < columns; j++){
                setValue(x, j, rowMatrix.getValue(0, j));
            }
        } else{
            throw std::domain_error("Matrix hasn't got the same columns");
        }
    } else {
        throw std::domain_error("Row index is invalid");
    }
}

template<typename T>
void Matrix<T>::setCol(int y, T * value) {
    for(int i = 0; i < rows; i++){
        setValue(i, y, value[i]);
    }
}

template<typename T>
void Matrix<T>::setRow(int x, T* value) {
    for(int j = 0; j < columns; j++){
        setValue(x, j, value[j]);
    }
}




#endif //UNTITLED4_MATRIX_H

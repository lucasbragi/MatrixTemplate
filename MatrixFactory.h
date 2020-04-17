//
// Created by Luca Sbragi on 11/04/2020.
//

#ifndef UNTITLED4_MATRIXFACTORY_H
#define UNTITLED4_MATRIXFACTORY_H

#include <iostream>
#include "Matrix.h"

template <typename T>
class MatrixFactory{
public:
    Matrix<T> createMatrix(std::string type, int r, int c){
        if(type == ""){
            std::cout << "Matrice creata" << std::endl;
            Matrix<T> m(r, c);
            return m;
        }
    }
};

#endif //UNTITLED4_MATRIXFACTORY_H

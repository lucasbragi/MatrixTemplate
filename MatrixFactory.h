//
// Created by Luca Sbragi on 11/04/2020.
//

#ifndef UNTITLED4_MATRIXFACTORY_H
#define UNTITLED4_MATRIXFACTORY_H

#include <iostream>
#include "Matrix.h"

template <typename T, int R, int C>
class MatrixFactory{
public:
    Matrix<T, R, C> createMatrix(std::string type){
        if(type == ""){
            std::cout << "Matrice creata" << std::endl;
            Matrix<T, R, C> m;
            return m;
        }
    }
};

#endif //UNTITLED4_MATRIXFACTORY_H

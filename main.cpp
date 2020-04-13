#include <iostream>
#include "Matrix.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
/*
    //Prova con matrice 2x2 di double
    Matrix<double, 2, 2> m;
    m.isSquared();
    m.insertValue();
    m.showRow();
    m.showColumn();
    m.getValue(1, 1);
    m.transposed();
    m.creationIdentity();
    m.createB();
    m.inverse();

    //Prova con matrice di interi
    Matrix<int, 2, 2> m2;
    m2.isSquared();
    m2.insertValue();
    m2.getValue(1, 1);
    m2.transposed();
    m2.creationIdentity();
    m2.createB();
    m2.inverse();

    //Prova con matrice 3x3
    Matrix<double, 3, 3> m3;
    m3.isSquared();
    m3.insertValue();
    m3.getValue(2, 1);
    m3.transposed();
    m3.createB();
    m3.creationIdentity();
    m3.inverse();

    //Prova con matrice non quadrata
    Matrix<double, 1, 2> m1;
    m1.isSquared();
    m1.insertValue();
    m1.creationIdentity();
    m1.createB();
    m1.inverse();
*/
    return 0;
}


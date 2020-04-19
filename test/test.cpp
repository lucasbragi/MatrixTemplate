//
// Created by Luca Sbragi on 11/04/2020.
//

#include <gtest/gtest.h>
#include "../Matrix.h"

class TestMatrix : public testing::Test {
protected:
    TestMatrix() : matrix(3, 3) {}

    void setMatrix() {
        matrix.setRow(0, new int[3]{1, 3, 1});
        matrix.setRow(1, new int[3]{2, 8, 0});
        matrix.setRow(2, new int[3]{1, 6, 3});
    }
    Matrix<int> matrix;
};

TEST_F(TestMatrix, toString){
    setMatrix();
    ASSERT_EQ(" 131 280 163", matrix.toString());
}

TEST_F(TestMatrix, getCol){
    setMatrix();
    Matrix<int> col(3, 1);
    col = matrix.getCol(0);
    ASSERT_EQ(1, matrix.getValue(0, 0));
    ASSERT_EQ(2, matrix.getValue(1, 0));
    ASSERT_EQ(1, matrix.getValue(2, 0));
}

TEST_F(TestMatrix, getRow){
    setMatrix();
    Matrix<int> row(1, 3);
    row = matrix.getRow(0);
    ASSERT_EQ(1, matrix.getValue(0, 0));
    ASSERT_EQ(3, matrix.getValue(0, 1));
    ASSERT_EQ(1, matrix.getValue(0, 2));
}

TEST_F(TestMatrix, setCol){
    Matrix<int> col(3, 1);
    col.setValue(0, 0, 6);
    col.setValue(1, 0, 3);
    col.setValue(2, 0, 8);
    matrix.setCol(0, col);
    ASSERT_EQ(6, matrix.getValue(0, 0));
    ASSERT_EQ(3, matrix.getValue(1, 0));
    ASSERT_EQ(8, matrix.getValue(2, 0));
}

TEST_F(TestMatrix, setRow){
    Matrix<int> row(3, 1);
    row.setValue(0, 0, 9);
    row.setValue(0, 1, 5);
    row.setValue(0, 2, 4);
    matrix.setRow(0, row);
    ASSERT_EQ(9, matrix.getValue(0, 0));
    ASSERT_EQ(5, matrix.getValue(0, 1));
    ASSERT_EQ(4, matrix.getValue(0, 2));
}

TEST_F(TestMatrix, getTransposed){
    setMatrix();
    Matrix<int> transposedMatrix(3, 3);
    transposedMatrix.setRow(0, new int[3]{1, 2, 1});
    transposedMatrix.setRow(1, new int[3]{3, 8, 6});
    transposedMatrix.setRow(2, new int[3]{1, 0, 3});
    bool condition = false;
    if(matrix.transposed() == transposedMatrix){
        condition = true;
    }
    ASSERT_TRUE(condition);
}

TEST_F(TestMatrix, sumMatrix){
    setMatrix();
    Matrix<int> m1(3, 3);
    Matrix<int> m2(3, 3);
    Matrix<int> sum(3, 3);
    m1.setRow(0, new int[3]{1, 4, 3});
    m1.setRow(1, new int[3]{3, 5, 9});
    m1.setRow(2, new int[3]{6, 8, 4});
    m2.setRow(0, new int[3]{2, 7, 4});
    m2.setRow(1, new int[3]{5, 13, 9});
    m2.setRow(2, new int[3]{7, 14, 7});
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            sum.setValue(i, j, matrix.getValue(i, j) + m1.getValue(i, j));
        }
    }
    bool condition = false;
    if(sum == m2){
        condition = true;
    }
    ASSERT_TRUE(condition);
}

TEST_F(TestMatrix, sum_scalar){
    setMatrix();
    Matrix<int> sum(3,3);
    Matrix<int> tryMatrix(3, 3);
    tryMatrix.setRow(0, new int[3]{4, 6, 4});
    tryMatrix.setRow(1, new int[3]{5, 11, 3});
    tryMatrix.setRow(2, new int[3]{4, 9, 6});
    sum = matrix + 3;
    bool condition = false;
    if(sum == tryMatrix){
        condition = true;
    }
    ASSERT_TRUE(condition);
}

TEST_F(TestMatrix, productMatrix){
    setMatrix();
    Matrix<int> m1(3, 3);
    Matrix<int> m2(3, 3);
    Matrix<int> product(3, 3);
    int prod = 0;
    m1.setRow(0, new int[3]{1, 4, 3});
    m1.setRow(1, new int[3]{3, 5, 9});
    m1.setRow(2, new int[3]{6, 8, 4});
    m2.setRow(0, new int[3]{16, 27, 34});
    m2.setRow(1, new int[3]{26, 48, 78});
    m2.setRow(2, new int[3]{37, 58, 69});
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                prod = prod + matrix.getValue(i, k)*m1.getValue(k, j);
            }
            product.setValue(i, j, prod);
            prod = 0;
        }
    }
    bool condition = false;
    if(product == m2){
        condition = true;
    }
    ASSERT_TRUE(condition);
}

TEST_F(TestMatrix, product_scalar){
    setMatrix();
    Matrix<int> prod(3, 3);
    Matrix<int> tryMatrix(3, 3);
    tryMatrix.setRow(0, new int[3]{3, 9, 3});
    tryMatrix.setRow(1, new int[3]{6, 24, 0});
    tryMatrix.setRow(2, new int[3]{3, 18, 9});
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            prod.setValue(i, j, matrix.getValue(i, j)*3);
        }
    }
    bool condition = false;
    if(prod == tryMatrix){
        condition = true;
    }
    ASSERT_TRUE(condition);
}

TEST_F(TestMatrix, inverseMatrix){
    setMatrix();
    Matrix<int> tryMatrix(3, 3);
    tryMatrix.setRow(0, new int[3]{1, 0, 0});
    tryMatrix.setRow(1, new int[3]{0, 1, 0});
    tryMatrix.setRow(2, new int[3]{0, 0, 1});
    bool condition = false;
    if(tryMatrix == matrix * (matrix.inverse())){
        condition = true;
    }
    ASSERT_TRUE(condition);
}

TEST_F(TestMatrix, determinant){
    setMatrix();
    ASSERT_EQ(10, matrix.det(3));
}

TEST_F(TestMatrix, copyOperator){
    setMatrix();
    Matrix<int> m(3, 3);
    m.setRow(0, new int[3]{1, 3, 2});
    m.setRow(1, new int[3]{4, 8, 0});
    m.setRow(2, new int[3]{1, 9, 2});

    matrix = m;

    bool condition = false;
    if(matrix == m){
        condition = true;
    }
    ASSERT_TRUE(condition);
}

TEST_F(TestMatrix, setCol_Matrix_Exception){
    setMatrix();
    Matrix<int> tryMatrix(3,2);
    ASSERT_THROW(matrix.setCol(1, tryMatrix), std::domain_error);
}

TEST_F(TestMatrix, setRow_Matrix_Exception){
    setMatrix();
    Matrix<int> tryMatrix(2, 3);
    ASSERT_THROW(matrix.setRow(1, tryMatrix), std::domain_error);
}

TEST_F(TestMatrix, sum_Matrix_Exception){
    setMatrix();
    Matrix<int> tryMatrix(3, 2);
    ASSERT_THROW(matrix + tryMatrix, std::domain_error);
}

TEST_F(TestMatrix, product_Matrix_Exception){
    setMatrix();
    Matrix<int> tryMatrix(1,3);
    ASSERT_THROW(matrix * tryMatrix, std::domain_error);
}

TEST_F(TestMatrix, inverse_Matrix_Exception){
    setMatrix();
    Matrix<int> tryMatrix(3, 1);
    ASSERT_THROW(tryMatrix = matrix.inverse(), std::domain_error);
}

TEST_F(TestMatrix, copyOperator_Exception){
    setMatrix();
    Matrix<int> tryMatrix(3, 1);
    ASSERT_THROW(matrix = tryMatrix, std::domain_error);
}
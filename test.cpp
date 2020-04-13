//
// Created by Luca Sbragi on 11/04/2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../Matrix.h"



namespace {
    class TestMatrix : public testing::Test{
    public:
        Matrix<double, 3, 3> matrix;
    };
}
TEST_F(TestMatrix, controllMatriceQuadrata){
    ASSERT_EQ(true, matrix.isSquared());
}

TEST_F(TestMatrix, getTransposed) {
    Matrix<double, 3, 3> transposed;
    matrix.insertValue();
    bool condition = false;
    if (matrix.transposed() == transposed.insertValue())
        condition = true;
    ASSERT_TRUE(condition);
}

TEST_F(TestMatrix, getVal){
    Matrix<double, 3, 3> val;
    val.insertValue();
    ASSERT_EQ(1, val.getValue(0, 0));
    ASSERT_EQ(2, val.getValue(1, 0));
    ASSERT_EQ(3, val.getValue(1, 1));
}

TEST_F(TestMatrix, getCol){
    Matrix<double, 3, 3> col;
    ASSERT_EQ(3, col.getCol() );
    ASSERT_EQ(2, col.getCol() );
}

TEST_F(TestMatrix, getRow){
    Matrix<double, 3, 3> row;
    ASSERT_EQ(3, row.getRow() );
    ASSERT_EQ(2, row.getRow() );
}

//
// Created by Hadi Sinaee on 2019-01-19.
//

//
// Created by Hadi Sinaee on 2019-01-19.
//

#include <gtest/gtest.h>
#include "../src/storage/mtx_matrix.cpp"

class MtxMatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        this->pathDouble = "data/L_dense_double_01.mtx";
        this->pathInt = "data/L_dense_int_01.mtx";

        this->TRUE_DOUBLE_N = 4;
        this->TRUE_DOUBLE_M = 4;
        this->TRUE_DOUBLE_NZ = 16;

        this->TRUE_INT_N = 3;
        this->TRUE_INT_M = 3;
        this->TRUE_INT_NZ = 9;

        this->TRUE_DOUBLE_LI = new int[16]{
                1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4
        };
        this->TRUE_DOUBLE_LP = new int[5]{0, 4, 8, 12, 16};
        this->TRUE_DOUBLE_LX = new double[16]{
                .1, .2, .3, .4,
                .5, .6, .7, .8,
                .9, 1, 1.1, 1.2,
                1.3, 1.4, 1.5, 1.6
        };

        this->TRUE_INT_LI = new int[9]{
                1, 2, 3,
                1, 2, 3,
                1, 2, 3
        };
        this->TRUE_INT_LP = new int[4]{0, 3, 6, 9};
        this->TRUE_INT_LX = new int[9]{
                1, 2, 3,
                5, 6, 7,
                9, 10, 11
        };
    }


    MtxMatrix<double> mDouble;
    MtxMatrix<int> mInt;

    std::string pathDouble, pathInt;
    int TRUE_DOUBLE_N, TRUE_DOUBLE_M, TRUE_DOUBLE_NZ;
    int TRUE_INT_N, TRUE_INT_M, TRUE_INT_NZ;
    int *TRUE_DOUBLE_LI, *TRUE_INT_LI;
    int *TRUE_DOUBLE_LP, *TRUE_INT_LP;
    double *TRUE_DOUBLE_LX;
    int *TRUE_INT_LX;
};

TEST_F(MtxMatrixTest, fail_double_read_dense_invalid_string) {
    // reading data
    EXPECT_EQ(1, mDouble.readDataFrom("")) << "invalid file path strings return 1 as a read result.\n";
}

TEST_F(MtxMatrixTest, fail_double_read_dense_cannot_open_file) {
    // reading data
    EXPECT_EQ(2, mDouble.readDataFrom("./somewhere")) << "do not exist files return 2 as a read result.\n";
}


TEST_F(MtxMatrixTest, double_read_dense) {
    // reading data
    EXPECT_EQ(0, mDouble.readDataFrom(pathDouble)) << "has to return 0 for success reading of data";

    // check reading correctness
    ASSERT_FALSE(mDouble.isEmpty()) << "it has to contain some data.\n";

    // check validity of the read data
    auto dim = mDouble.getDimension();

    EXPECT_EQ(dim->getRows(), TRUE_DOUBLE_N) << "number of read rows are different from the baseline\n";
    EXPECT_EQ(dim->getColumns(), TRUE_DOUBLE_M) << "number of read columns are different from the baseline\n";
    EXPECT_EQ(dim->getNonZeros(), TRUE_DOUBLE_NZ) << "number of none zeros are different from the baseline\n";
}

TEST_F(MtxMatrixTest, double_check_mtx_data) {
    EXPECT_EQ(0, mDouble.readDataFrom(pathDouble)) << "has to return 0 for success reading of data";

    // check index values
    auto li = mDouble.getLi();
    for (int i = 0; i < TRUE_DOUBLE_N; i++) {
        EXPECT_EQ(li[i], TRUE_DOUBLE_LI[i]) << "the computed row index is different from the baseline\n";
    }

    // check column values
    auto lp = mDouble.getLp();
    for (int i = 0; i < TRUE_DOUBLE_M + 1; ++i) {
        EXPECT_EQ(lp[i], TRUE_DOUBLE_LP[i]) << "the computed column pointer is different from the baseline\n";
    }
    EXPECT_EQ(TRUE_DOUBLE_LP[TRUE_DOUBLE_M], TRUE_DOUBLE_NZ);

    // check values against [] operator
    for (int i = 0; i < TRUE_DOUBLE_NZ; ++i) {
        EXPECT_EQ(mDouble[i], TRUE_DOUBLE_LX[i]) << "the computed column value is different from the baseline\n";
    }

    // check values of getData function against [] operator
    for (int i = 0; i < TRUE_DOUBLE_NZ; ++i) {
        EXPECT_EQ(mDouble[i], mDouble.getDataAt(i)) << "v[] operator is different from v.getDataAt function\n";
    }
}

TEST_F(MtxMatrixTest, double_none_zeros_index_one_column) {
    EXPECT_EQ(0, mDouble.readDataFrom(pathDouble)) << "has to return 0 for success reading of data";

    // reading the whole column
    auto columnIndices = mDouble.getNoneZeroRowIndices(1);
    int idx = 1;
    for (auto it : *columnIndices) {
        EXPECT_EQ(it, idx++) << "the row index for column 1 is different from the baseline\n";
    }
}

TEST_F(MtxMatrixTest, double_set_value) {
    EXPECT_EQ(0, mDouble.readDataFrom(pathDouble)) << "has to return 0 for success reading of data";

    // setting a new value
    mDouble.setDataAt(0, .43);
    mDouble.setDataAt(1, .89);

    EXPECT_EQ(mDouble[0], .43) << "v[0] didn't change correctly.\n";
    EXPECT_EQ(mDouble[1], .89) << "v[1] didn't change correctly\n";

    EXPECT_EQ(mDouble.getDataAt(0), mDouble[0]) << "v.getDataAt and v[] are not the same after the change\n";
    EXPECT_EQ(mDouble.getDataAt(1), mDouble[1]) << "v.getDataAt and v[] are not the same after the change\n";

}


TEST_F(MtxMatrixTest, int_read_dense) {
    // reading data
    EXPECT_EQ(0, mInt.readDataFrom(pathInt)) << "has to return 0 for successful reading of data";

    // check reading correctness
    ASSERT_FALSE(mInt.isEmpty()) << "it has to contain some data.\n";

    // check validity of the read data
    auto dim = mInt.getDimension();

    EXPECT_EQ(dim->getRows(), TRUE_INT_N) << "number of read rows are different from the baseline\n";
    EXPECT_EQ(dim->getColumns(), TRUE_INT_M) << "number of read columns are different from the baseline\n";
    EXPECT_EQ(dim->getNonZeros(), TRUE_INT_NZ) << "number of none zeros are different from the baseline\n";
}

TEST_F(MtxMatrixTest, int_check_mtx_data) {
    EXPECT_EQ(0, mInt.readDataFrom(pathInt)) << "has to return 0 for successful reading of data";

    // check index values
    auto li = mInt.getLi();
    for (int i = 0; i < TRUE_INT_N; i++) {
        EXPECT_EQ(li[i], TRUE_INT_LI[i]) << "the computed row index is different from the baseline\n";
    }

    // check column values
    auto lp = mInt.getLp();
    for (int i = 0; i < TRUE_INT_M + 1; ++i) {
        EXPECT_EQ(lp[i], TRUE_INT_LP[i]) << "the computed column pointer is different from the baseline\n";
    }
    EXPECT_EQ(TRUE_INT_LP[TRUE_INT_M], TRUE_INT_NZ);

    // check values against [] operator
    for (int i = 0; i < TRUE_INT_NZ; ++i) {
        EXPECT_EQ(mInt[i], TRUE_INT_LX[i]) << "the computed column value is different from the baseline\n";
    }

    // check values of getData function against [] operator
    for (int i = 0; i < TRUE_INT_NZ; ++i) {
        EXPECT_EQ(mInt[i], mInt.getDataAt(i)) << "v[] operator is different from v.getDataAt function\n";
    }
}

TEST_F(MtxMatrixTest, int_none_zeros_index_one_column) {
    EXPECT_EQ(0, mInt.readDataFrom(pathInt)) << "has to return 0 for successful reading of data";

    // reading the whole column
    auto columnIndices = mInt.getNoneZeroRowIndices(1);
    int idx = 1;
    for (auto it : *columnIndices) {
        EXPECT_EQ(it, idx++) << "the row index for column 1 is different from the baseline\n";
    }
}

TEST_F(MtxMatrixTest, int_set_value) {
    EXPECT_EQ(0, mInt.readDataFrom(pathInt)) << "has to return 0 for successful reading of data";

    const int v1 = -100, v2 = -200;

    // setting a new value
    mInt.setDataAt(0, v1);
    mInt.setDataAt(1, v2);

    EXPECT_EQ(mInt[0], v1) << "v[0] didn't change correctly.\n";
    EXPECT_EQ(mInt[1], v2) << "v[1] didn't change correctly\n";

    EXPECT_EQ(mInt.getDataAt(0), mInt[0]) << "v.getDataAt and v[] are not the same after the change\n";
    EXPECT_EQ(mInt.getDataAt(1), mInt[1]) << "v.getDataAt and v[] are not the same after the change\n";

}
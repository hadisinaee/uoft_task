//
// Created by Hadi Sinaee on 2019-01-19.
//

#include <gtest/gtest.h>
#include "../src/storage/mtx_vector.cpp"

class MtxVectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        this->pathDouble = "data/b_dense_double_01.mtx";
        this->pathInt = "data/b_dense_int_01.mtx";
        this->pathSparseInt = "data/b_sparse_int_01.mtx";

        // double section
        this->TRUE_DOUBLE_N = 4;
        this->TRUE_DOUBLE_M = 1;
        this->TRUE_DOUBLE_NZ = 4;

        this->TRUE_DOUBLE_LI = new int[4]{1, 2, 3, 4};
        this->TRUE_DOUBLE_LP = new int[2]{0, 4};
        this->TRUE_DOUBLE_LX = new double[4]{.1, .2, .3, .4};

        // int section
        this->TRUE_INT_N = 4;
        this->TRUE_INT_M = 1;
        this->TRUE_INT_NZ = 4;

        this->TRUE_INT_LI = new int[4]{1, 2, 3, 4};
        this->TRUE_INT_LP = new int[2]{0, 4};
        this->TRUE_INT_LX = new int[4]{10, 20, 30, 40};

        // sparse int section
        this->TRUE_S_INT_N = 10;
        this->TRUE_S_INT_M = 1;
        this->TRUE_S_INT_NZ = 4;

        this->TRUE_S_INT_LI = new int[4]{1, 3, 5, 10};
        this->TRUE_S_INT_LP = new int[2]{0, 4};
        this->TRUE_S_INT_LX = new int[4]{-1, -2, -3, -4};
    }


    MtxVector<double> vDouble;
    MtxVector<int> vInt, vSparseInt;

    std::string pathDouble, pathInt, pathSparseInt;

    int TRUE_DOUBLE_N, TRUE_DOUBLE_M, TRUE_DOUBLE_NZ;
    int *TRUE_DOUBLE_LI, *TRUE_DOUBLE_LP;
    double *TRUE_DOUBLE_LX;

    int TRUE_INT_N, TRUE_INT_M, TRUE_INT_NZ;
    int *TRUE_INT_LI, *TRUE_INT_LP;
    int *TRUE_INT_LX;

    int TRUE_S_INT_N, TRUE_S_INT_M, TRUE_S_INT_NZ;
    int *TRUE_S_INT_LI, *TRUE_S_INT_LP;
    int *TRUE_S_INT_LX;
};

TEST_F(MtxVectorTest, fail_double_read_dense_invalid_string) {
    // reading data
    auto readResult = vDouble.readDataFrom("");

    // 1 for invalid file path
    EXPECT_EQ(readResult, 1) << "invalid file path strings return 1 as a read result.\n";
}

TEST_F(MtxVectorTest, fail_double_read_dense_cannot_open_file) {
    // reading data
    auto readResult = vDouble.readDataFrom("./somewhere");

    // 1 for invalid file path
    EXPECT_EQ(readResult, 2) << "do not exist files return 2 as a read result.\n";
}

TEST_F(MtxVectorTest, double_read_dense) {
    // reading data
    auto readResult = vDouble.readDataFrom(pathDouble);

    // 0 for successful read of data
    EXPECT_EQ(readResult, 0) << "successful read operations return 0.\n";
    // check reading correctness
    ASSERT_FALSE(vDouble.isEmpty()) << "it has to contain some data.\n";

    // check validity of the read data
    auto dim = vDouble.getDimension();

    EXPECT_EQ(dim->getRows(), TRUE_DOUBLE_N) << "number of read rows are different from the baseline\n";
    EXPECT_EQ(dim->getColumns(), TRUE_DOUBLE_M) << "number of read columns are different from the baseline\n";
    EXPECT_EQ(dim->getNonZeros(), TRUE_DOUBLE_NZ) << "number of none zeros are different from the baseline\n";
}

TEST_F(MtxVectorTest, double_check_mtx_data) {
    EXPECT_EQ(vDouble.readDataFrom(pathDouble), 0);

    // check index values
    auto li = vDouble.getLi();
    for (int i = 0; i < TRUE_DOUBLE_N; i++) {
        EXPECT_EQ(li[i], TRUE_DOUBLE_LI[i]) << "the computed row index is different from the baseline\n";
    }

    // check column values
    auto lp = vDouble.getLp();
    for (int i = 0; i < TRUE_DOUBLE_M + 1; ++i) {
        EXPECT_EQ(lp[i], TRUE_DOUBLE_LP[i]) << "the computed column pointer is different from the baseline\n";
    }
    EXPECT_EQ(TRUE_DOUBLE_LP[TRUE_DOUBLE_M], TRUE_DOUBLE_NZ);

    // check values against [] operator
    for (int i = 0; i < TRUE_DOUBLE_NZ; ++i) {
        EXPECT_EQ(vDouble[i], TRUE_DOUBLE_LX[i]) << "the computed column value is different from the baseline\n";
    }

    // check values of getData function against [] operator
    for (int i = 0; i < TRUE_DOUBLE_NZ; ++i) {
        EXPECT_EQ(vDouble[i], vDouble.getDataAt(i)) << "v[] operator is different from v.getDataAt function\n";
    }
}

TEST_F(MtxVectorTest, double_none_zeros_index_one_column) {
    EXPECT_EQ(vDouble.readDataFrom(pathDouble), 0);

    // reading the whole column
    auto columnIndices = vDouble.getNoneZeroRowIndices(1);
    int idx = 1;
    for (auto it : *columnIndices) {
        EXPECT_EQ(it, idx++) << "the row index for column 1 is different from the baseline\n";
    }
}

TEST_F(MtxVectorTest, double_set_value) {
    EXPECT_EQ(vDouble.readDataFrom(pathDouble), 0);

    // setting a new value
    vDouble.setDataAt(0, .43);
    vDouble.setDataAt(1, .89);

    EXPECT_EQ(vDouble[0], .43) << "v[0] didn't change correctly.\n";
    EXPECT_EQ(vDouble[1], .89) << "v[1] didn't change correctly\n";

    EXPECT_EQ(vDouble.getDataAt(0), vDouble[0]) << "v.getDataAt and v[] are not the same after the change\n";
    EXPECT_EQ(vDouble.getDataAt(1), vDouble[1]) << "v.getDataAt and v[] are not the same after the change\n";

}


TEST_F(MtxVectorTest, int_read_dense) {
    // reading data
    EXPECT_EQ(vInt.readDataFrom(pathInt), 0);

    // check reading correctness
    ASSERT_FALSE(vInt.isEmpty()) << "it has to contain some data.\n";

    // check validity of the read data
    auto dim = vInt.getDimension();

    EXPECT_EQ(dim->getRows(), TRUE_INT_N) << "number of read rows are different from the baseline\n";
    EXPECT_EQ(dim->getColumns(), TRUE_INT_M) << "number of read columns are different from the baseline\n";
    EXPECT_EQ(dim->getNonZeros(), TRUE_INT_NZ) << "number of none zeros are different from the baseline\n";
}

TEST_F(MtxVectorTest, int_check_mtx_data) {
    EXPECT_EQ(vInt.readDataFrom(pathInt), 0);

    // check index values
    auto li = vInt.getLi();
    for (int i = 0; i < TRUE_INT_N; i++) {
        EXPECT_EQ(li[i], TRUE_INT_LI[i]) << "the computed row index is different from the baseline\n";
    }

    // check column values
    auto lp = vInt.getLp();
    for (int i = 0; i < TRUE_INT_M + 1; ++i) {
        EXPECT_EQ(lp[i], TRUE_INT_LP[i]) << "the computed column pointer is different from the baseline\n";
    }
    EXPECT_EQ(TRUE_INT_LP[TRUE_INT_M], TRUE_INT_NZ);

    // check values against [] operator
    for (int i = 0; i < TRUE_INT_NZ; ++i) {
        EXPECT_EQ(vInt[i], TRUE_INT_LX[i]) << "the computed column value is different from the baseline\n";
    }

    // check values of getData function against [] operator
    for (int i = 0; i < TRUE_INT_NZ; ++i) {
        EXPECT_EQ(vInt[i], vInt.getDataAt(i)) << "v[] operator is different from v.getDataAt function\n";
    }
}

TEST_F(MtxVectorTest, int_none_zeros_index_one_column) {
    EXPECT_EQ(vInt.readDataFrom(pathInt), 0);

    // reading the whole column
    auto columnIndices = vInt.getNoneZeroRowIndices(1);
    int idx = 1;
    for (auto it : *columnIndices) {
        EXPECT_EQ(it, idx++) << "the row index for column 1 is different from the baseline\n";
    }
}

TEST_F(MtxVectorTest, int_set_value) {
    EXPECT_EQ(vInt.readDataFrom(pathInt), 0);

    const int v1 = -100, v2 = -200;

    // setting a new value
    vInt.setDataAt(0, v1);
    vInt.setDataAt(1, v2);

    EXPECT_EQ(vInt[0], v1) << "v[0] didn't change correctly.\n";
    EXPECT_EQ(vInt[1], v2) << "v[1] didn't change correctly\n";

    EXPECT_EQ(vInt.getDataAt(0), vInt[0]) << "v.getDataAt and v[] are not the same after the change\n";
    EXPECT_EQ(vInt.getDataAt(1), vInt[1]) << "v.getDataAt and v[] are not the same after the change\n";

}


TEST_F(MtxVectorTest, sparse_int_read) {
    EXPECT_EQ(vSparseInt.readDataFrom(pathSparseInt), 0);

    // check reading correctness
    ASSERT_FALSE(vSparseInt.isEmpty()) << "it has to contain some data.\n";

    // check validity of the read data
    auto dim = vSparseInt.getDimension();

    EXPECT_EQ(dim->getRows(), TRUE_S_INT_N) << "number of read rows are different from the baseline\n";
    EXPECT_EQ(dim->getColumns(), TRUE_S_INT_M) << "number of read columns are different from the baseline\n";
    EXPECT_EQ(dim->getNonZeros(), TRUE_S_INT_NZ) << "number of none zeros are different from the baseline\n";
}

TEST_F(MtxVectorTest, sparse_int_check_mtx_data) {
    EXPECT_EQ(vSparseInt.readDataFrom(pathSparseInt), 0);

    // check index values
    auto li = vSparseInt.getLi();
    for (int i = 0; i < TRUE_S_INT_NZ; i++) {
        EXPECT_EQ(li[i], TRUE_S_INT_LI[i]) << "the computed row index is different from the baseline\n";
    }

    // check column values
    auto lp = vSparseInt.getLp();
    for (int i = 0; i < TRUE_S_INT_M + 1; ++i) {
        EXPECT_EQ(lp[i], TRUE_S_INT_LP[i]) << "the computed column pointer is different from the baseline\n";
    }
    EXPECT_EQ(TRUE_S_INT_LP[TRUE_S_INT_M], TRUE_S_INT_NZ);

    // check values against [] operator
    for (int i = 0; i < TRUE_S_INT_NZ; ++i) {
        EXPECT_EQ(vSparseInt[i], TRUE_S_INT_LX[i]) << "the computed column value is different from the baseline\n";
    }

    // check values of getData function against [] operator
    for (int i = 0; i < TRUE_S_INT_NZ; ++i) {
        EXPECT_EQ(vSparseInt[i], vSparseInt.getDataAt(i)) << "v[] operator is different from v.getDataAt function\n";
    }
}

TEST_F(MtxVectorTest, sparse_int_none_zeros_index_one_column) {
    EXPECT_EQ(vSparseInt.readDataFrom(pathSparseInt), 0);

    // reading the whole column
    auto columnIndices = vSparseInt.getNoneZeroRowIndices(1);
    auto idx = 0;
    int cIndex[] = {1, 3, 5, 10};
    for (auto it : *columnIndices) {
        EXPECT_EQ(it, cIndex[idx++]) << "the row index for column 1 is different from the baseline\n";
    }
}

TEST_F(MtxVectorTest, sparse_set_value) {
    EXPECT_EQ(vSparseInt.readDataFrom(pathSparseInt), 0);

    const int v1 = -100, v2 = -200;

    // setting a new value
    vSparseInt.setDataAt(0, v1);
    vSparseInt.setDataAt(1, v2);

    EXPECT_EQ(vSparseInt[0], v1) << "v[0] didn't change correctly.\n";
    EXPECT_EQ(vSparseInt[1], v2) << "v[1] didn't change correctly\n";

    EXPECT_EQ(vSparseInt.getDataAt(0), vSparseInt[0]) << "v.getDataAt and v[] are not the same after the change\n";
    EXPECT_EQ(vSparseInt.getDataAt(1), vSparseInt[1]) << "v.getDataAt and v[] are not the same after the change\n";
}

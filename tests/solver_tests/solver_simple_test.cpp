//
// Created by Hadi Sinaee on 2019-01-25.
//

#include <gtest/gtest.h>
#include "../../src/solver/simple_solver.cpp"
#include "../../src/storage/mtx_vector.cpp"

class SimpleSolverTest : public ::testing::Test {
protected:
    void SetUp() override {
        this->mDenseDouble = "../data/solvers/L_double_lower_01.mtx";
        this->bDenseDouble = "../data/solvers/B_double_dense_01.mtx";
        this->bSparseDouble = "../data/solvers/B_double_sparse_01.mtx";

        this->correctAnswer = new double[4];
        this->correctAnswer[0] = 500;
        this->correctAnswer[1] = 0.117647058823529;
        this->correctAnswer[2] = -90.6363636363636;
        this->correctAnswer[3] = -93.5514705882353;

        this->sparseCorrectAnswer = new double[4];
        this->sparseCorrectAnswer[0] = 500;
        this->sparseCorrectAnswer[1] = 0.235294117647059;
    }

    std::string bDenseDouble, bSparseDouble, mDenseDouble;
    SimpleSolver<MtxMatrix<double>, MtxVector<double>> simpleSolver01;
    double *correctAnswer, *sparseCorrectAnswer;
    int NZ_Sparse = 2;
};

TEST_F(SimpleSolverTest, test01_4x4_dense) {
    MtxVector<double> b;

    ASSERT_EQ(0, b.readDataFrom(bDenseDouble)) << "has to be 0 for successful read operations";

    MtxMatrix<double> m;
    EXPECT_EQ(0, m.readDataFrom(mDenseDouble)) << "has to be 0 for successful read operations";

    SolverResult sr = simpleSolver01.solve(&m, &b);
    b.save("./", "_[dense]_s.mtx");
    for (int i = 0; i < 4; i++) {
        EXPECT_NEAR(b[i], this->correctAnswer[i], .000000005) << "the computed answer has to be the same";
    }

    EXPECT_EQ(sr.getSolverStatus(), 1);
}


TEST_F(SimpleSolverTest, test01_4x4_sparse) {
    MtxVector<double> b;

    ASSERT_EQ(0, b.readDataFrom(bSparseDouble)) << "has to be 0 for successful read operations";
    EXPECT_EQ(NZ_Sparse, b.getDimension()->getNonZeros()) << "vector none zero number is not correct.";

    MtxMatrix<double> m;
    EXPECT_EQ(0, m.readDataFrom(mDenseDouble)) << "has to be 0 for successful read operations";

    SolverResult sr = simpleSolver01.solve(&m, &b);
    b.save("./", "_[sparse]_s.mtx");

    for (int i = 0; i < 2; i++) {
        EXPECT_NEAR(b[i], this->sparseCorrectAnswer[i], .000000005) << "the computed answer has to be the same";
    }

    EXPECT_EQ(sr.getSolverStatus(), 1);
}
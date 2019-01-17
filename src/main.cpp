#include <iostream>
#include <omp.h>

#include "solver/simple_solver.cpp"
#include "solver/sparse_parallel_solver.cpp"
#include "solver/sparse_solver.cpp"
#include "storage/mtx_matrix.cpp"
#include "storage/mtx_vector.cpp"

// void simple(int n, float *a, float *b) {
//   int i;
// #pragma omp parallel for
//   for (int i = 0; i < n; i++) {
//     b[i] = (a[i] + a[i - 1]) / 2.0;
//   }
// }

int main(int argc, char **argv) {
  std::string vectorPath, matrixPath, outputPath, algorithmType;
  // for (int i = 1; i < argc; i += 2) {
  //   if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) {
  //     vectorPath = argv[i + 1];
  //   } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
  //     matrixPath = argv[i + 1];
  //   } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
  //     outputPath = argv[i + 1];
  //   } else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
  //     algorithmType = argv[i + 1];
  //   } else {
  //     std::cout << "warning: switch " << argv[i]
  //               << " doesn't supported or provided any value! \n";
  //   }
  // }
  //
  // if (vectorPath.length() == 0 || matrixPath.length() == 0) {
  //   std::cout << "vectorPath or matrixPath is empty.\n";
  //   return 1;
  // }
  //
  // if (outputPath.length() == 0) {
  //   outputPath = "./";
  // }
  //
  // if (algorithmType.length() == 0) {
  //   algorithmType = "NONE";
  // }
  // std::cout << "\n";

  // vector data
  // std::string filePath = "../data/b_sparse_af_0_k101.mtx";
  std::string filePath = "../data/b.mtx";
  vectorPath = filePath;
  MtxVector<long double> v;
  // v.readDataFrom(filePath);
  v.readDataFrom(vectorPath);

  auto vDim = v.getDimension();
  std::cout << "[Reading]>> Vector(" << vectorPath << "):\n"
            << "#rows=" << vDim->getRows()
            << ", #columns=" << vDim->getColumns()
            << ", #nonzeros=" << vDim->getNonZeros() << std::endl
            << std::endl;

  // matrix data
  MtxMatrix<long double> m;

  // filePath = "../data/af_0_k101.mtx";
  filePath = "../data/L.mtx";
  matrixPath = filePath;
  // m.readDataFrom(filePath);
  m.readDataFrom(matrixPath);

  std::cout << "[Reading]>> Matrix(" << matrixPath << "):\n"
            << "#rows=" << m.getDimension()->getRows()
            << ", #columns=" << m.getDimension()->getColumns()
            << ", #nonzeros=" << m.getDimension()->getNonZeros() << std::endl
            << std::endl;

  // if (algorithmType.compare("simple") == 0) {
  //   SimpleSolver<MtxMatrix<long double>, MtxVector<long double>> s;
  //
  //   SolverResult result = s.solve(&m, &v);
  //   v.save(outputPath, "ss.mtx");
  //   std::cout << "\n[Saved]>> the result saved in ["
  //             << outputPath + "ss.mtx]\n";
  // } else if (algorithmType.compare("sparse") == 0) {
  //   SparseSolver<MtxMatrix<long double>, MtxVector<long double>> ss;
  //
  //   SolverResult result = ss.solve(&m, &v);
  //   v.save(outputPath, "sps.mtx");
  //   std::cout << "\n[Saved]>> the result saved in ["
  //             << outputPath + "sps.mtx]\n";
  // } else {
  //   std::cout << "\n[Warning]>> Your algorithm type(-a) switch is "
  //             << algorithmType << " which is not supported.\n"
  //             << "Possible options are \"simple\" and \"sparse\"\n"
  //             << "Running \"simple\" as a default solver.\n\n";
  //
  //   SimpleSolver<MtxMatrix<long double>, MtxVector<long double>> s;
  //
  //   SolverResult result = s.solve(&m, &v);
  //   v.save(outputPath, "ss.mtx");
  //   std::cout << "\n[Saved]>> the result saved in ["
  //             << outputPath + "ss-default.mtx]\n";
  // }

  SparseParallelSolver<MtxMatrix<long double>, MtxVector<long double>> s;

  SolverResult result = s.solve(&m, &v);
  v.save("./", "sps_parallel.mtx");

  return 0;
}

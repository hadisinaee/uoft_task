#include <iostream>
#include <omp.h>

#include "solver/simple_solver.cpp"
#include "solver/sparse_parallel_solver.cpp"
#include "solver/sparse_solver.cpp"
#include "storage/mtx_matrix.cpp"
#include "storage/mtx_vector.cpp"

void showInfo(std::map<std::string, double> algorithmSteps, std::map<std::string, double> programSteps) {

    printf("\n%.*s\n", 42,
           "========================================================");
    printf("%-25s%-20s\n", "Step", "Time(mSec)");
    printf("%.*s\n", 42,
           "========================================================");
    for (auto &programStep : programSteps) {
        printf("%-25s%-20.15f\n", programStep.first.c_str(), programStep.second * 1000);
    }

    for (auto &algorithmStep : algorithmSteps) {
        printf("%-25s%-20.15f\n", algorithmStep.first.c_str(), algorithmStep.second * 1000);
    }
    printf("%.*s\n", 42,
           "----------------------------------------------");
}

void showHelp() {
    std::string helpString = "List of available switches: \n"
                             "\t-v vector_file_path, e.g: -v ./b.mtx\n"
                             "\t-m matrix_file_path, e.g: -m ./L.mtx\n"
                             "\t-o output_directory_path, e.g: -o ./\n"
                             "\t-a algorithm_type[simple, sparse, par_sparse], e.g: -a par_sparse";
    printf("%s\n", helpString.c_str());
}

int main(int argc, char **argv) {

    // defining variables for holding user arguments
    std::string vectorPath, matrixPath, outputPath, algorithmType;

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) {
            vectorPath = argv[i + 1];
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            matrixPath = argv[i + 1];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputPath = argv[i + 1];
        } else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            algorithmType = argv[i + 1];
        } else if (strcmp(argv[i], "-h") == 0) {
            showHelp();
            return 0;
        } else {
            printf("[WARNING]: switch %s isn't supported!\n", argv[i]);
        }
    }

    // checks for validity of the given paths
    if (vectorPath.length() == 0 || matrixPath.length() == 0) {
        printf("[ERROR]: variables {vectorPath} or {matrixPath} is empty. Add them by -v and -m respectively.\n");
        return 1;
    }

    // detects the output path
    if (outputPath.length() == 0) {
        printf("[WARNING]: the output path has not been specified. Choosing default path(./). Use -o to specify an output path.\n");
        outputPath = "./";
    }

    // detects the algorithm type
    if (algorithmType.length() == 0) {
        printf("[WARNING]: The algorithm type has not been specified. Running simple algorithm. Use -a to specify an algorithm.\n");
        algorithmType = "simple";
    }

    // creating a map for time
    std::map<std::string, double> stepsTime;

    // reading vector data
    printf("[READING]: reading vector data at (%s):\n", vectorPath.c_str());
    double vectorReadTime = omp_get_wtime();
    MtxVector<long double> v;
    v.readDataFrom(vectorPath);
    vectorReadTime = omp_get_wtime() - vectorReadTime;
    stepsTime.insert(std::pair<std::string, double>("read_vector", vectorReadTime));

    auto vDim = v.getDimension();
    printf("[READ]: the vector has been read. (#rows= %d #cols= %d #nz= %d)\n", vDim->getRows(), vDim->getColumns(),
           vDim->getNonZeros());


    // reading matrix data
    printf("[READING]: reading matrix data at (%s):\n", matrixPath.c_str());
    double matrixReadTime = omp_get_wtime();
    MtxMatrix<long double> m;
    m.readDataFrom(matrixPath);
    matrixReadTime = omp_get_wtime() - matrixReadTime;
    stepsTime.insert(std::pair<std::string, double>("read_matrix", matrixReadTime));

    auto mDim = m.getDimension();
    printf("[READ]: the matrix has been read. (#rows= %d #cols= %d #nz= %d)\n", mDim->getRows(), mDim->getColumns(),
           mDim->getNonZeros());


    // solving the the system based on the given algorithm option
    printf("[SOLVING]: solve the system using %s algorithm.\n", algorithmType.c_str());
    double algoTime = 0;
    SolverResult result;
    if ("simple" == algorithmType) {
        SimpleSolver<MtxMatrix<long double>, MtxVector<long double>> s;
        algoTime = omp_get_wtime();
        result = s.solve(&m, &v);
        algoTime = omp_get_wtime() - algoTime;

        printf("[SAVING]: successfully solved the system. Saving the result at %s%s.\n", outputPath.c_str(), "ss.mtx");
        v.save(outputPath, "simple.mtx");

    } else if ("sparse" == algorithmType) {
        SparseSolver<MtxMatrix<long double>, MtxVector<long double>> ss;
        algoTime = omp_get_wtime();
        result = ss.solve(&m, &v);
        algoTime = omp_get_wtime() - algoTime;

        printf("[SAVING]: successfully solved the system. Saving the result at %s.%s.\n", outputPath.c_str(),
               "sps.mtx");
        v.save(outputPath, "sparse.mtx");
    } else if ("par_sparse" == algorithmType) {
        SparseParallelSolver<MtxMatrix<long double>, MtxVector<long double>> ss;
        algoTime = omp_get_wtime();
        result = ss.solve(&m, &v);
        algoTime = omp_get_wtime() - algoTime;

        printf("[SAVING]: successfully solved the system. Saving the result at %s.%s.\n", outputPath.c_str(),
               "sps.mtx");
        v.save(outputPath, "parallel_sparse.mtx");
    } else {
        SimpleSolver<MtxMatrix<long double>, MtxVector<long double>> s;
        algoTime = omp_get_wtime();
        result = s.solve(&m, &v);
        algoTime = omp_get_wtime() - algoTime;

        v.save(outputPath, "simple.mtx");

        printf("[SAVED]: it successfully solved the system. Check %s for seeing the results.\n",
               outputPath.c_str());
    }
    stepsTime.insert(std::pair<std::string, double>("algo_total", algoTime));

    showInfo(result.getStepsTime(), stepsTime);

    return 0;
}

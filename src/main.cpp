#include <iostream>
#include <omp.h>
#include <iomanip>

#include "include/utils/colors.h"
#include "src/solver/simple_solver.cpp"
#include "src/solver/sparse_parallel_solver.cpp"
#include "src/solver/sparse_solver.cpp"
#include "src/storage/mtx_matrix.cpp"
#include "src/storage/mtx_vector.cpp"

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
    printf("%s %s", FWHT("[uoft_task]"), "list of available switches:\n");
    printf("\t%s %s\n", FWHT("[-v]"), FCYN("vector_file_path, e.g: -v ./b.mtx"));
    printf("\t%s %s\n", FWHT("[-m]"), FCYN("matrix_file_path, e.g: -m ./L.mtx"));
    printf("\t%s %s\n", FWHT("[-o]"), FCYN("output_directory_path, e.g: -o ./"));
    printf("\t%s %s\n", FWHT("[-a]"), FCYN("algorithm_type[simple, sparse, par_sparse], e.g: -a par_sparse"));
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
            printf("[%-10s] switch %s isn't supported!\n", FYEL("WARNING"), argv[i]);
        }
    }

    // checks for validity of the given paths
    if (vectorPath.length() == 0 || matrixPath.length() == 0) {
        printf("[%-10s] variables {vectorPath} or {matrixPath} is empty. Add them by -v and -m respectively.\n",
               FRED("ERROR"));
        return 1;
    }

    // detects the output path
    if (outputPath.length() == 0) {
        printf("[%-10s] the output path has not been specified. Choosing default path(./). Use -o to specify an output path.\n",
               FYEL("WARNING"));
        outputPath = "./";
    }

    // detects the algorithm type
    if (algorithmType.length() == 0) {
        printf("[%-10s] the algorithm type has not been specified. Running simple algorithm. Use -a to specify an algorithm.\n",
               FYEL("WARNING"));
        algorithmType = "simple";
    }

    // creating a map for time
    std::map<std::string, double> stepsTime;

    // reading vector data
    printf("[%-10s] reading vector data at (%s):\n", FGRN("READING"), vectorPath.c_str());
    double vectorReadTime = omp_get_wtime();
    MtxVector<long double> v;
    v.readDataFrom(vectorPath);
    vectorReadTime = omp_get_wtime() - vectorReadTime;
    stepsTime.insert(std::pair<std::string, double>("read_vector", vectorReadTime));

    auto vDim = v.getDimension();
    printf("[%-10s] the vector has been read. (#rows= %d #cols= %d #nz= %d)\n", FGRN("READ"), vDim->getRows(),
           vDim->getColumns(),
           vDim->getNonZeros());


    // reading matrix data
    printf("[%-10s] reading matrix data at (%s):\n", FGRN("READING"), matrixPath.c_str());
    double matrixReadTime = omp_get_wtime();
    MtxMatrix<long double> m;
    m.readDataFrom(matrixPath);
    matrixReadTime = omp_get_wtime() - matrixReadTime;
    stepsTime.insert(std::pair<std::string, double>("read_matrix", matrixReadTime));

    auto mDim = m.getDimension();
    printf("[%-10s] the matrix has been read. (#rows= %d #cols= %d #nz= %d)\n", FGRN("READ"), mDim->getRows(),
           mDim->getColumns(),
           mDim->getNonZeros());


    // solving the the system based on the given algorithm option
    printf("[%-10s] solve the system using %s algorithm.\n", FGRN("SOLVING"), algorithmType.c_str());
    double algoTime = 0;
    SolverResult result;
    if ("simple" == algorithmType) {
        SimpleSolver<MtxMatrix<long double>, MtxVector<long double>> s;
        algoTime = omp_get_wtime();
        result = s.solve(&m, &v);
        algoTime = omp_get_wtime() - algoTime;

        printf("[%-10s] successfully solved the system. Saving the result at %s%s.\n", FGRN("SAVING"),
               outputPath.c_str(),
               "simple_solver.mtx");
        v.save(outputPath, "simple_solver.mtx");

    } else if ("sparse" == algorithmType) {
        SparseSolver<MtxMatrix<long double>, MtxVector<long double>> ss;
        algoTime = omp_get_wtime();
        result = ss.solve(&m, &v);
        algoTime = omp_get_wtime() - algoTime;

        printf("[%-10s] successfully solved the system. Saving the result at %s%s.\n", FGRN("SAVING"),
               outputPath.c_str(),
               "sparse_solver.mtx");
        v.save(outputPath, "sparse_solver.mtx");
    } else if ("par_sparse" == algorithmType) {
        SparseParallelSolver<MtxMatrix<long double>, MtxVector<long double>> ss;
        algoTime = omp_get_wtime();
        result = ss.solve(&m, &v);
        algoTime = omp_get_wtime() - algoTime;

        printf("[%-10s] successfully solved the system. Saving the result at %s%s.\n", FGRN("SAVING"),
               outputPath.c_str(),
               "parallel_sparse_solver.mtx");
        v.save(outputPath, "parallel_sparse_solver.mtx");
    } else {
        SimpleSolver<MtxMatrix<long double>, MtxVector<long double>> s;
        algoTime = omp_get_wtime();
        result = s.solve(&m, &v);
        algoTime = omp_get_wtime() - algoTime;

        v.save(outputPath, "simple.mtx");

        printf("[%-10s] successfully solved the system. Saving the result at %s%s.\n", FGRN("SAVING"),
               outputPath.c_str(),
               "simple_solver_default.mtx");
    }
    stepsTime.insert(std::pair<std::string, double>("algo_total", algoTime));

    showInfo(result.getStepsTime(), stepsTime);

    return 0;
}

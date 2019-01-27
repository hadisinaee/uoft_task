#include "../../include/solver/sparse_parallel_solver.h"
#include "../../include/utils/dfs.h"
#include <omp.h>

/*
 * Parallel Sparse Lower Triangular Solver Lx=b
 * L is stored in the compressed column storage format
 *
 * Templates:
 * M : matrix template class
 * V : vector template class
 * T: type of data stored in matrix or vector
 *
 * Inputs:
 *  L: the matrix of storage type M
 *  b : the right hand-side of equation of storage type V
 * In/Out:
 *  x : the right hand-side b at start and the solution x at the end.
 *
 * Return:
 *  0: if there is an error while solving the equation
 *  1: successful operation
 */
template<class M, class V>
SolverResult SparseParallelSolver<M, V>::solve(M *L, V *b) {
    // stores the result of the solver
    SolverResult sr;

    // get dimension of the matrix
    int n = L->getDimension()->getRows();

    // creating G, a graph of (V, E) where,
    // V= { 0, 1, 2, ... ,dim_b }
    // E= { (j,i) | l_ij != 0 }
    // |V| = dim_b + 1 since the v indices start from 1
    Graph g(n + 1);

    // buildig G by iterating over matrix entries by column
    // retrieving row indicies of nonzero entries
    double graphTime = omp_get_wtime();
    std::list<int> *nzRowIndexList;
    for (int columnIndex = 1; columnIndex <= n; columnIndex++) {

        nzRowIndexList = L->getNoneZeroRowIndices(columnIndex);
        for (auto &it : *nzRowIndexList) {
            if (it == 0) {
                std::cout << columnIndex << "here" << std::endl;
            }
            // preventing self-loop since it will add the current columnIndes in DFS
            if (columnIndex != it)
                g.addEdge(columnIndex, it);
        }
    }
    graphTime = omp_get_wtime() - graphTime;
    sr.setStepTime("graph_creating", graphTime);

    // creating set B, a set of none_zeros of right hand side b
    std::list<int> *BList = b->getNoneZeroRowIndices(1);

    // creating the reach set of B, X = reach_L(B)
    double dfsTime = omp_get_wtime();
    for (auto &it : *BList) {
        g.DFS(it);
    }
    dfsTime = omp_get_wtime() - dfsTime;
    sr.setStepTime("dfs_search", dfsTime);

    // creating a sorted list of sorted vertices for creating a wavefront based on
    // the DFS tree.
    double depthCreationTime = omp_get_wtime();
    auto reachSetVector = g.getResultList();
    unsigned long reachSetSize = reachSetVector->size();
    auto *sortedVerticesList = new std::vector<int>[reachSetSize];

    for (int &it : *reachSetVector) {
        sortedVerticesList->push_back(it);
    }
    // std::cout << std::endl;
    sort(sortedVerticesList->begin(), sortedVerticesList->end());

    // creating a list of node depth of size the number of rows(n)
    std::map<int, int> depthMap;

    // initializing each depth to zero, depth(i) = 0 for all i=1,2,3, ..., n
    for (auto it = sortedVerticesList->begin(); it != sortedVerticesList->end();
         it++) {
        depthMap[*it] = 0;
    }

    // depth(i) = 1 + max_j{depth(j), where L(i,j) != 0}
    std::set<int> setOfParents;
    int maxDepth, maxLevel = 0;
    for (auto it = sortedVerticesList->begin(); it != sortedVerticesList->end();
         it++) {
        setOfParents = g.getParentOf(*it);
        maxDepth = 0;
        for (auto itp = setOfParents.begin(); itp != setOfParents.end(); itp++) {
            if (depthMap[*itp] > maxDepth)
                maxDepth = depthMap[*itp];
        }
        depthMap[*it] = 1 + maxDepth;
        if (maxLevel < 1 + maxDepth)
            maxLevel = 1 + maxDepth;
    }
    depthCreationTime = omp_get_wtime() - depthCreationTime;
    sr.setStepTime("depth_creation", depthCreationTime);

    // create a pointer for holding start of the new level in sortedVerticesList
    double levelCreationTime = omp_get_wtime();
    auto level = new int[maxLevel + 1];
    for (int i = 0; i < maxLevel + 1; i++) {
        level[i] = 0;
    }

    int prevLevel = 1;
    for (auto &itm : depthMap) {
        if (itm.second == prevLevel) {
            level[prevLevel] = level[prevLevel] + 1;
        } else {
            level[itm.second] = 1 + level[prevLevel];
            prevLevel = itm.second;
        }
    }
    levelCreationTime = omp_get_wtime() - levelCreationTime;
    sr.setStepTime("level_creation", levelCreationTime);

    // solving the the equations in the block in parallel
    // the column pointer of L
    int *Lp = L->getLp();

    // the row index of L
    int *Li = L->getLi();

    double tdata = omp_get_wtime();
    for (int l = 1; l <= maxLevel; l++) {
        int j1 = level[l - 1], j2 = level[l];

#pragma omp parallel for
        for (int k = j1; k < j2; k++) {
            int j = (*sortedVerticesList)[k] - 1;

            // x[j] /= Lx[Lp[j]];
            b->setDataAt(j, b->getDataAt(j) / (*L)[Lp[j]]);

            for (int p = Lp[j] + 1; p < Lp[j + 1]; p++) {
                // x[Li[p]] -= Lx[p] * x[j];
                b->setDataAt(Li[p], b->getDataAt(Li[p]) - (*L)[p] * b->getDataAt(j));
            }
        }
    }
    tdata = omp_get_wtime() - tdata;

    sr.setSolverStatus((short) 1);
    sr.setTime(tdata);
    sr.setStepTime("solve", tdata);
    return sr;
}

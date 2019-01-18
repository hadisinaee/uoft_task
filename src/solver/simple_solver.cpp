#include "../utils/dfs.cpp"
#include "simple_solver.h"
#include <omp.h>

// TODO: change direct access to Lp and Li. Make it available via a method
// access call.
/*
 * Lower triangular solver Lx=b
 * L is stored in the compressed column storage format
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
template<typename M, typename V>
SolverResult SimpleSolver<M, V>::solve(M *L, V *b) {
    // dimension of matrix L
    int dim_l = L->getDimension()->getColumns();
    SolverResult sr;

    // getting information about CSC format
    // the column pointer of L
    int *Lp = L->getLp();
    // the row index of L
    int *Li = L->getLi();

    // checking input values
    if (!Lp || !Li || b->isEmpty()) {
        sr.setSolverStatus((short) 0);
        sr.setTime(-1);
        return sr;
    }

    double tdata = omp_get_wtime();
    for (int j = 0; j < dim_l; j++) {
        // x[j] /= Lx[Lp[j]];
        b->setDataAt(j, b->getDataAt(j) / (*L)[Lp[j]]);

        for (int p = Lp[j] + 1; p < Lp[j + 1]; p++) {
            // x[Li[p]] -= Lx[p] * x[j];
            b->setDataAt(Li[p], b->getDataAt(Li[p]) - (*L)[p] * b->getDataAt(j));
        }
    }
    tdata = omp_get_wtime() - tdata;

    sr.setSolverStatus((short) 1);
    sr.setTime(tdata);
    sr.setStepTime("solve", tdata);

    return sr;
}

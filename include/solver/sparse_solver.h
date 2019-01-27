//
// Created by Hadi Sinaee on 2019-01-26.
//

#ifndef UOFT_TASK_SPARSE_SOLVER_H
#define UOFT_TASK_SPARSE_SOLVER_H

#include "../storage/mtx_matrix.h"
#include "../storage/mtx_vector.h"
#include "base_solver.h"

/**
 * SparseSolver implements a Solver abstract class. Showing a sparse solution
 * implementation for the Lx=b system. It uses a DFS for predicting nonzero
 * entries of the final solution. In this regard, it will reduce amount of
 * computation needed for sparse conditions.
 */
template<typename M, typename V>
class SparseSolver : Solver<M, V> {
public:
    // solves Lx=b for L of type M and x and b of type V
    SolverResult solve(M *, V *);
};

#endif //UOFT_TASK_SPARSE_SOLVER_H

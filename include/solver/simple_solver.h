
#ifndef BASE_SIMPLE_SOLVER_H
#define BASE_SIMPLE_SOLVER_H

#include "../storage/mtx_matrix.h"
#include "../storage/mtx_vector.h"
#include "base_solver.h"

/**
 * SimpleSolver implements a Solver abstract class. Showing a verbose
 * implementation for the Lx=b system.
 */
template <typename M, typename V> class SimpleSolver : Solver<M, V> {
public:
    // solves Lx=b for L of type M and x and b of type V
    // return 0 in the case of error or 1 o.w.
    SolverResult solve(M *, V *);
};


#endif
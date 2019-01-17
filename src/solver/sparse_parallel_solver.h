#include "../storage/mtx_matrix.h"
#include "../storage/mtx_vector.h"
#include "base_solver.h"

/**
 * SparseParallelSolver implements a Solver abstract class. Showing a sparse
 * parallel solution implementation for the Lx=b system. It uses wavefront
 * segmentation to identify blocks that can be solved in parallel.
 */
template <typename M, typename V> class SparseParallelSolver : Solver<M, V> {
public:
  // solves Lx=b for L of type M and x and b of type V
  SolverResult solve(M *, V *);
};

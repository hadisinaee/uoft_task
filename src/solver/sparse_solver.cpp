#include "../utils/dfs.h"
#include "sparse_solver.h"

/*
 * Sparse Lower Triangular Solver Lx=b
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
template <class M, class V> SolverResult SparseSolver<M, V>::solve(M *L, V *b) {
  // stores the result of the solver
  SolverResult sr;

  // getting number of unknowns
  int dim_b = b->getDimension()->getRows();

  // creating G, a graph of (V, E) where,
  // V= { 0, 1, 2, ... ,dim_b }
  // E= { (j,i) | l_ij != 0 }
  // |V| = dim_b + 1 since the v indices start from 1
  Graph g(dim_b + 1);

  // buildig G by iterating over matrix entries by column
  // retrieving row indicies of nonzero entries
  std::list<int> *nzRowIndexList;
  for (int columnIndex = 1; columnIndex <= dim_b; columnIndex++) {
    nzRowIndexList = L->getNoneZeroRowIndices(columnIndex);
    for (auto it = nzRowIndexList->begin(); it != nzRowIndexList->end(); it++) {
      if (*it == 0) {
        std::cout << columnIndex << "here" << std::endl;
      }
      // preventing self-loop since it will add the current columnIndes in DFS
      if (columnIndex != *it)
        g.addEdge(columnIndex, *it);
    }
  }

  // creating set B, a set of nonzeros of right hand side b
  std::list<int> *BList = b->getNoneZeroRowIndices(1);

  // creating the reach set of B, X = reach_L(B)
  for (auto it = BList->begin(); it != BList->end(); it++) {
    g.DFS(*it);
  }

  // getting information about CSC format
  // the column pointer of L
  int *Lp = L->getLp();
  // the row index of L
  int *Li = L->getLi();

  // checking input values
  if (!Lp || !Li || b->isEmpty()) {
    sr.setSolverStatus((short)12);
    sr.setTime((long int)-1);
    return sr;
  }

  int j = 0;
  for (auto jit = g.getResultList()->begin(); jit != g.getResultList()->end();
       jit++) {
    j = *jit;

    // x[j] /= Lx[Lp[j]];
    b->setDataAt(j, b->getDataAt(j) / (*L)[Lp[j]]);

    for (int p = Lp[j] + 1; p < Lp[j + 1]; p++) {
      // x[Li[p]] -= Lx[p] * x[j];
      b->setDataAt(Li[p], b->getDataAt(Li[p]) - (*L)[p] * b->getDataAt(j));
    }
  }

  sr.setSolverStatus((short)1);
  sr.setTime((long int)-100);
  return sr;
}

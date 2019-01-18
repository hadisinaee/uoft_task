#ifndef BASE_SOLVER_H
#define BASE_SOLVER_H

/**
 * SolverResult is the return type of any solver containing information about
 * the solver such as amount of time it has spent on the task and the status of
 * the solver.
 *
 * Fileds:
 *  t(long int): stores amout of time the solver has spent
 *  s(short): status code showing the final status of the solver
 */
class SolverResult {
private:
    double t;
  short s;

public:
    double getTime() { return this->t; }
  short getSolverStatus() { return this->s; }

    void setTime(const double value) { this->t = value; }
  void setSolverStatus(const short value) { this->s = value; }
};

/**
 * Solver is a abstract class representing any solver behavior for Lx=b. These
 * solvers has to work with two types, Matrix(L) and Vector(b).
 *
 * Method(s):
 * SolverResult solve(MatrixType *, VectorType *): solves the system for
 * L(MatrixType)x=b(VectorType) and returns SolverResult object
 */
template <typename MatrixType, typename VectorType> class Solver {
public:
  // solves Lx=b for L of type M and x and b of type V
  // returns a SolverResult object indicate useful info about the solve
  virtual SolverResult solve(MatrixType *, VectorType *) = 0;
};

#endif

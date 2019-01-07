#include "mtx_matrix.h"
#include <algorithm>

MtxMatrix::MtxMatrix(int M, int N, double fillerValue) {
  // creates the array of M*N size
  this->data = new double[M*N];
  std::fill(this->data, this->data + M*N, fillerValue);
}

MtxMatrix::MtxMatrix(int M, int N) {
  // creates the array of M*N size
  this->data = new double[M*N];
  std::fill(this->data, this->data + M*N, 0.);
}

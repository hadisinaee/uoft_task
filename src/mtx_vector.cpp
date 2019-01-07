#include "mtx_vector.h"
#include <algorithm>

MtxVector::MtxVector(int M, double fillerValue) {
  this->M = M;
  // creates the array of M size
  this->data = new long double[M];
  std::fill(this->data, this->data + M, fillerValue);
}

MtxVector::MtxVector(int M) : MtxVector(M, 0.){}

int MtxVector::getM() {
  return this->M;
}

void MtxVector::setDataAt(int idx, long double value) {
  this->data[idx] = value;
}

double MtxVector::getDataAt(int idx) {
  return this->data[idx];
}

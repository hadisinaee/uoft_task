// my first program in C++
#include <iostream>
#include <omp.h>

#include "mtx_vector.cpp"
#include "mtx_matrix.cpp"

void simple(int n, float *a, float *b) {
  int i;
  #pragma omp parallel for
  for(int i=0; i < n ; i++){
    b[i] = (a[i] + a[i-1]) / 2.0;
  }
}

int main()
{
  std::string filePath = "../data/af_0_k101_b.mtx";
  MtxVector v;
  v.readMtxData(filePath);

  std::cout << v.getM() << std::endl
            << v.getDataAt(5) << std::endl;

  MtxMatrix m;

  filePath = "../data/af_0_k101.mtx";
  m.readMtxData(filePath);

  std::cout << "M=" << m.getM() << ", N=" << m.getN() << ", L=" << m.getL() << std::endl;

  return 0;
}

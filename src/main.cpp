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

// TODO: add argc
int main()
{
  std::string filePath = "../data/af_0_k101_b.mtx";
  MtxVector<long double> v;
  v.readMtxData(filePath);

  std::cout << "Vector:" << std::endl
            << "#Rows=" << v.getM() << std::endl;

  MtxMatrix<long double> m;

  filePath = "../data/af_0_k101.mtx";
  m.readMtxData(filePath);

  std::cout << "Matrix:" << std::endl
            << "#Rows=" << m.getM() << ", #Columns=" << m.getN() << ", #NonZeros=" << m.getL() << std::endl;

  return 0;
}

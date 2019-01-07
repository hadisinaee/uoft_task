// my first program in C++
#include <iostream>
#include <omp.h>
#include "mtx_reader.cpp"
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
  MtxReader<MtxVector> mr;

  std::string filePath = "../data/af_0_k101_b.mtx";
  MtxVector V = mr.readMtxData(filePath, false);

  // make 20 a configurable value
  std::cout << std::setprecision(20);
  std::cout << V.getM() << nl
            << V.getDataAt(5);
  // #pragma omp parallel
  // {
  //   cout << "Hello ";
  //   cout << "World!\n";
  // }
}

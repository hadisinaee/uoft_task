#include "mtx_matrix.h"
#include <fstream>
#include <algorithm>

template <class T>
int MtxMatrix<T>::getM() {
  return this->M;
}

template <class T>
int MtxMatrix<T>::getN() {
  return this->N;
}

template <class T>
int MtxMatrix<T>::getL() {
  return this->L;
}
template <class T>
T MtxMatrix<T>::getDataAt(int idx) {
  return this->data[idx];
}

template <class T>
void MtxMatrix<T>::setDataAt(int idx, T value) {
  this->data[idx] = value;
}

template <class T>
void MtxMatrix<T>::readMtxData(std::string filePath) {
  // open the file
  std::ifstream fin(filePath);

  // ignore headers and comments
  while (fin.peek() == '%') fin.ignore(2048, '\n');

  fin >> this->M >> this->N >> this->L;

  this->data = new long double[L];
  this->col = new int[L+1];
  this->row = new int[L];

  this->col[0] = 0;
  this->col[1] = 0;

  int m, n, idx;
  long double data;
  // read the data
  for (int l = 0, pn = 1; l < L; l++)
  {
    fin >> this->row[l] >> n >> this->data[l];
    if (n-pn == 0) { // if on the same column
      this->col[pn]++;
    } else {
      this->col[n] = this->col[pn] + 1;
      pn = n;
    }
  }

  // std::cout << "COL: ";
  // for(int i=0; i<5; i++){
  //   std::cout << this->col[i] << " ";
  // }
  //
  // std::cout << std::endl << "ROW: ";
  // for(int i=0; i<20; i++){
  //   std::cout << this->row[i] << " ";
  // }
  //
  // std::cout << std::endl << "DATA: ";
  // for(int i=0; i<20; i++){
  //   std::cout << this->data[i] << " ";
  // }
  //
  // std::cout << std::endl;

  fin.close();
}

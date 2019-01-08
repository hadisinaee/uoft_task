#include "mtx_matrix.h"
#include <fstream>
#include <algorithm>

int MtxMatrix::getM() {
  return this->M;
}

int MtxMatrix::getN() {
  return this->N;
}

int MtxMatrix::getL() {
  return this->L;
}

long double MtxMatrix::getDataAt(int idx) {
  return this->data[idx];
}

void MtxMatrix::setDataAt(int idx, long double value) {
  this->data[idx] = value;
}

void MtxMatrix::readMtxData(std::string filePath) {
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
  for (int l = 0, pn = 1; l < 30; l++)
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

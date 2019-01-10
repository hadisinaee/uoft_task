#include "mtx_matrix.h"
#include <algorithm>
#include <fstream>
#include <list>

template <class T> int MtxMatrix<T>::getM() { return this->M; }

template <class T> int MtxMatrix<T>::getN() { return this->N; }

template <class T> int MtxMatrix<T>::getNZ() { return this->NZ; }

template <class T> int *MtxMatrix<T>::getLi() { return this->Li; }

template <class T> int *MtxMatrix<T>::getLp() { return this->Lp; }

template <class T> T *MtxMatrix<T>::getLx() { return this->Lx; }

template <class T> T MtxMatrix<T>::operator[](int idx) { return this->Lx[idx]; }

template <class T> T MtxMatrix<T>::getDataAt(int idx) { return this->Lx[idx]; }

template <class T> void MtxMatrix<T>::setDataAt(int idx, T value) {
  this->Lx[idx] = value;
}

template <class T> void MtxMatrix<T>::readMtxData(std::string filePath) {
  // open the file
  std::ifstream fin(filePath);

  // ignore headers and comments
  while (fin.peek() == '%')
    fin.ignore(2048, '\n');

  fin >> this->M >> this->N >> this->NZ;

  this->Lx = new long double[this->NZ];
  this->Lp = new int[this->NZ + 1];
  this->Li = new int[this->NZ];

  this->Lp[0] = 0;
  this->Lp[1] = 0;

  int m, n, idx;
  long double data;
  // read the data
  for (int l = 0, pn = 1; l < this->NZ; l++) {
    fin >> this->Li[l] >> n >> this->Lx[l];
    if (n - pn == 0) { // if on the same column
      this->Lp[pn]++;
    } else {
      this->Lp[n] = this->Lp[pn] + 1;
      pn = n;
    }
  }

  // std::cout << "COL: ";
  // for(int i=0; i<5; i++){
  //   std::cout << this->Lp[i] << " ";
  // }
  //
  // std::cout << std::endl << "ROW: ";
  // for(int i=0; i<20; i++){
  //   std::cout << this->Li[i] << " ";
  // }
  //
  // std::cout << std::endl << "DATA: ";
  // for(int i=0; i<20; i++){
  //   std::cout << this->Lx[i] << " ";
  // }
  //
  // std::cout << std::endl;

  fin.close();
}

template <class T> bool MtxMatrix<T>::isEmpty() { return !this->Lx; }

template <class T> std::list<T> *MtxMatrix<T>::getColumn(const int idx) {
  // computing the length of the column
  int columnLength = this->Lp[idx] - this->Lp[idx - 1];

  // creating a list of column data with the computed length of the given index
  std::list<T> *columnList = new std::list<T>[columnLength];

  // iterating over nonzero data of the given index column
  // saving them inside a list
  for (int i = this->Lp[idx - 1]; i < this->Lp[idx]; i++) {
    columnList->push_back(this->Lx[i]);
  }

  return columnList;
}

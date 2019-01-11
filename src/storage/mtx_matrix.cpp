#include "mtx_matrix.h"
#include <algorithm>
#include <fstream>
#include <list>

template <class DataType>
void MtxMatrix<DataType>::readDataFrom(std::string filePath) {
  // open the file
  std::ifstream fin(filePath);
  this->dim = Dimension();

  // ignore headers and comments
  while (fin.peek() == '%')
    fin.ignore(2048, '\n');

  // reading information of the matrix from the first line
  int rows, columns, nz;
  fin >> rows >> columns >> nz;

  // setting matrix information in Dimension
  this->dim.setRows(rows);
  this->dim.setColumns(columns);
  this->dim.setNonZeros(nz);

  // initializing Lx(value array), Lp(pointer array), Li(indices array)
  this->Lx = new DataType[nz];
  this->Lp = new int[nz + 1];
  this->Li = new int[nz];

  this->Lp[0] = 0;
  this->Lp[1] = 0;

  // reading matrix entries
  int m, n, idx;
  DataType data;
  for (int l = 0, pn = 1; l < nz; l++) {
    fin >> this->Li[l] >> n >> this->Lx[l];
    if (n - pn == 0) { // if they are on the same column
      this->Lp[pn]++;
    } else {
      this->Lp[n] = this->Lp[pn] + 1;
      pn = n;
    }
  }

  // std::cout << "COL: ";
  // for (int i = 0; i < 5; i++) {
  //   std::cout << this->Lp[i] << " ";
  // }
  //
  // std::cout << std::endl << "ROW: ";
  // for (int i = 0; i < 20; i++) {
  //   std::cout << this->Li[i] << " ";
  // }
  //
  // std::cout << std::endl << "DADataTypeA: ";
  // for (int i = 0; i < 20; i++) {
  //   std::cout << this->Lx[i] << " ";
  // }
  //
  // std::cout << std::endl;

  fin.close();
}

template <class DataType> Dimension *MtxMatrix<DataType>::getDimension() {
  return &this->dim;
}

template <class DataType> void MtxMatrix<DataType>::save(std::string path) {
  return;
}

template <class DataType> bool MtxMatrix<DataType>::isEmpty() {
  return !this->Lx;
}

template <class DataType>
std::list<DataType> *MtxMatrix<DataType>::getColumn(const int idx) {
  // computing the length of the column
  int columnLength = this->Lp[idx] - this->Lp[idx - 1];

  // creating a list of column data with the computed length of the given index
  std::list<DataType> *columnList = new std::list<DataType>[columnLength];

  // iterating over nonzero data of the given index column
  // saving them inside a list
  for (int i = this->Lp[idx - 1]; i < this->Lp[idx]; i++) {
    columnList->push_back(this->Lx[i]);
  }

  return columnList;
}

template <class DataType> DataType MtxMatrix<DataType>::getDataAt(int idx) {
  return this->Lx[idx];
}

template <class DataType>
void MtxMatrix<DataType>::setDataAt(int idx, DataType value) {
  this->Lx[idx] = value;
}

template <class DataType>
std::list<int> *MtxMatrix<DataType>::getNoneZeroRowIndices(const int idx) {
  // computing the length of the column
  int columnLength = this->Lp[idx] - this->Lp[idx - 1];

  // creating a list of column data with the computed length of the given index
  std::list<int> *rowIndicesList = new std::list<int>[columnLength];

  // iterating over nonzero data of the given index column
  // saving them inside a list
  for (int i = this->Lp[idx - 1]; i < this->Lp[idx]; i++) {
    rowIndicesList->push_back(this->Li[i]);
  }

  return rowIndicesList;
}

template <class DataType> DataType MtxMatrix<DataType>::operator[](int idx) {
  return this->Lx[idx];
}

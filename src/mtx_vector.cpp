#include "mtx_vector.h"
#include <algorithm>
#include <fstream>

template <class T> int MtxVector<T>::getM() { return this->M; }

template <class T> void MtxVector<T>::setDataAt(int idx, T value) {
  this->data[idx] = value;
}

template <class T> T MtxVector<T>::getDataAt(int idx) {
  return this->data[idx];
}

template <class T> void MtxVector<T>::readMtxData(std::string filePath) {
  int c;
  // open the file
  std::ifstream fin(filePath);

  // ignore headers and comments
  while (fin.peek() == '%')
    fin.ignore(2048, '\n');

  // read in dimension of vector
  fin >> this->M >> c;

  // create the vector values
  this->data = new T[M];

  // read the the vector data
  T input = 0;
  int idx = 0;
  while (fin >> input) {
    this->setDataAt(idx, input);
    idx++;
  }

  fin.close();
}

template <class T> bool MtxVector<T>::isEmpty() { return !this->data; }

template <class T> T MtxVector<T>::operator[](int idx) {
  return this->data[idx];
}

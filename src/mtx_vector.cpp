#include "mtx_vector.h"
#include <fstream>
#include <algorithm>

int MtxVector::getM() {
  return this->M;
}

void MtxVector::setDataAt(int idx, long double value) {
  this->data[idx] = value;
}

double MtxVector::getDataAt(int idx) {
  return this->data[idx];
}

void MtxVector::readMtxData(std::string filePath) {
  int c;
  // open the file
  std::ifstream fin(filePath);

  // ignore headers and comments
  while (fin.peek() == '%') fin.ignore(2048, '\n');

  // read in dimensions
  fin >> this->M >> c;

  // create the vector values
  this->data = new long double[M];

  // read the the vector data
  long double input = 0;
  int idx = 0;
  while (fin >> input) {
    this->setDataAt(idx, input);
    idx++;
  }

  fin.close();
}

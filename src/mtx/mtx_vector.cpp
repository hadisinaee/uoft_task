#include "mtx_vector.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

template <typename DataType>
void MtxVector<DataType>::readDataFrom(std::string filePath) {
  // open the file
  std::ifstream fin(filePath);
  this->dim = Dimension();

  // ignore headers and comments
  while (fin.peek() == '%')
    fin.ignore(2048, '\n');

  // reading line by line
  // the first line contains the information of the vector
  std::string line;
  std::getline(fin, line);

  // Vector of string to save tokens
  std::vector<std::string> tokens;

  // stringstream class check1
  std::stringstream check1(line);

  std::string intermediate;

  // Tokenizing w.r.t. space ' '
  while (getline(check1, intermediate, ' ')) {
    tokens.push_back(intermediate);
  }

  // checks for sparsity of the vector
  // 3 parts if it is a sparse vector with nonzero part
  // 2 parts if it is a dense vector
  this->dim.setRows(std::stoi(tokens[0]));
  this->dim.setColumns(std::stoi(tokens[1]));
  if (tokens.size() == 3) {
    this->dim.setNonZeros(std::stoi(tokens[2]));
  }

  // create the vector values
  // std::cout << this->dim.getColumns() << std::endl;
  this->data = new DataType[this->dim.getRows()];

  // read the the vector data
  DataType input = 0;
  int idx = 0;
  while (fin >> input) {
    this->setDataAt(idx, input);
    if (input != 0) {
    }
    idx++;
  }

  fin.close();
}

template <typename DataType> Dimension *MtxVector<DataType>::getDimension() {
  return &this->dim;
}

template <typename DataType>
void MtxVector<DataType>::save(std::string outputPath) {
  return;
}

template <typename DataType> bool MtxVector<DataType>::isEmpty() {
  return !this->data;
}

template <typename DataType>
std::list<int> *MtxVector<DataType>::getNoneZeroRowIndices(const int indx) {
  return this->nzRowIndices;
}

template <typename DataType> DataType MtxVector<DataType>::getDataAt(int idx) {
  return this->data[idx];
}

template <typename DataType>
void MtxVector<DataType>::setDataAt(int idx, DataType value) {
  this->data[idx] = value;
}

template <typename DataType> DataType MtxVector<DataType>::operator[](int idx) {
  return this->data[idx];
}

template <typename DataType>
std::list<DataType> *MtxVector<DataType>::getColumn(const int idx) {
  // doesn't apply for vectors
  return NULL;
}

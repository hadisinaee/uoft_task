#ifndef MTX_MATRIX_H
#define MTX_MATRIX_H

#include "csc_storage_format.h"
#include <list>

/**
 * MtxMatrix is an implementation of CSCStorageFormat abstract class
 * representing CSC format for a matrix.
 */
template <class DataType> class MtxMatrix : CSCStorageFormat<DataType> {
public:
  // reads a file of .mtx
  void readDataFrom(std::string);
  // returns dimension of the vector(n*1)
  Dimension *getDimension();
  // saves the data in the given path
  void save(std::string, std::string);
  // checks for emptiness of Lx
  bool isEmpty();
  // get a column array of a column
  std::list<DataType> *getColumn(const int);
  // overloading [] oberator for accessing data
  DataType getDataAt(const int);
  // set a value in the given index
  void setDataAt(const int, const DataType);
  // a list of nonzero indices of the vector
  std::list<int> *getNoneZeroRowIndices(const int);
  // returns the value at the given index
  DataType operator[](int);
  // getter of column pointer array
  int *getLp();
  // getter of indicies array
  int *getLi();

private:
  // information about the matrix
  Dimension dim;
  // row values; nonzero values from the matrix
  DataType *Lx;
  // coloumn pointer; indices associated with the first entry in column
  int *Lp;
  // row index; indices associated with the row of nonzero
  int *Li;
};

#endif

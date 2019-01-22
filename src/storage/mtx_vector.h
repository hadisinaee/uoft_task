#ifndef MTX_VECTOR_H
#define MTX_VECTOR_H

#include "csc_storage_format.h"
#include <list>
#include <set>

/**
 * MtxVector is an implementation of CSCStorageFormat abstract class
 * representing CSC format for a vector.
 */
template <class DataType> class MtxVector : CSCStorageFormat<DataType> {
public:
  // read file from .mtx
  void readDataFrom(std::string);
  // returns dimension of the vector(n*1)
  Dimension *getDimension();
  // saves the data in the given path
  void save(std::string, std::string);
  // checks for emptiness of the vector
  bool isEmpty();
  // a list of nonzero indices of the vector
  std::list<int> *getNoneZeroRowIndices(int);
  // overloading [] oberator for accessing data
  DataType getDataAt(int);
  // set a value in the given index
  void setDataAt(int, DataType);
  // returns the value at the given index
  DataType operator[](int);
  // the same as getDataAt since it is a vector of size(n*1)
  std::list<DataType> *getColumn(int);
  // getter of column pointer array
  int *getLp();
  // getter of indicies array
  int *getLi();

private:
  // information about the dimension and sparsity of the vectore
  Dimension dim{};
  // row values; nonzero values from the matrix
  DataType *Lx;
    // column pointer; indices associated with the first entry in column
    int *Lp{};
  // row index; indices associated with the row of nonzero
  int *Li{};
  // raw data of the vector containing both zeros and non-zeros
  DataType *raw_data;
    // a list of available indices
    std::set<int> availableIndices;
};

#endif

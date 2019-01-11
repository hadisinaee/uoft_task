#include "csc_storage_format.h"
#include <list>

/**
 * This class implements CSCStorageFormat class.
 * Please refer to the doc for more information about the base methods.
 *
 * MtxVector represents a CSC storage format for a vector representation.
 */
template <class DataType> class MtxVector : CSCStorageFormat<DataType> {
public:
  // read file from .mtx
  void readDataFrom(const std::string);
  // returns dimension of the vector(n*1)
  Dimension *getDimension();
  // saves the data in the given path
  void save(std::string);
  // checks for emptiness of the vector
  bool isEmpty();
  // a list of nonzero indices of the vector
  std::list<int> *getNoneZeroRowIndices(const int);
  // overloading [] oberator for accessing data
  DataType getDataAt(const int);
  // set a value in the given index
  void setDataAt(const int, const DataType);
  // returns the value at the given index
  DataType operator[](int);
  // the same as getDataAt since it is a vector of size(n*1)
  std::list<DataType> *getColumn(const int);

private:
  // information about the dimension and sparsity of the vectore
  Dimension dim;
  // vector's data
  DataType *data;
  // a list of nonzeros indicies
  std::list<int> *nzRowIndices;
};

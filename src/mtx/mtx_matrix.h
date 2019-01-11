#include "csc_storage_format.h"
#include <list>

template <class DataType> class MtxMatrix : CSCStorageFormat<DataType> {
private:
  Dimension dim; // information about the matrix
  DataType *Lx;  // row values; nonzero values from the matrix
  int *Lp; // coloumn pointer; indices associated with the first entry in column
  int *Li; // row index; indices associated with the row of nonzero

public:
  // reads a file of .mtx
  void readDataFrom(std::string);
  // returns dimension of the vector(n*1)
  Dimension *getDimension();
  // saves the data in the given path
  void save(std::string);
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
};

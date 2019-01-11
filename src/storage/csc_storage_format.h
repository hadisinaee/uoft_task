#ifndef STORAGE_FORMAT_H
#define STORAGE_FORMAT_H

#include "base_storage_format.h"
#include <list>

/**
 * CSCStorageFormat is an abstract class derived from StorageFormat representing
 * behavior of CSC storage format.
 *
 * Methods:
 *  virtual bool isEmpty(): checks for emptiness of the data
 *  virtual std::list<DataType> *getColumn(const int): get a column of the given
 * index
 *
 *   virtual std::list<int> *getNoneZeroRowIndices(const int): get a list of row
 * indicies for the given column
 *
 *  virtual DataType getDataAt(const int): returns the data at the given index
 *  virtual void setDataAt(const int, const DataType): set the data at the given
 * index
 *
 *  virtual DataType operator[](const int): overload [] for accessing Lx items
 */
template <typename DataType> class CSCStorageFormat : StorageFormat<DataType> {
public:
  virtual bool isEmpty() = 0;

  virtual std::list<DataType> *getColumn(const int) = 0;
  virtual std::list<int> *getNoneZeroRowIndices(const int) = 0;

  virtual DataType getDataAt(const int) = 0;
  virtual void setDataAt(const int, const DataType) = 0;

  virtual DataType operator[](const int) = 0;
};

#endif

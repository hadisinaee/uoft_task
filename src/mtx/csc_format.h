#ifndef STORAGE_FORMAT_H
#define STORAGE_FORMAT_H

#include "mtx.h"
#include <list>

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

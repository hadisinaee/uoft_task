#ifndef MTX_H
#define MTX_H

#include <list>

class Dimension {
private:
  int rows;
  int columns;
  int nonzeros;

public:
  int getRows() { return this->rows; }
  int getColumns() { return this->columns; }
  int getNonZeros() { return this->nonzeros; }

  void setRows(const int value) { this->rows = value; }
  void setColumns(const int value) { this->columns = value; }
  void setNonZeros(const int value) { this->nonzeros = value; }
};

template <typename DataType> class StorageFormat {
public:
  virtual void readDataFrom(const std::string) = 0;
  virtual Dimension *getDimension() = 0;
  virtual void save(std::string) = 0;
};

#endif

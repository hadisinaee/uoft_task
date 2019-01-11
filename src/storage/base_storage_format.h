#ifndef MTX_H
#define MTX_H

#include <list>

/**
 * Dimension represent useful information such as:
 *  1- rows: number of rows
 *  2- columns: number of columns
 *  3- nonzeros: number of nonzeros
 * for any matrix and vector.
 */
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

/**
 * StorageFormat represents an abstract class for any storage format.
 *
 * Methods:
 *  void readDataFrom(const std::string): reads data from the given path
 *  Dimension *getDimension(): returns information about the matrix or vector
 * entity
 *  void save(std::string, std::string): saves data to the given path with the
 * given name
 */
template <typename DataType> class StorageFormat {
public:
  virtual void readDataFrom(const std::string) = 0;
  virtual Dimension *getDimension() = 0;
  virtual void save(std::string, std::string) = 0;
};

#endif

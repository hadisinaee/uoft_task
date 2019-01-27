#ifndef MTX_H
#define MTX_H

#include <list>

/**
 * Dimension represent useful information such as:
 *  1- rows: number of rows
 *  2- columns: number of columns
 *  3- none_zeros: number of nonzeros
 * for any matrix and vector.
 */
class Dimension {
private:
    int rows;
    int columns;
    int none_zeros;

public:
    int getRows() { return this->rows; }

    int getColumns() { return this->columns; }

    int getNonZeros() { return this->none_zeros; }

    void setRows(const int value) { this->rows = value; }

    void setColumns(const int value) { this->columns = value; }

    void setNonZeros(const int value) { this->none_zeros = value; }
};

/**
 * StorageFormat represents an abstract class for any storage format.
 *
 * Methods:
 *  int readDataFrom(const std::string): reads data from the given path, returns the status of the operation.
 *      returns
 *          -1 : not implemented
 *          0  : success
 *          1  : filePath is not valid
 *          2  : cannot open the file
 *
 *  Dimension *getDimension(): returns information about the matrix or vector
 * entity
 *  void save(std::string, std::string): saves data to the given path with the
 * given name
 */
template<typename DataType>
class StorageFormat {
public:
    virtual int readDataFrom(const std::string) = 0;

    virtual Dimension *getDimension() = 0;

    virtual int save(std::string, std::string) = 0;
};

#endif

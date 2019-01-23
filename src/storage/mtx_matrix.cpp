#include "mtx_matrix.h"
#include <algorithm>
#include <fstream>
#include <list>

template<typename DataType>
void MtxMatrix<DataType>::readDataFrom(std::string filePath) {
    // checks that the given path is valid
    if (filePath.empty()) {
        return;
    }

    // open the file
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        return;
    }

    this->dim = Dimension();

    // represent that the given file is a dense or a sparse vector
    bool isDense = true;

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
        isDense = false;
    } else {
        this->dim.setNonZeros(this->dim.getRows() * this->dim.getColumns());
    }

    // reading information of the matrix from the first line
    auto columns = this->getDimension()->getColumns(),
            nz = this->getDimension()->getNonZeros();


    // initializing Lx(value array), Lp(pointer array), Li(indices array)
    this->Lx = new DataType[nz];
    for (int i = 0; i < nz; i++) {
        this->Lx[i] = (DataType) 0;
    }
    this->Lp = new int[columns + 1];
    this->Li = new int[nz];

    this->Lp[0] = 0;
    this->Lp[1] = 0;

    // reading matrix entries
    int n;
    for (int l = 0, pn = 1; l < nz; l++) {
        fin >> this->Li[l] >> n >> this->Lx[l];
        if (n - pn == 0) { // if they are on the same column
            this->Lp[pn]++;
        } else {
            this->Lp[n] = this->Lp[pn] + 1;
            pn = n;
        }
    }

    fin.close();
}

template<typename DataType>
Dimension *MtxMatrix<DataType>::getDimension() {
    return &this->dim;
}

template<typename DataType>
void MtxMatrix<DataType>::save(std::string path, std::string name) {
}

template<typename DataType>
bool MtxMatrix<DataType>::isEmpty() {
    return !this->Lx;
}

template<typename DataType>
std::list<DataType> *MtxMatrix<DataType>::getColumn(const int idx) {
    // computing the length of the column
    int columnLength = this->Lp[idx] - this->Lp[idx - 1];

    // creating a list of column data with the computed length of the given index
    auto *columnList = new std::list<DataType>[columnLength];

    // iterating over nonzero data of the given index column
    // saving them inside a list
    for (int i = this->Lp[idx - 1]; i < this->Lp[idx]; i++) {
        columnList->push_back(this->Lx[i]);
    }

    return columnList;
}

template<typename DataType>
DataType MtxMatrix<DataType>::getDataAt(int idx) {
    return this->Lx[idx];
}

template<typename DataType>
void MtxMatrix<DataType>::setDataAt(int idx, DataType value) {
    this->Lx[idx] = value;
}

template<typename DataType>
std::list<int> *MtxMatrix<DataType>::getNoneZeroRowIndices(const int idx) {
    // computing the length of the column
    int columnLength = this->Lp[idx] - this->Lp[idx - 1];

    // creating a list of column data with the computed length of the given index
    auto *rowIndicesList = new std::list<int>[columnLength];

    // iterating over nonzero data of the given index column
    // saving them inside a list
    for (int i = this->Lp[idx - 1]; i < this->Lp[idx]; i++) {
        rowIndicesList->push_back(this->Li[i]);
    }

    return rowIndicesList;
}

template<typename DataType>
DataType MtxMatrix<DataType>::operator[](int idx) {
    return this->Lx[idx];
}

template<typename DataType>
int *MtxMatrix<DataType>::getLp() {
    return this->Lp;
}

template<typename DataType>
int *MtxMatrix<DataType>::getLi() {
    return this->Li;
}

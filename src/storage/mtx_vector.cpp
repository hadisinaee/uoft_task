#include "mtx_vector.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

// reads data from the given file source path
template<typename DataType>
int MtxVector<DataType>::readDataFrom(std::string filePath) {
    // checks that the given path is valid
    if (filePath.empty()) {
        return 1;
    }

    // open the given file
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        return 2;
    }

    // creating a dimension for this vector
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
        this->dim.setNonZeros(this->dim.getRows());
    }

    // create the vector values
    // initializing Lx(value array), Lp(pointer array), Li(indices array)
    this->Lx = new DataType[this->dim.getNonZeros()];
    this->Lp = new int[this->dim.getColumns() + 1];
    this->Li = new int[this->dim.getNonZeros()];
    this->raw_data = new DataType[this->dim.getRows() + 1];

    this->Lp[0] = 0;
    this->Lp[1] = 0;

    int n = isDense ? 1 : 0;
    for (int l = 0, pn = 1; l < this->dim.getNonZeros(); l++) {
        if (isDense) {
            this->Li[l] = l + 1;
            fin >> this->Lx[l];
        } else {
            fin >> this->Li[l] >> n >> this->Lx[l];
        }

        // add to available set of indicies which are not zero
        availableIndices.insert(this->Lx[l]);
        this->raw_data[this->Li[l]] = this->Lx[l];

        if (n - pn == 0) { // if they are on the same column
            this->Lp[pn]++;
        } else {
            this->Lp[n] = this->Lp[pn] + 1;
            pn = n;
        }
    }

    fin.close();

    return 0;
}

template<typename DataType>
Dimension *MtxVector<DataType>::getDimension() {
    return &this->dim;
}

template<typename DataType>
int MtxVector<DataType>::save(std::string outputPath, std::string name) {
    // creating an output stream
    std::ofstream fout;
    std::string finalFilePath;

    // formating the output path correctly
    std::string backSlashString = "/";
    if (outputPath.size() >= backSlashString.size() &&
        outputPath.compare(outputPath.size() - backSlashString.size(),
                           backSlashString.size(), backSlashString) == 0)
        finalFilePath += name;
    else
        finalFilePath += ("/" + name);

    // counting number of none_zeros in the final answer
    int nz = 0;
    for (int i = 0; i < this->getDimension()->getRows(); i++) {
        if (this->raw_data[i] != 0)
            nz++;
    }

    // stroing in the .mtx format
    fout.open(finalFilePath);

    fout << "% Vector Type \n";
    fout << this->getDimension()->getRows() << " "
         << this->getDimension()->getColumns() << " ";

    // if it is a dense vector, skip the nonzero part in the .mtx
    if (nz != this->getDimension()->getRows()) {
        fout << nz;
    }
    fout << "\n";

    // write the nonzero entries of the vector to the file
    for (int i = 0; i < this->getDimension()->getRows(); i++) {
        if (this->raw_data[i] != 0) {
            fout << i + 1 << " " << 1 << " " << this->raw_data[i] << std::endl;
        }
    }

    fout.close();
    return 0;
}

template<typename DataType>
bool MtxVector<DataType>::isEmpty() {
    return !this->Lx;
}

template<typename DataType>
std::list<int> *MtxVector<DataType>::getNoneZeroRowIndices(const int idx) {
    // computing the length of the column
    int columnLength = this->Lp[idx] - this->Lp[idx - 1];

    // creating a list of column data(from raw_data) with the length of columnLength
    auto *rowIndicesList = new std::list<int>[columnLength];

    // finding none zero indices using Li
    for (int i = this->Lp[idx - 1]; i < this->Lp[idx]; i++) {
        rowIndicesList->push_back(this->Li[i]);
    }

    return rowIndicesList;
}

// returns the i-th entry in the vector.
template<typename DataType>
DataType MtxVector<DataType>::getDataAt(int idx) {
    if (idx >= 0 && idx < this->dim.getNonZeros()) {
        return this->Lx[idx];
    } else {
        return 0.0;
    }
}

// sets a value at the i-th index of the vector
template<typename DataType>
int MtxVector<DataType>::setDataAt(int idx, DataType value) {
    // has to be in bound of Lx range
    if (idx >= 0 && idx < this->dim.getNonZeros())
        this->Lx[idx] = value;
    else
        return 1;
    return 0;

}

// returns i-th element of Lx not the whole vector
template<typename DataType>
DataType MtxVector<DataType>::operator[](int idx) {
    return this->Lx[idx];
}

template<typename DataType>
std::list<DataType> *MtxVector<DataType>::getColumn(const int idx) {
    // doesn't apply for vectors
    return NULL;
}

template<typename DataType>
int *MtxVector<DataType>::getLp() {
    return this->Lp;
}

template<typename DataType>
int *MtxVector<DataType>::getLi() {
    return this->Li;
}

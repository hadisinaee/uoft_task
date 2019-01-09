template <class T>
class MtxMatrix {
private:
  int M; // number of rows
  int N; // number of columns
  int L; // number of nonzeros
  T* data; // nonzero values from the matrix
  int* col; // indices associated with the first entry of each column
  int* row; // indices associated with the row of nonzero

public:
  // getters
  int getM();
  int getN();
  int getL();
  int* getColArr();
  int* getRowArr();
  T getDataAt(int);

  // setters
  void setDataAt(int, T);

  // reads a file
  void readMtxData(std::string);
};

template <class T> class MtxMatrix {
private:
  int M;  // number of rows
  int N;  // number of columns
  int NZ; // number of nonzeros

  T *Lx;   // row values; nonzero values from the matrix
  int *Lp; // coloumn pointer; indices associated with the first entry in column
  int *Li; // row index; indices associated with the row of nonzero

public:
  // reads a file of .mtx
  void readMtxData(std::string);

  // checks for emptiness of Lx
  bool isEmpty();

  // getter(s)
  int getM();
  int getN();
  int getNZ();
  int *getLp();
  int *getLi();
  int *getLx();
  T getDataAt(int);

  // setter(s)
  void setDataAt(int, T);
};

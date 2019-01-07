// TODO: add a template for value of vector/matrix
class MtxVector {
private:
  int M; // number of rows
  long double* data; // matrix data

public:
  // takes (M) and creates a filled matrix with the given thrid arg
  MtxVector (int, double);
  // takes (M) and creates a filled matrix with 0s
  MtxVector (int);

  // getter(s)
  int getM();
  double getDataAt(int);

  // setter(s)
  void setDataAt(int, long double);
};

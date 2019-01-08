// TODO: add a template for value of vector/matrix
class MtxVector {
private:
  int M; // number of rows
  long double* data; // matrix data

public:
  // getter(s)
  int getM();
  double getDataAt(int);

  // setter(s)
  void setDataAt(int, long double);
  void readMtxData(std::string);
};

// TODO: add a template for value of vector/matrix
template <class T>
class MtxVector {
private:
  int M; // number of rows
  T* data; // matrix data

public:
  // getter(s)
  int getM();
  T getDataAt(int);

  // setter(s)
  void setDataAt(int, T);
  void readMtxData(std::string);
};

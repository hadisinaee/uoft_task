template <class T> class MtxVector {
private:
  int length; // number of rows, i.e length of the array
  T *data;    // matrix data

public:
  // read file from .mtx
  void readMtxData(std::string);
  // checks for emptiness of the vector
  bool isEmpty();
  // overloading [] oberator for accessing data
  T operator[](int);

  // getter(s)
  int getLength();
  T getDataAt(int);

  // setter(s)
  void setDataAt(int, T);
};

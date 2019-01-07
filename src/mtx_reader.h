#include <iostream>

const int LONG_BUFFER=2048;

template <class T>
class MtxReader {
public:
  // .mtx file path reader
  std::string filePath;

  // reads .mtx file from the given path
  T readMtxData(std::string, bool);
};

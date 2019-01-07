#include "iostream"
#include "fstream"
#include "algorithm"
#include "stdio.h"

#include "mtx_reader.h"


const std::string nl="\n";

template <class T>
T MtxReader<T>::readMtxData(std::string filePath, bool isMatrix) {
  int M, N, L;

  std::cout << "[READ]> "
            << filePath
            << " isVector=" << isMatrix
            << nl;

  // open the file
  std::ifstream fin(filePath);

  // ignore headers and comments
  while (fin.peek() == '%') fin.ignore(LONG_BUFFER, '\n');

  fin >> M >> N;

  if(isMatrix) {
    // read nonzeros
    fin >> L;
    return T(M, N);
  } else {
    T mv = T(M);

    long double input = 0;
    int idx = 0;
    while (fin >> input) {
      mv.setDataAt(idx, input);
      idx++;
    }

    return mv;
  }

}

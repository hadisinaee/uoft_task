class MtxMatrix {
public:
  int M; // number of rows
  int N; // number of columns
  int L; // number of nonzeros
  double* data; // matrix data

  // takes (M, N) and creates a filled matrix with 0s
  MtxMatrix (int,int);

  // takes (M, N) and creates a filled matrix with the given thrid arg
  MtxMatrix (int, int, double);
};

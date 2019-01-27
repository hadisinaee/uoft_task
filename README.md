# Project Structure
- **include**: contains all required headers.
- **src**: contains all implementations of classes (`.cpp`):
  - **solver**: this folder contains files and classes that are responsible for solving equations. It has an abstract class named `base_solver` which implemented by two types of solvers, `simple_solver` and `sparse_solver`. New solvers can be added to this folder and implement the `base_solver`.
  - **storage**: this folder contains files and classes that are responsible for storing data and reading them. It has an abstract class named `base_storage_format`. Another abstract class derived from `base_storage_format` named `csc_storage_format`, representing CSC storage format, which implemented by two other classes, `mtx_matrix` and `mtx_vector`. New storage formats can be added to this folder and implement the `base_storage_format` or available ones such as `csc_storage_format`.
  - **utils**: contains utility classes which are needed by other classes. In this case, it has a `dfs` for traversing a graph.
- **tests**: all tests of these project will go here.
  - **lib**: contains `googletest` framework sources.
  - **data**: all test data required for testing.
  - **solver_tests**: tests for different algorithms.

# Algorithms
In this section, different algorithms are described for `Lx=b` where `L` is a `n x n` lower triangular matrix.

### Simple Algorithm
This algorithm basically is iterating over none-zero elements of matrix `L` and computes the final answers.

### Sparse Algorithm
In this algorithm, a graph of `G=(V,E)`, where `V={1,2,3,...,n}` and `E={(i, j) | Lji != 0`, is created. 
Then, a `DFS` is run starting from none-zero elements of `b`. The resulting set is named reach-set of `b`.
Finally, the solver algorithm is run for vertices inside this reach-set instead of all none-zero elements of `L`.
  
### Parallel Sparse Algorithm
In order to make the sparse algorithm parallel, the nodes are grouped into levels. 
Their levels are computed based on `wavefront` algorithm which defines a depth for each node
base on the following formula:  
```
depth(i) = 1 + max_j{depth(j), where L(i,j) != 0}
```
In this approach, first the reach-set of `b` is computed and then the `wavefront` algorithm executed.
All nodes inside each level can be run in parallel.

# Install and Build

### tests
In order to run the tests, the [googletest framework](https://github.com/google/googletest) needed to be installed.

### cli
List of available switches
``` 
	-v vector_file_path, e.g: -v ./b.mtx
	-m matrix_file_path, e.g: -m ./L.mtx
	-o output_directory_path, e.g: -o ./
	-a algorithm_type[simple, sparse, par_sparse], e.g: -a par_sparse
```

### demo

[![asciicast](https://asciinema.org/a/223712.svg)](https://asciinema.org/a/223712)

# TODO

- [x] add a `CMakeLists` file.
- [x] add support for testing.
    - [x] add the `googletest` framework.
    - [x] write tests for utils classes.
    - [x] write tests for storage classes.
        - [x] add tests for dense `mtx_vector`
        - [x] add tests for dense `mtx_matrix`
        - [x] add tests for sparse `mtx_vector`
        - [x] add tests for sparse `mtx_matrix`
    - [x] write tests for solver classes.
        - [x] write tests for `simple_solver`
        - [x] write tests for `sparse_solver`
        - [x] write tests for `parallel sparse_solver`
- [x] update readme with algorithms descriptions.
- [x] add more solvers with support of parallelism.
    - [x] wavefront based parallelism.
- [ ] try to setup `Travis CI` with this repo.
- [ ] add a test coverage tool.

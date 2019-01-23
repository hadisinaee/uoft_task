# Project Structure

- **src**: this folder contains all the files of this project.
  - **solver**: this folder contains files and classes that are responsible for solving equations. It has an abstract class named `base_solver` which implemented by two types of solvers, `simple_solver` and `sparse_solver`. New solvers can be added to this folder and implement the `base_solver`.
  - **storage**: this folder contains files and classes that are responsible for storing data and reading them. It has an abstract class named `base_storage_format`. Another abstract class derived from `base_storage_format` named `csc_storage_format`, representing CSC storage format, which implemented by two other classes, `mtx_matrix` and `mtx_vector`. New storage formats can be added to this folder and implement the `base_storage_format` or available ones such as `csc_storage_format`.
  - **utils**: contains utility classes which are needed by other classes. In this case, it has a `dfs` for traversing a graph.
- **tests**: all tests of these project will go here.

# CLI
List of available switches
``` 
	-v vector_file_path, e.g: -v ./b.mtx
	-m matrix_file_path, e.g: -m ./L.mtx
	-o output_directory_path, e.g: -o ./
	-a algorithm_type[simple, sparse, par_sparse], e.g: -a par_sparse
```
# TODO

- [x] add a `CMakeLists` file.
- [ ] add support for testing.
    - [x] add googletest framework.
    - [x] write tests for utils classes.
    - [ ] write tests for storage classes.
        - [x] add tests for dense `mtx_vector`
        - [x] add tests for dense `mtx_matrix`
        - [ ] add tests for sparse `mtx_vector`
        - [ ] add tests for sparse `mtx_matrix`
    - [ ] write tests for solver classes.
- [ ] update readme with algorithms descriptions.
- [x] add more solvers with support of parallelism.
    - [x] wavefront based parallelism.
- [ ] try to setup Travis CI with this repo.

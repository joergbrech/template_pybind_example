# Experimental Code for C++ templates and pybind11

Some experimentation with pybind and templated C++ code. This code has been modified from pybind's [cmake example](https://github.com/pybind/cmake_example). 
In contrast to their example, a C++14 compatible compiler is required for this repo.

The idea is to figure out a clean general and reusable way of binding class template realizations using convenience functions, see [this stackoverflow question](https://stackoverflow.com/questions/64552878/how-can-i-automatically-bind-templated-member-functions-of-variadic-class-templa).

## Installation

Just clone this repository and pip install. Note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive https://github.com/pybind/cmake_example.git
pip install ./cmake_example
```

With the `setup.py` file included in this example, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.

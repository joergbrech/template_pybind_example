cmake_minimum_required(VERSION 2.8.12)
project(template_example)

add_subdirectory(pybind11)
pybind11_add_module(template_example src/main.cpp)

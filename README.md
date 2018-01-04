 Status | |
 :--- | :---
Travis  | [![Build Status Travis](https://travis-ci.org/meshell/modern_cpp_project_template.png)](https://travis-ci.org/meshell/modern_cpp_project_template)
[![Coverage Status Coveralls](https://coveralls.io/repos/github/meshell/modern_cpp_project_template/badge.svg?branch=master)](https://coveralls.io/github/meshell/modern_cpp_project_template?branch=master)
[![Coverage Status codecov](https://codecov.io/gh/meshell/modern_cpp_project_template/branch/master/graph/badge.svg)](https://codecov.io/gh/meshell/modern_cpp_project_template)


Modern C++ project template
===========================

CMake based C++ project template for modern C++, i.e. C++11 and beyond

An example project which can be used as starting point for C++11/14/17 projects using cmake.
It includes:
* static code analysis integration with clang-tidy
* Source code documentation using [DoxyPress](http://www.copperspice.com/docs/doxypress/index.html)
* A Dummy unittest using the [Catch] (https://github.com/philsquared/Catch) testing framework
* A Dummy BDD Style (Gherkin) feature test using [Cucumber](http://cukes.info/) and [Cucumber-cpp] (https://github.com/cucumber/cucumber-cpp)
* CMake targets to build, run tests and measure metrics.


# Dependencies
---------------
Building the Project requires
* a recent Version of [CMake](http://www.cmake.org/) (3.6.x). See CMake documentation for more information about building using CMake.
* a recent C++ compiler supporting C++11

The external dependencies are downloaded and built.

# How to build
--------------

__Linux__
You can use cmake to configure and build.
E.g.
* mkdir build && (cd build && cmake ../src)
* cmake --build build --target all --config Debug

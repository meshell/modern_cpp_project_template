 Status | |
 :--- | :---
Travis  | [![Build Status Travis](https://travis-ci.org/meshell/modern_cpp_project_template.png)](https://travis-ci.org/meshell/modern_cpp_project_template)
AppVeyor  | [![Build status AppVeyor](https://ci.appveyor.com/api/projects/status/u0axo813um798dc7?svg=true)](https://ci.appveyor.com/project/meshell/modern_cpp_project_template)


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

__Windows__
You can use cmake to configure and build, you can also run the build.bat script to build the project and run the tests or run create_windows_installer.bat to create the installer exe.

Usage:
* build.bat [VS2013|VS2015] [--cmake_path <path_to_cmake>] [--config [Debug|Release]]
* create_windows_installer.bat [VS2015] [--cmake_path <path_to_cmake>] [--config [Debug|Release]]

# Known Issues
--------------

__Boost and MinGW__

There is bug in boost and building with MinGW will fail first. In order to build boost with MinGW a script executed when building boost modifies the generated project-config.jam (in the boost build folder) by replacing all occurrence of mingw with gcc, i.e. the script replaces
```
if ! mingw in [ feature.values <toolset> ]
{
    using mingw ;
}

project : default-build <toolset>mingw ;
```

with

```
if ! gcc in [ feature.values <toolset> ]
{
    using gcc ;
}

project : default-build <toolset>gcc ;
```
__Compile Error duplicate section__
When you build with MinGW you may have compile errors similar to the following:
```
C:/Work/Cpp_project_template/externals/lib/libboost_regex-mt-d.a(regex.o): duplicate section `.rdata$_ZTVN5boost16exception_detail10clone_implINS0_19error_info_injectorISt11logic_errorEEEE[__ZTVN5boost16exception_detail10clone_implINS0_19error_info_injectorISt11logic_errorEEEE]' has different size
C:/Work/Cpp_project_template/externals/lib/libboost_regex-mt-d.a(regex.o): duplicate section `.rdata$_ZTVN5boost16exception_detail10clone_implINS0_19error_info_injectorISt13runtime_errorEEEE[__ZTVN5boost16exception_detail10clone_implINS0_19error_info_injectorISt13runtime_errorEEEE]' has different size
C:/Work/Cpp_project_template/externals/lib/libboost_regex-mt-d.a(regex.o): duplicate section `.rdata$_ZTSN5boost16exception_detail10clone_implINS0_19error_info_injectorISt11logic_errorEEEE[__ZTSN5boost16exception_detail10clone_implINS0_19error_info_injectorISt11logic_errorEEEE]' has different size
C:/Work/Cpp_project_template/externals/lib/libboost_regex-mt-d.a(regex.o): duplicate section `.rdata$_ZTSN5boost16exception_detail19error_info_injectorISt11logic_errorEE[__ZTSN5boost16exception_detail19error_info_injectorISt11logic_errorEE]' has different size
C:/Work/Cpp_project_template/externals/lib/libboost_regex-mt-d.a(regex.o): duplicate section `.rdata$_ZTSN5boost16exception_detail10clone_implINS0_19error_info_injectorISt13runtime_errorEEEE[__ZTSN5boost16exception_detail10clone_implINS0_19error_info_injectorISt13runtime_errorEEEE]' has different size
C:/Work/Cpp_project_template/externals/lib/libboost_regex-mt-d.a(regex.o): duplicate section `.rdata$_ZTSN5boost16exception_detail19error_info_injectorISt13runtime_errorEE[__ZTSN5boost16exception_detail19error_info_injectorISt13runtime_errorEE]' has different size
```
I don't know a solution to this problem, it seems to be a compiler bug see [stackoverflow thread](http://stackoverflow.com/questions/14181351/i-got-duplicate-section-errors-when-compiling-boost-regex-with-size-optimizati)

# Running Unit tests / specification
------------------------
A cmake targets exists for each test framework to run the tests. And additionally the CTest target contains all tests from all unittests frameworks included.

# Running Feature tests
------------------------
A cmake target exists to run the feature tests (run_feature_test).
For more details on how to run cucumber feature tests see the Cucumber-cpp documentation.

# Sonar Metrics
----------------
In order to generate the code metrics and use sonar for publishing the metrics, [sonar-runner](http://docs.codehaus.org/display/SONAR/Installing+and+Configuring+Sonar+Runner), [cppcheck] (http://cppcheck.sourceforge.net/), [valgrind] (http://valgrind.org/) and [Rough Auditing Tool for Security (RATS)] (http://code.google.com/p/rough-auditing-tool-for-security/) are needed.
On the sonar server the [C++ Community Plugin](http://docs.codehaus.org/pages/viewpage.action?pageId=185073817) should be installed.

# C++ Project template library test cmake file

# required minimum version of cmake
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(TEST_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY}/tests)

file(MAKE_DIRECTORY
    ${TEST_RUNTIME_OUTPUT_DIRECTORY}
    )

# set report and documentation output paths
if(NOT REPORT_DIR)
    set(REPORT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../reports CACHE PATH "Reports directory")
endif(NOT REPORT_DIR)
if(NOT COVERAGE_REPORT_DIR)
    set(COVERAGE_REPORT_DIR ${REPORT_DIR}/coverage CACHE PATH "Coverage reports output directory")
endif(NOT COVERAGE_REPORT_DIR)
if(NOT TESTS_REPORT_DIR)
    set(TESTS_REPORT_DIR ${REPORT_DIR}/tests CACHE PATH "Testresult output directory")
endif(NOT TESTS_REPORT_DIR)

# create report and documentation output directories
file(MAKE_DIRECTORY
    ${REPORT_DIR}
    ${COVERAGE_REPORT_DIR}
    ${TESTS_REPORT_DIR}
    )

include(clang)

############
# CATCH Main
############
include(Catch)

add_library(catch_main OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_compile_features(catch_main
    PUBLIC
    cxx_noexcept
    )

target_include_directories(catch_main
    SYSTEM
    PUBLIC
    ${CATCH_INCLUDE_DIR}
    )
add_dependencies(catch_main catch)

#########################################################################
# Create test executables for every testclass (no coverage measurement) #
#########################################################################

function(register_catchtest TEST_FILE)
    get_filename_component(TEST_NAME ${TEST_FILE} NAME)
    message(STATUS "Adding Catch test " ${TEST_NAME})
    add_executable(${TEST_NAME}
        EXCLUDE_FROM_ALL
        ${TEST_FILE}.cpp
        $<TARGET_OBJECTS:catch_main>
        )

    target_include_directories(${TEST_NAME}
        SYSTEM
        PUBLIC
        ${CATCH_INCLUDE_DIR}
        )
    target_compile_options(${TEST_NAME}
        PRIVATE
        $<$<CONFIG:CMAKE_COMPILER_IS_CLANGCXX>:"-Wno-exit-time-destructors;">
        )

    target_link_libraries(${TEST_NAME}
        internal::project_lib ${ARGN}
        )

    # TODO uncomment if you would like each Test to show up in CTest as a test
    catch_add_tests(${TEST_NAME} "" ${TEST_FILE}.cpp)
    set(CATCHTEST_SOURCES ${CATCHTEST_SOURCES} ${TEST_FILE}.cpp PARENT_SCOPE)
endfunction()

# TODO add here all your tests (source file name without extension)
# The following tests are all the same tests but with different syntax, i.e
# - Classic Test
# - BDD Style Test
register_catchtest(src/dummy_test_catch)
register_catchtest(src/dummy_scenario_catch)

######################################
# Create a single test executable.   #
######################################

add_executable(unittests
    ${CATCHTEST_SOURCES}
    $<TARGET_OBJECTS:catch_main>
    )

add_executable(tests::unit ALIAS unittests)

set_target_properties(unittests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${TEST_RUNTIME_OUTPUT_DIRECTORY}"
    )

add_test(unittest unittests)

set_target_properties(unittests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${TEST_RUNTIME_OUTPUT_DIRECTORY}"
    )

target_include_directories(unittests
    SYSTEM
    PUBLIC
    ${CATCH_INCLUDE_DIR}
    )

target_compile_options(unittests
    PRIVATE
    $<$<CONFIG:CMAKE_COMPILER_IS_CLANGCXX>:"-Wno-exit-time-destructors;">
    )

target_link_libraries(unittests
    PUBLIC
    internal::project_lib
    )

if(CLANG_TIDY_EXE)
    set_target_properties(
        unittests
        PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_PROPERTIES}"
    )
endif()

add_dependencies(unittests catch)

# Target: run tests
add_custom_target(run_unittests
    ALL # run the test always for target all
    unittests --order rand
    )

add_dependencies(run_unittests
    tests::unit
    )

# Target: run tests with junit output
add_custom_target(run_unittests_junit
    unittests -r junit;-o ${TESTS_REPORT_DIR}/unit-tests.xml
    )

add_dependencies(run_unittests_junit
    tests::unit
    )
if(CMAKE_BUILD_TYPE MATCHES Debug)
    if(COVERAGE_XML)
        include(CodeCoverage)
        SETUP_TARGET_FOR_COVERAGE_COBERTURA(
            NAME coverage_unittests_xml
            EXECUTABLE unittests
            OUTPUTNAME ${COVERAGE_REPORT_DIR}/unittests
            DEPENDENCIES unittests
        )

        if(NOT TARGET coverage)
            add_custom_target(coverage)
        endif(NOT TARGET coverage)

        add_dependencies(coverage coverage_unittests_xml)
    endif(COVERAGE_XML)

    if(COVERAGE_HTML)
        SETUP_TARGET_FOR_COVERAGE(
            NAME coverage_unittests_html
            EXECUTABLE unittests
            OUTPUTNAME ${COVERAGE_REPORT_DIR}/unittests
            DEPENDENCIES unittests
        )
        if(NOT TARGET coverage)
            add_custom_target(coverage)
        endif(NOT TARGET coverage)
        add_dependencies(coverage coverage_unittests_html)
    endif(COVERAGE_HTML)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

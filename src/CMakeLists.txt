# C++ Project template top cmake file

# required minimum version of cmake
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

# project name
# TODO fill in your project name and version
project(modern_cpp_project_template VERSION 0.0.1 LANGUAGES CXX C)

option(COVERAGE_XML "Enable binary instrumentation to collect test coverage information in the DEBUG configuration (XML output)" TRUE)
option(COVERAGE_HTML "Enable binary instrumentation to collect test coverage information in the DEBUG configuration (HTML output)" FALSE)

# set default built type to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

# set the path to the additional cmake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

file(MAKE_DIRECTORY
    ${RUNTIME_OUTPUT_DIRECTORY}
    )

include(clang)

# Enable unit-testing.
enable_testing(true)


add_subdirectory(project_library)
add_subdirectory(app)


# add a target to generate API documentation with Doxygen
if(NOT DOC_DIR)
    set(DOC_DIR ${PROJECT_SOURCE_DIR}/../doc CACHE PATH "Documentation directory")
endif(NOT DOC_DIR)


file(MAKE_DIRECTORY
    ${DOC_DIR}
    )

# generate doxypress documentation
# TODO


# Add some custom target

# Targets for code anyalysis
# set report output paths
if(NOT REPORT_DIR)
    set(REPORT_DIR ${PROJECT_SOURCE_DIR}/../reports CACHE PATH "Reports directory")
endif(NOT REPORT_DIR)

# create report and documentation output directories
file(MAKE_DIRECTORY
    ${REPORT_DIR}
    )

find_program(CPPCHECK_EXE cppcheck)

if(CPPCHECK_EXE)
    message(STATUS "cppcheck found (${CPPCHECK_EXE}). Add target run_cppcheck")
    add_custom_target(run_cppcheck
        ${CPPCHECK_EXE} -I${PROJECT_SOURCE_DIR}/include --enable=style -f --std=c++11 -j2 --xml ${PROJECT_SOURCE_DIR}/project_library/ 2> ${REPORT_DIR}/cppcheck.xml
        COMMENT "Run cppcheck and output report to ${REPORT_DIR}/cppcheck.xml" VERBATIM
        )
endif(CPPCHECK_EXE)

find_program(RATS_EXE rats)

if(RATS_EXE)
    message(STATUS "rough-auditing-tool-for-security (RATS) found (${CPPCHECK_EXE}). Add target run_rats")
    add_custom_target(run_rats
        ${RATS_EXE} --quiet --xml ${PROJECT_SOURCE_DIR}/project_library/ > ${REPORT_DIR}/rats.xml
        COMMENT "Run cppcheck and output report to ${REPORT_DIR}/rats.xml" VERBATIM
        )
endif(RATS_EXE)

add_custom_target(clean-reports
    ${CMAKE_COMMAND} -E remove_directory ${REPORT_DIR}
    COMMENT "Delete all reports." VERBATIM
    )

# Packaging

install(FILES
    ${PROJECT_SOURCE_DIR}/../README.md
    ${PROJECT_SOURCE_DIR}/../LICENSE
    DESTINATION doc
    COMPONENT doc
    )

# project name used in doxygen docu
string(REGEX REPLACE "_" " " PROJECT_DOC_NAME ${PROJECT_NAME})

# project name used for installation
set(APPLICATION_NAME ${PROJECT_DOC_NAME})

include(CMakeInstallation.cmake)

add_custom_target(install_${PROJECT_NAME}
    $(MAKE) install
    DEPENDS ${PROJECT_NAME}
    COMMENT "Installing ${PROJECT_NAME}"
    )

add_custom_target(package_${PROJECT_NAME}
    $(MAKE) package
    DEPENDS ${PROJECT_NAME}
    COMMENT "Packaging ${PROJECT_NAME}"
    )

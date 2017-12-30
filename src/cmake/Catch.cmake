set(CATCH_VERSION "2.0.1" CACHE STRING "Define Catch-2 version")

function(catch_add_tests executable extra_args)
    if(NOT ARGN)
        message(FATAL_ERROR "Missing ARGN: Read the documentation for CATCH_ADD_TESTS")
    endif()
    foreach(source ${ARGN})
        file(READ "${source}" contents)
        string(REGEX MATCHALL "TEST_CASE *\\( *\"([ A-Za-z_0-9]+)\" *, *\"\\[[ A-Za-z_0-9]*\\]\" *\\)" found_tests ${contents})
        foreach(hit ${found_tests})
            string(REGEX REPLACE "TEST_CASE *\\( *\"([ A-Za-z_0-9]+)\".*" "\\1" test_name ${hit})
            string(REPLACE " " "_" test_name_underscore ${test_name})
            add_test(${test_name_underscore} ${executable} ${extra_args})
        endforeach()

        # Test alternative
        string(REGEX MATCHALL "SCENARIO *\\( *\"([ A-Za-z_0-9]+)\" *, *\"\\[[ A-Za-z_0-9]*\\]\" *\\)" found_tests ${contents})
        foreach(hit ${found_tests})
            string(REGEX REPLACE "SCENARIO *\\( *\"([ A-Za-z_0-9]+)\".*" "\\1" test_name ${hit})
            string(REPLACE " " "_" test_name_underscore ${test_name})
            add_test(${test_name_underscore} ${executable} ${extra_args})
        endforeach()
    endforeach()
endfunction()

include(ExternalProject)

ExternalProject_Add(catch
    URL https://github.com/catchorg/Catch2/archive/v${CATCH_VERSION}.tar.gz
    PREFIX ${CMAKE_BINARY_DIR}/catch2-v${CATCH_VERSION}
    TIMEOUT 10
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    )

# Expose required variable (CATCH_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(catch source_dir)
set(CATCH_INCLUDE_DIR ${source_dir}/single_include CACHE INTERNAL "Path to include folder for Catch")

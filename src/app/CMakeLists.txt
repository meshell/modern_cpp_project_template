# C++ Project template application cmake file

# required minimum version of cmake
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

if(NOT RUNTIME_OUTPUT_DIRECTORY)
    set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../bin)
    file(MAKE_DIRECTORY
        ${RUNTIME_OUTPUT_DIRECTORY}
        )
endif()

include(clang)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    )

add_executable(${PROJECT_NAME}::exe ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${RUNTIME_OUTPUT_DIRECTORY}"
    )

#
# with Boost
#

if(USE_STATIC_BOOST)
    set(Boost_USE_STATIC_LIBS ON)
else(USE_STATIC_BOOST)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        BOOST_ALL_DYN_LINK
        )
endif(USE_STATIC_BOOST)


set(Boost_Components program_options)
find_package(Boost COMPONENTS ${Boost_Components})

if(NOT Boost_FOUND)
    include(Boost)
endif(NOT Boost_FOUND)

target_include_directories(${PROJECT_NAME}
    SYSTEM
    PUBLIC
    ${Boost_INCLUDE_DIRS}
    )

target_link_libraries(${PROJECT_NAME}
    Boost::boost
    ${Boost_LIBRARIES}
    internal::project_lib
    )

if(CLANG_TIDY_EXE)
    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_PROPERTIES}"
    )
endif()

#Install targets

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    COMPONENT main
    )
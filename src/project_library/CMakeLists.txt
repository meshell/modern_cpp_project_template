# C++ Project template library cmake file

# required minimum version of cmake
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

include(clang)

# configure a header file to pass the version number to the source code
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/project_library_version.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/my_project/project_library_version.h"
)


# Build library
# TODO uncomment the EXCLUDE_FROM_ALL if your library is only used internally

add_library(project_lib STATIC
    #  EXCLUDE_FROM_ALL
    ""
    )

# define alias
add_library(internal::project_lib ALIAS project_lib)

# add source files
target_sources(project_lib
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp"
    )

target_include_directories(project_lib
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/my_project
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(project_lib
        PUBLIC
        -pedantic
        -Wall
        -Wextra
        PRIVATE
        -Werror
        -Wcast-align
        -Wcast-qual
        -Wctor-dtor-privacy
        -Wdisabled-optimization
        -Wformat=2
        -Winit-self
        -Wlogical-op
        -Wmissing-declarations
        -Wmissing-include-dirs
        -Wnoexcept
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wshadow
        -Wsign-conversion
        -Wsign-promo
        -Wstrict-null-sentinel
        -Wstrict-overflow=5
        -Wswitch-default
        -Wundef
        )
elseif(CMAKE_COMPILER_IS_CLANGCXX)
    target_compile_options(project_lib
        PUBLIC
        -Weverything
        -Wno-c++98-compat
        -Wno-padded
        PRIVATE
        -Werror
        )
endif(CMAKE_COMPILER_IS_GNUCXX)

target_compile_options(project_lib
    PUBLIC
    "$<$<BOOL:MSVC>:-D_WIN32_WINNT=0x0601>"
    "$<$<BOOL:UNIX>:-fPIC;>"
    )

target_compile_options(project_lib
    PUBLIC
    "$<$<BOOL:UNIX>:-fPIC>"
    )

set_target_properties(project_lib
    PROPERTIES
    LINK_FLAGS "$<$<BOOL:UNIX>:Xlinker '--no-as-needed'>"
    )

if(CLANG_TIDY_EXE)
    set_target_properties(
        project_lib
        PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_PROPERTIES}"
    )
endif()


# Define some common C++11/14/17 features
# TODO uncomment the C++11/14/17 features you use
target_compile_features(project_lib
    PUBLIC
    #    cxx_aggregate_default_initializers
    #    cxx_alias_templates
    #    cxx_alignas
    #    cxx_alignof
    #    cxx_attributes
    #    cxx_attribute_deprecated
    cxx_auto_type
    #    cxx_binary_literals
    cxx_constexpr
    #    cxx_contextual_conversions
    #    cxx_decltype_incomplete_return_types
    #    cxx_decltype
    #    cxx_decltype_auto
    #    cxx_default_function_template_args
    cxx_defaulted_functions
    cxx_defaulted_move_initializers
    cxx_delegating_constructors
    cxx_deleted_functions
    #    cxx_digit_separators
    #    cxx_enum_forward_declarations
    #    cxx_explicit_conversions
    #    cxx_extended_friend_declarations
    #    cxx_extern_templates
    cxx_final
    #    cxx_func_identifier
    #    cxx_generalized_initializers
    #    cxx_generic_lambdas
    #    cxx_inheriting_constructors
    #    cxx_inline_namespaces
    cxx_lambdas
    #    cxx_lambda_init_captures
    #    cxx_local_type_template_args
    #    cxx_long_long_type
    cxx_noexcept
    #    cxx_nonstatic_member_init
    cxx_nullptr
    cxx_override
    cxx_range_for
    cxx_raw_string_literals
    #    cxx_reference_qualified_functions
    #    cxx_relaxed_constexpr
    #    cxx_return_type_deduction
    #    cxx_right_angle_brackets
    cxx_rvalue_references
    #    cxx_sizeof_member
    cxx_static_assert
    #    cxx_strong_enums
    #    cxx_thread_local
    #    cxx_trailing_return_types
    #    cxx_unicode_literals
    #    cxx_uniform_initialization
    #    cxx_unrestricted_unions
    #    cxx_user_literals
    #    cxx_variable_templates
    #    cxx_variadic_macros
    #    cxx_variadic_templates
    #    cxx_template_template_parameters
    )

export(TARGETS project_lib NAMESPACE internal:: FILE ${CMAKE_CURRENT_SOURCE_DIR}/../project-lib_export.cmake)

add_subdirectory(tests)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    include(CodeCoverage)
    if(COVERAGE_XML OR COVERAGE_HTML)
        ENABLE_COVERAGE(project_lib)
    endif(COVERAGE_XML OR COVERAGE_HTML)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

#Install targets
install(TARGETS project_lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
    COMPONENT library
    )

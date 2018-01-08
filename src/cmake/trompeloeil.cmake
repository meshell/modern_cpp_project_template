set(TROMPELOEIL_VERSION "29" CACHE STRING "Define Catch-2 version")


include(ExternalProject)

ExternalProject_Add(trompeloeil
    URL https://github.com/rollbear/trompeloeil/archive/v${TROMPELOEIL_VERSION}.tar.gz
    PREFIX ${CMAKE_BINARY_DIR}/trompeloeil-v${TROMPELOEIL_VERSION}
    TIMEOUT 10
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    )

# Expose required variable (TROMPELOEIL_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(trompeloeil source_dir)
set(TROMPELOEIL_INCLUDE_DIR ${source_dir}/include CACHE INTERNAL "Path to include folder for trompeloeil")

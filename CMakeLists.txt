cmake_minimum_required(VERSION 3.0)
project(Gamma C)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

# We want to see messages about the percentage of build progress.
set_property(GLOBAL PROPERTY RULE_MESSAGES ON)

# We want to see the commands called by make.
set(CMAKE_VERBOSE_MAKEFILE ON)

# We set common compilation options for all project variants.
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra")
# Default options for Release and Debug variants make sense.
set (CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set (CMAKE_C_FLAGS_DEBUG "-g")

# We indicate source files.
set(SOURCE_FILES
        src/gamma.c
        src/gamma.h
        src/main.c
        src/ufind.c
        src/ufind.h
        src/safe_malloc.c
        src/safe_malloc.h
        src/parser.c
        src/parser.h
        src/handler.c
        src/handler.h
        src/ansi_escapes.c
        src/ansi_escapes.h
        src/ui.c
        src/ui.h
        )

# We indicate the executable file.
add_executable(gamma ${SOURCE_FILES})

# We add Doxygen support: check if it is installed:
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # We indicate the location of the configuration file and give its destination in the folder where
    # the compilation takes place.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    # We add the doc target: using make doc will call doxygen with the appropriate configuration file.
    # An appropriate comment will be written to the output.
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
    )
endif (DOXYGEN_FOUND)

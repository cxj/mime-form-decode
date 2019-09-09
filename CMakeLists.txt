# Very basic CMake project.
cmake_minimum_required(VERSION 2.8.4)

project(mime-form-decode)

# Undocumented settings to help prevent in-source builds.
# Don't want to contaminate source tree, nor accidentally overwrite files.
# However, this does not work reliably.  It's still possible to screw up. :-(
#set( CMAKE_DISABLE_SOURCE_CHANGES  ON )
#set( CMAKE_DISABLE_IN_SOURCE_BUILD  ON )

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(tests)

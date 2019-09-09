# Very basic CMake project.
cmake_minimum_required(VERSION 2.8.4)


include_directories(../include)

add_executable(try1 try1.cpp)
add_executable(try2 try2.cpp)

target_link_libraries(try1 mimedecode)
target_link_libraries(try2 mimedecode)

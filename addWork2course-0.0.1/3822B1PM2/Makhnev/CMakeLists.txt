cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME matrix)
project(${PROJECT_NAME} LANGUAGES CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

add_executable(speed_test "./samples/speedtest.cpp" 
"${INCLUDE_DIR}/tmatrix.h"
"${INCLUDE_DIR}/tdynamicvector.h"
"${INCLUDE_DIR}/tcompressedsparserow.h"
"${INCLUDE_DIR}/tvector.h"
"${INCLUDE_DIR}/tcoordinatelist.h")

add_executable(${PROJECT_NAME}_test "./test/test_main.cpp" 
"${TEST_DIR}/test_tmatrix.cpp" 
"${TEST_DIR}/test_tvector.cpp" 
"${TEST_DIR}/test_coordinatelist.cpp" 
"${TEST_DIR}/test_compressedsparserow.cpp" 
"${TEST_DIR}/test_vector.cpp"
"${INCLUDE_DIR}/tmatrix.h"
"${INCLUDE_DIR}/tdynamicvector.h"
"${INCLUDE_DIR}/tcompressedsparserow.h"
"${INCLUDE_DIR}/tvector.h"
"${INCLUDE_DIR}/tcoordinatelist.h")

set(TEST_NAME ${PROJECT_NAME}_test)
add_library(gtest "${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest-all.cc" "${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest.h")

target_link_libraries(${TEST_NAME} PUBLIC gtest)
target_include_directories(speed_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${TEST_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/gtest" "${CMAKE_CURRENT_SOURCE_DIR}/include")
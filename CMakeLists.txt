cmake_minimum_required(VERSION 3.10)
project(Test)

set(CMAKE_CXX_STANDARD 11)

add_executable(Test main.cpp cache/lru_cache.h cache/lru_cache.cpp  pool/struct_pool.h pool/struct_pool.cpp pool/constant.h pool/test.cpp pool/int_pool.h pool/int_pool.cpp)
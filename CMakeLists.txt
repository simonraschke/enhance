cmake_minimum_required(VERSION 3.2)
project(enhance VERSION 1.0.0 DESCRIPTION "c++ enhancements")
# include(GNUInstallDirs)
add_library(mylib INTERFACE)

target_include_directories(enhance INTERFACE enhance/)
target_compile_options(enhance PRIVATE -std=c++14 -O2 -g0)


enable_testing()
add_subdirectory(tests)
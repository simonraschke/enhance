cmake_minimum_required(VERSION 3.2)
project(enhance VERSION 1.0.0 DESCRIPTION "c++ enhancements")
# include(GNUInstallDirs)
add_library(enhance INTERFACE)

target_include_directories(enhance INTERFACE enhance/)
target_compile_options(enhance INTERFACE -std=c++17 -O2 -g0)

install(TARGETS enhance)

enable_testing()
add_subdirectory(tests)
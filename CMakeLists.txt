cmake_minimum_required( VERSION 3.28 FATAL_ERROR )

project( MDLValidator )

add_executable( mdl_validator "source/mdl-validator/main.cpp" )

target_include_directories(
    mdl_validator PRIVATE
    "include/"
)

set_target_properties(
    mdl_validator PROPERTIES
    CXX_STANDARD 20
)
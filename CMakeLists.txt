cmake_minimum_required(VERSION 3.10)
project(FlowShop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
    src/main.cpp
    src/problem.cpp
    src/solver.cpp
    src/utils.cpp
)

add_executable(main ${SOURCES})
cmake_minimum_required(VERSION 3.15)
project(KravsExecutor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Core library source files (excluding main.cpp)
file(GLOB CORE_SRC_FILES "src/*/*.cpp")

add_executable(kravs_executor src/main.cpp ${CORE_SRC_FILES})
add_executable(test_kravs_executor tests/test_kravs.cpp ${CORE_SRC_FILES})


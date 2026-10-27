cmake_minimum_required(VERSION 3.15)
project(KravsExecutor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# K-4: Platform and library dependency configuration
if(WIN32)
    message(STATUS "Configuring KravsExecutor for Windows target with Win32 API support.")
else()
    message(STATUS "Configuring KravsExecutor for cross-platform chroot build (simulation/stubs enabled).")
endif()

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Core library source files (excluding main.cpp)
file(GLOB CORE_SRC_FILES "src/*/*.cpp")

add_executable(kravs_executor src/main.cpp ${CORE_SRC_FILES})
add_executable(test_kravs_executor tests/test_kravs.cpp ${CORE_SRC_FILES})

add_test(NAME KravsUnitAndNegativeTests COMMAND test_kravs_executor)

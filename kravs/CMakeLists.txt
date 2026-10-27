cmake_minimum_required(VERSION 3.15)
project(KravsExecutor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    message(STATUS "Configuring KravsExecutor for Windows target with Win32 API support.")
else()
    message(STATUS "Configuring KravsExecutor for cross-platform chroot build.")
endif()

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB CORE_SRC_FILES "src/*/*.cpp")

add_executable(kravs_executor src/main.cpp ${CORE_SRC_FILES})
add_executable(test_kravs_executor tests/test_kravs.cpp ${CORE_SRC_FILES})

# Restrict KRAVS_TEST_STUB strictly to test target as mandated
target_compile_definitions(test_kravs_executor PRIVATE KRAVS_TEST_STUB)

add_test(NAME TestLoaderPositiveAndNegative COMMAND test_kravs_executor LoaderTest WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME TestInjectorPositiveAndNegative COMMAND test_kravs_executor InjectorTest WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME TestHookManager COMMAND test_kravs_executor HookTest WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME TestEnvironment COMMAND test_kravs_executor EnvTest WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME TestApiBridgePositiveAndNegative COMMAND test_kravs_executor BridgeTest WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME TestSchedulerPositiveAndNegative COMMAND test_kravs_executor SchedulerTest WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME TestExecutionPositiveAndNegative COMMAND test_kravs_executor ExecutionTest WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME TestUIAndTelemetry COMMAND test_kravs_executor UITest WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

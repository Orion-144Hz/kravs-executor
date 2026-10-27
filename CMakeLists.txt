cmake_minimum_required(VERSION 3.15)
project(KravsRootProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add kravs subdirectory as requested by management
add_subdirectory(kravs)

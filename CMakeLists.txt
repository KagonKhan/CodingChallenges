cmake_minimum_required(VERSION 3.29)

cmake_policy(SET CMP0155 OLD)    # Disable modules support, this is broken with clang-tidy at the moment

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)     # Only set the cxx_standard if it is not set by someone else
endif()

set(CMAKE_CXX_EXTENSIONS OFF)




project(json LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(spdlog REQUIRED)

# add_executable (wc src/wc/wc.cpp)
add_executable (json src/json-parser/json.cpp)

target_link_libraries(json PUBLIC
    spdlog::spdlog
)

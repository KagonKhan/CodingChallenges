cmake_minimum_required(VERSION 3.26)

project(json LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(spdlog REQUIRED)

# add_executable (wc CodingChallenges/wc/wc.cpp)
add_executable (json CodingChallenges/json-parser/json.cpp)

target_include_directories(json 
    PUBLIC spdlog::spdlog
)


target_compile_options(json PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_include_directories(json PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(json PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

option(ENABLE_SANITIZERS "Enable address & undefined sanitizers" ON)

if(ENABLE_SANITIZERS AND NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
endif()

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=modernize-*")

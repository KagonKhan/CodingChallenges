cmake_minimum_required(VERSION 3.26)

project(wc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable (wc CodingChallenges/wc/wc.cpp)

target_compile_options(wc PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_include_directories(wc PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(wc PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

option(ENABLE_SANITIZERS "Enable address & undefined sanitizers" ON)

if(ENABLE_SANITIZERS AND NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
endif()

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=modernize-*")

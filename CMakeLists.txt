cmake_minimum_required(VERSION 3.5)

project(HelloThrift)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(intro hello.cpp)
add_executable(server server/HelloServer.cpp)

target_compile_features(intro PRIVATE cxx_lambda_init_captures)
target_compile_features(server PRIVATE cxx_lambda_init_captures)

cmake_minimum_required(VERSION 3.10)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)
#这里GLAD_INCLUDE目录填你自己存放的路径
set(GLAD_INCLUDE /Users/fijiisland/Documents/Dependencies/glad/include)

find_package(glfw3 REQUIRED)

include_directories(${GLAD_INCLUDE})

add_executable(OpenGL main.cpp glad.c)

target_link_libraries(OpenGL glfw)
cmake_minimum_required(VERSION 3.10)

project(Project03)

include_directories(${CMAKE_SOURCE_DIR}/Librerias/include include)

file(GLOB SOURCES "src/*.c" "src/*.cpp" "include/*.h" "include/*.hpp")
add_executable(Project03 ${SOURCES})

target_link_libraries(Project03 ${CMAKE_SOURCE_DIR}/Librerias/lib/glfw3.lib)
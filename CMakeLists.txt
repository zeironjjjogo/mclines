cmake_minimum_required(VERSION 3.20)

project(mclines LANGUAGES CXX)

find_package(OpenCV REQUIRED)

add_executable(MCLs ./src/main.cpp ./src/diag.cpp ./src/drawer.cpp)
target_compile_features(MCLs PUBLIC cxx_std_20)
target_include_directories(MCLs PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(MCLs ${OpenCV_LIBS})

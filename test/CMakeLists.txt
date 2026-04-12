cmake_minimum_required(VERSION 3.14)
project(mclines_test)

find_package(GTest CONFIG REQUIRED)
add_executable(${PROJECT_NAME} test.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../src/diag.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include/")
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
enable_testing()

cmake_minimum_required(VERSION 3.4)

project(Vector3D)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)

IF (NOT TARGET gtest)
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(libs/googletest)
ENDIF()

#find_package(Qt5Core)

#add_executable(${PROJECT_NAME} "main.cpp")

#target_link_libraries(${PROJECT_NAME} Qt5::Core)
#target_link_libraries(${TEST_NAME} gtest gtest_main ${PROJECT_NAME})

set(TEST_NAME ${PROJECT_NAME}_UnitTest)
add_library(${PROJECT_NAME} STATIC
    vector3d.h
    vector3d.cpp)
add_executable(${TEST_NAME} vector3d_unittests.cpp)
target_link_libraries(${TEST_NAME} gtest gtest_main ${PROJECT_NAME})

cmake_minimum_required(VERSION 3.0.0)

# c++20
set(CMAKE_CXX_STANDARD 20)

project(exelogbook VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(exelogbook main.cpp)

# Add header files (.h) in include folder to the project
include_directories(include)

find_package(SQLite3 REQUIRED)
find_package(ImGui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})
include_directories(${ImGui_INCLUDE_DIRS})
include_directories(${glfw3_INCLUDE_DIRS})
include_directories(${glad_INCLUDE_DIRS})

target_link_libraries(
  exelogbook
  PRIVATE
    SQLite::SQLite3
    glfw
    glad::glad
    imgui::imgui
)

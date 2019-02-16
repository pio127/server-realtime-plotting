
cmake_minimum_required(VERSION 3.7)
project (plotting_TCP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PythonLibs 2.7)
find_package(nlohmann_json 3.2.0 REQUIRED)

include_directories(include ${PYTHON_INCLUDE_DIRS})

add_executable(server server.cpp)
add_executable(clientPlot clientPlot.cpp)

target_link_libraries(server ${PYTHON_LIBRARIES} nlohmann_json::nlohmann_json)
target_link_libraries(clientPlot ${PYTHON_LIBRARIES} nlohmann_json::nlohmann_json)

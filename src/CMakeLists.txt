cmake_minimum_required(VERSION 3.25)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp view/view.h view/view.cpp model/graph/graph.h model/graph/graph.cpp model/graph/algorithms.h model/graph/algorithms.cpp parallels.h parallels.cpp)

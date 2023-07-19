cmake_minimum_required(VERSION 3.25)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cc view/view.h view/view.cc model/graph/graph.h model/graph/graph.cc model/graph/ant_algorithms.h model/graph/ant_algorithms.cc parallels.h parallels.cc)

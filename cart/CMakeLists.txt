cmake_minimum_required (VERSION 3.0)
project (deeznescart)

file(GLOB DEEZNESCART_SRC src/*.cpp)

add_library(deeznescart ${DEEZNESCART_SRC})
target_include_directories(deeznescart PUBLIC
                           include)
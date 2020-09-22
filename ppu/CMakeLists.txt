cmake_minimum_required (VERSION 2.6)
project (deeznesppu)

file(GLOB DEEZNESPPU_SRC src/*.cpp)

add_library(deeznesppu ${DEEZNESPPU_SRC} ${DEEZNESPPU_HEADERS})
target_include_directories(deeznesppu PRIVATE
                           ${Boost_INCLUDE_DIRS})
target_include_directories(deeznesppu PUBLIC
                           include)
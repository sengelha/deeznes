cmake_minimum_required (VERSION 2.6)
project (deeznesio)

#file(GLOB DEEZNESIO_SRC src/*.cpp)

add_library(deeznesio INTERFACE)
target_include_directories(deeznesio INTERFACE
                           include)
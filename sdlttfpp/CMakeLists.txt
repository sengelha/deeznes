cmake_minimum_required (VERSION 2.6)
project (deeznessdlttfpp)

file(GLOB DEEZNESSDLTTFPP_SRC src/*.cpp)

add_library(deeznessdlttfpp ${DEEZNESSDLTTFPP_SRC})
target_include_directories(deeznessdlttfpp PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(deeznessdlttfpp PUBLIC include)
target_link_libraries(deeznessdlttfpp PRIVATE deeznessdlpp SDL2::SDL2_ttf)
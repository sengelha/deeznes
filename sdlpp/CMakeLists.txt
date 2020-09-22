cmake_minimum_required (VERSION 2.6)
project (deeznessdlpp)

file(GLOB DEEZNESSDLPP_SRC src/*.cpp)

add_library(deeznessdlpp ${DEEZNESSDLPP_SRC})
target_include_directories(deeznessdlpp PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(deeznessdlpp PUBLIC include)
target_link_libraries(deeznessdlpp PRIVATE SDL2::SDL2)
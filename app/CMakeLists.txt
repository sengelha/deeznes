cmake_minimum_required (VERSION 2.6)
project (deeznesapp)

file(GLOB DEEZNESAPP_SRC src/*.cpp)

add_executable(deeznesapp ${DEEZNESAPP_SRC})
target_compile_features(deeznesapp PRIVATE cxx_std_17)
target_include_directories(deeznesapp PRIVATE
                           ${CMAKE_CURRENT_BINARY_DIR}
                           ${Boost_INCLUDE_DIRS})
target_link_libraries(deeznesapp
                      deeznesconsole
                      deeznescpu
                      deeznesppu
                      deeznessdlpp
                      deeznessdlttfpp
                      SDL2::SDL2main)
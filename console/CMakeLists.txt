cmake_minimum_required (VERSION 3.0)
project (deeznesconsole)

file(GLOB DEEZNESCONSOLE_SRC src/*.cpp)

add_library(deeznesconsole ${DEEZNESCONSOLE_SRC})
target_include_directories(deeznesconsole PRIVATE
                           ${Boost_INCLUDE_DIRS})
target_include_directories(deeznesconsole PUBLIC
                           include)
target_link_libraries(deeznesconsole
                      deeznescart
                      deeznescompat
                      deeznescpu
                      deeznesio
                      deeznesppu)
target_compile_features(deeznesconsole PRIVATE
                        cxx_std_17)
cmake_minimum_required (VERSION 2.6)
project (deeznescpu)

find_package(Boost 1.73.0 REQUIRED)

file(GLOB DEEZNESCPU_SRC src/*.cpp)

add_library(deeznescpu ${DEEZNESCPU_SRC})
target_compile_features(deeznescpu PRIVATE cxx_final)
target_include_directories(deeznescpu PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${Boost_INCLUDE_DIRS})
target_include_directories(deeznescpu PUBLIC
                           include)
target_link_libraries(deeznescpu
                      deeznescompat)
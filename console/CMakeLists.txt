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

include(GoogleTest)
file(GLOB CONSOLETEST_SRC test/*.cpp)
add_executable(consoletest ${CONSOLETEST_SRC})
target_link_libraries(consoletest PRIVATE deeznesconsole GTest::gtest)
target_compile_features(consoletest PRIVATE cxx_std_17)
gtest_discover_tests(consoletest)
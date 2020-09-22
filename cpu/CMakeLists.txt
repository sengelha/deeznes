cmake_minimum_required (VERSION 2.6)
project (deeznescpu)

file(GLOB CPU_SRC src/*.cpp)
add_library(deeznescpu ${CPU_SRC})
target_compile_features(deeznescpu PRIVATE cxx_final)
target_include_directories(deeznescpu PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${Boost_INCLUDE_DIRS})
target_include_directories(deeznescpu PUBLIC
                           include)
target_link_libraries(deeznescpu
                      deeznescompat)

include(GoogleTest)
file(GLOB CPUTEST_SRC test/*.cpp)
add_executable(cputest ${CPUTEST_SRC})
target_include_directories(cputest PRIVATE
                           ${Boost_INCLUDE_DIRS})
target_link_libraries(cputest PRIVATE deeznescpu GTest::gtest)
target_compile_features(cputest PRIVATE cxx_std_17)
gtest_discover_tests(cputest)
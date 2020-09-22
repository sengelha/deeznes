cmake_minimum_required (VERSION 2.6)
project (deeznesppu)

file(GLOB DEEZNESPPU_SRC src/*.cpp)

add_library(deeznesppu ${DEEZNESPPU_SRC} ${DEEZNESPPU_HEADERS})
target_include_directories(deeznesppu PRIVATE
                           ${Boost_INCLUDE_DIRS})
target_include_directories(deeznesppu PUBLIC
                           include)

include(GoogleTest)
file(GLOB PPUTEST_SRC test/*.cpp)
add_executable(pputest ${PPUTEST_SRC})
target_link_libraries(pputest PRIVATE deeznesppu GTest::gtest)
target_compile_features(pputest PRIVATE cxx_std_17)
gtest_discover_tests(pputest)
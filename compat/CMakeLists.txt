cmake_minimum_required (VERSION 2.6)
project (deeznescompat)

add_library(deeznescompat INTERFACE)
target_include_directories(deeznescompat INTERFACE
                           include)
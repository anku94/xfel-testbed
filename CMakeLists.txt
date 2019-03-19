cmake_minimum_required(VERSION 3.10)

project (pptb)

set(CMAKE_PREFIX_PATH /users/ankushj/lcls2/install/lib)

find_library(XTCDATA_LIB NAMES libxtc.so)

include_directories("/users/ankushj/lcls2/install/include")

add_executable(pptb
  src/main.cpp src/EventGenerator.cpp)

target_link_libraries(pptb "${XTCDATA_LIB}")

cmake_minimum_required(VERSION 3.10)

project (pptb)

set(CMAKE_PREFIX_PATH /users/ankushj/lcls2/install)

# find_library(XTCDATA_LIB NAMES libxtc)
# add_library(XTCDATALIB SHARED IMPORTED)

# include_directories("/users/ankushj/lcls2/install/include")
# link_directories("/users/ankushj/lcls2/install/lib")
find_package(libxtc REQUIRED)

add_executable(pptb
  src/main.cpp)

target_link_libraries(pptb "${XTCDATA_LIB}")

cmake_minimum_required(VERSION 3.27)
project("searchEngine" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")


#set(SOURCE_FILES src/main.cpp)
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
#add_executable(engineRun ${SOURCE_FILES})
add_subdirectory(src)
#target_link_libraries(engineRun src)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(tests)







cmake_minimum_required(VERSION 3.27)
project("SearchEngine" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

set(MY_INCLUDE_DIR
        ${CMAKE_SOURCE_DIR}/include
)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

#set(JSON_BuildTests OFF CACHE INTERNAL "")
#
#add_subdirectory(nlohmann_json)
#target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)





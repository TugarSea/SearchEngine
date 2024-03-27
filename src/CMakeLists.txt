project(engine)

set(Src
	"ConverterJSON.cpp"
	"SearchServer.cpp"
	"InvertedIndex.cpp"
	"main.cpp"
)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(engine ${Src})

#target_link_libraries(engine PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(engine PUBLIC ${MY_INCLUDE_DIR})
add_library(source STATIC 
	Shader.cpp	Shader.h
)

target_include_directories( source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} vendor )

add_subdirectory(vendor)

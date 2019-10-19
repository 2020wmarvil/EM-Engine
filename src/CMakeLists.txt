add_library(source STATIC 
	Temp.cpp
)

target_include_directories( source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} vendor )

add_subdirectory(vendor)

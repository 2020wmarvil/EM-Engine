add_library(source STATIC 
	Entity.cpp	Entity.h
	Shader.cpp	Shader.h
	SpriteLoader.h	SpriteData.h

	VertexArray.h	VertexArray.cpp VertexBufferLayout.h
	VertexBuffer.h	VertexBuffer.cpp
	IndexBuffer.h	IndexBuffer.cpp
)

target_include_directories( source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} vendor )

add_subdirectory(vendor)

add_library(source STATIC 
	Shader.cpp	Shader.h
	SpriteLoader.h	SpriteData.h
	Texture.cpp	Texture.h
	Camera.cpp	Camera.h

	VertexArray.h	VertexArray.cpp VertexBufferLayout.h
	VertexBuffer.h	VertexBuffer.cpp
	IndexBuffer.h	IndexBuffer.cpp

	Collider.h	Collider.cpp
	Entity.cpp	Entity.h
	Terrain.h
	Player.h
)

target_include_directories( source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} vendor )

add_subdirectory(vendor)

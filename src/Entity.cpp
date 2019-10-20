#include "Entity.h"

Entity::Entity(const SpriteData& data)
    : m_VBO(data.vertices.data(), data.vertices.size() * sizeof(float), GL_DYNAMIC_DRAW),
      m_IBO(data.indices.data(), data.indices.size() * sizeof(unsigned int), GL_DYNAMIC_DRAW) 
{
	VertexBufferLayout layout;
	layout.PushFloat(2);
	m_VAO.AddBuffer(m_VBO, layout);

}

Entity::~Entity() {}

void Entity::Bind() const {
    m_VAO.Bind();
    m_VBO.Bind();
    m_IBO.Bind();
}

void Entity::Unbind() const {
    m_VAO.Unbind();
    m_VBO.Unbind();
    m_IBO.Unbind();
}
#include "Entity.h"

Entity::Entity(const SpriteData& data)
    : m_VBO(data.m_vertices.data(), data.m_vertices.size() * sizeof(float), GL_DYNAMIC_DRAW),
      m_IBO(data.m_indices.data(), data.m_indices.size() * sizeof(unsigned int), GL_DYNAMIC_DRAW) 
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
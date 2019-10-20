#pragma once

#include "SpriteData.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Entity {
private:
    VertexArray m_VAO;
    VertexBuffer m_VBO;
    IndexBuffer m_IBO;

public: 
    Entity(const SpriteData& data);
    ~Entity();

    void Bind() const;
    void Unbind() const;
};
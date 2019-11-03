#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "SpriteData.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

class Entity {
private:
    VertexArray m_VAO;
    VertexBuffer m_VBO;
    IndexBuffer m_IBO;

    Texture m_Texture;
    unsigned char m_Sprite=12;
    unsigned char m_Rows=3;
    unsigned char m_Cols=8;
protected:
    glm::vec3 m_Pos;
    glm::vec3 m_Scale;
    float m_Angle;

    glm::vec3 m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    const glm::vec3 m_AxisOfRotation = glm::vec3(0.0f, 0.0f, 1.0f);
public: 
    Entity(const SpriteData& data, const std::string& texPath, int texRows, int texCols);
    Entity(const SpriteData& data, const std::string& texPath, int texRows, int texCols, 
            glm::vec3 position, float angle, glm::vec3 scale);
    ~Entity();

    void Bind(Shader& shader) const;
    void Unbind() const;

    glm::mat4 ComputeModel();
    void Draw(Shader& shader) const;
    void Update(float dt);

    void SetPosition(glm::vec3 position) { m_Pos = position; }
    void SetScale(glm::vec3 scale) { m_Scale = scale; }
    void SetAngle(float angle) { m_Angle = angle; }
    void SetSprite(unsigned int sprite) { m_Sprite = sprite; }

    glm::vec2 GetTexOffset() const;
    glm::vec3 GetPosition() const { return m_Pos; }

    inline unsigned int GetIBOSize() const { return m_IBO.GetSize(); }
};
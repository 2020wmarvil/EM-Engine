#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
    unsigned int m_Sprite=0, m_Rows, m_Cols;

    float m_Width, m_Height;
protected:
    glm::vec3 m_Pos;
    glm::vec3 m_Scale;
    float m_Angle;

    glm::vec3 m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    const glm::vec3 m_AxisOfRotation = glm::vec3(0.0f, 0.0f, 1.0f);
public: 
Entity(const std::vector<float>& vertices, float width, float height,
            const std::string& texPath, int texRows, int texCols, 
            glm::vec3 position, float angle, glm::vec3 scale);
    ~Entity();

    void Bind(Shader& shader) const;
    void Unbind() const;

    glm::mat4 ComputeModel() const;
    void Draw(Shader& shader, glm::mat4* vp) const;
    void Update(float dt);

    void SetPosition(glm::vec3 position) { m_Pos = position; }
    void SetScale(glm::vec3 scale) { m_Scale = scale; }
    void SetAngle(float angle) { m_Angle = angle; }
    void SetSprite(unsigned int sprite) { m_Sprite = sprite; }

    glm::vec2 GetTexOffset() const;
    glm::vec3 GetPosition() const { return m_Pos; }
    float GetX() const { return m_Pos.x; }
    float GetY() const { return m_Pos.y; }
    float GetWidth() const { return m_Width; }
    float GetHeight() const { return m_Height; }

    inline unsigned int GetIBOSize() const { return m_IBO.GetSize(); }
};
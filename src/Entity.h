#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <thread>
#include <chrono>
#include <mutex>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

class Entity {
private:
    VertexArray m_VAO;
    VertexBuffer* m_VBO;
    IndexBuffer* m_IBO;

    Texture m_Texture;
    unsigned int m_Sprite=0, m_Rows, m_Cols;
    float m_SpriteInterval = 0.250f, m_LastTime = 0.0f;

    glm::vec2 m_TopLeft, m_BottomRight;
    float m_Width, m_Height;

    std::thread* m_AnimationThread;
    std::mutex m_ThreadLock;

    bool m_Grounded = false;
protected:
    glm::vec3 m_Pos, m_PrevPos;
    float m_Angle;

    glm::vec3 m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    const glm::vec3 m_AxisOfRotation = glm::vec3(0.0f, 0.0f, 1.0f);
public: 
Entity( const std::string& texPath, int texRows, int texCols, glm::vec3 position, float angle);
    ~Entity();

    void Bind(Shader& shader) const;
    void Unbind() const;

    glm::mat4 ComputeModel() const;
    void Draw(Shader& shader, glm::mat4* vp) const;
    void Update(float dt);
    void UpdateAnimation(float dt);
    void UpdateBounds();

    void SetPosition(glm::vec3 position);
    void SetAngle(float angle);
    void SetSprite(unsigned int sprite) { m_Sprite = sprite; }
    void SetGrounded(bool grounded) { m_Grounded = grounded; }

    glm::vec2 GetTexOffset() const;
    glm::vec2 GetTopLeft() const { return m_TopLeft; }
    glm::vec2 GetBottomRight() const { return m_BottomRight; }
    glm::vec3 GetPosition() const { return m_Pos; }
    glm::vec3 GetPreviousPosition() const { return m_PrevPos; }
    float GetWidth() const { return m_Width; }
    float GetHeight() const { return m_Height; }
    unsigned int GetIBOSize() const { return m_IBO->GetSize(); }

    bool isPixelTransparent(int x, int y) const { return m_Texture.isTransparent(m_Sprite, x, y); }
};

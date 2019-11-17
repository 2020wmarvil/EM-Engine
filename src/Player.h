#pragma once

#include "Entity.h"

class Player : public Entity {
private:
    float m_BaseSpeed = 1.0f;
public:
    Player(const std::string& texPath, int texRows, int texCols, glm::vec3 position, float angle)
    : Entity(texPath, texRows, texCols, position, angle) {}

    void ScaleVelocityX(int scalar) { m_Velocity.x = m_BaseSpeed * scalar; }
    void ScaleVelocityY(int scalar) { m_Velocity.y = m_BaseSpeed * scalar; }
};
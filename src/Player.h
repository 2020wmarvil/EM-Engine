#pragma once

#include "Entity.h"

std::vector<float> playerVertices = {
    -8,  8, 0.0,   0.3333,  
     8,  8, 0.125, 0.3333,  
     8, -8, 0.125, 0.0,  
    -8, -8, 0.0,   0.0
};

class Player : public Entity {
private:
    float m_BaseSpeed = 1.0f;
public:
    Player(const std::string& texPath, int texRows, int texCols, glm::vec3 position, float angle)
    : Entity(playerVertices, 16, 16, texPath, texRows, texCols, position, angle) {}

    void ScaleVelocityX(int scalar) { m_Velocity.x = m_BaseSpeed * scalar; }
    void ScaleVelocityY(int scalar) { m_Velocity.y = m_BaseSpeed * scalar; }
};
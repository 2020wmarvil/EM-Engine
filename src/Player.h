#pragma once

#include "Entity.h"

std::vector<float> playerVertices = {
    -200,  200, 0.0,   0.3333,  
     200,  200, 0.125, 0.3333,  
     200, -200, 0.125, 0.0,  
    -200, -200, 0.0,   0.0
};

class Player : public Entity {
private:
    float m_BaseSpeed = 5.0f;
public:
    Player(const std::string& texPath, int texRows, int texCols,
        glm::vec3 position, float angle, glm::vec3 scale)
    : Entity(playerVertices, texPath, texRows, texCols, position, angle, scale) {}

    void ScaleVelocityX(int scalar) { m_Velocity.x = m_BaseSpeed * scalar; }
    void ScaleVelocityY(int scalar) { m_Velocity.y = m_BaseSpeed * scalar; }
};
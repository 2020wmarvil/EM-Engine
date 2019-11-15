#pragma once

#include "Entity.h"

std::vector<float> playerVertices = {
    -100,  100, 0.0,   0.3333,  
     100,  100, 0.125, 0.3333,  
     100, -100, 0.125, 0.0,  
    -100, -100, 0.0,   0.0
};

class Player : public Entity {
private:
    float m_BaseSpeed = 5.0f;
public:
    Player(const std::string& texPath, int texRows, int texCols,
        glm::vec3 position, float angle)
    : Entity(playerVertices, 200, 200, texPath, texRows, texCols, position, angle) {}

    void ScaleVelocityX(int scalar) { m_Velocity.x = m_BaseSpeed * scalar; }
    void ScaleVelocityY(int scalar) { m_Velocity.y = m_BaseSpeed * scalar; }
};
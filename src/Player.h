#pragma once

#include "Entity.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

class Player : public Entity {
private:
    float m_BaseSpeed = 5.0f;
public:
    Player(const SpriteData& data, const std::string& texPath, int texWidth, int texHeight,
        glm::vec3 position, float angle, glm::vec3 scale)
    : Entity(data, texPath, texWidth, texHeight, position, angle, scale) {}

    void ScaleVelocityX(int scalar) { m_Velocity.x = m_BaseSpeed * scalar; }
    void ScaleVelocityY(int scalar) { m_Velocity.y = m_BaseSpeed * scalar; }
};
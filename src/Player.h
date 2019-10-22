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
    Player(const SpriteData& data, glm::vec3 position, float angle, glm::vec3 scale)
    : Entity(data, position, angle, scale) {}

    void ScaleVelocityX(int scalar) { m_Velocity.x = m_BaseSpeed * scalar; }
    void ScaleVelocityY(int scalar) { m_Velocity.y = m_BaseSpeed * scalar; }
};
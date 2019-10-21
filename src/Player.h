#pragma once


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Entity.h"

class Player : public Entity {
private:
    float m_SpeedX;
    float m_SpeedY;
public:
    Player(const SpriteData& data, glm::vec3 position, float angle, glm::vec3 scale)
    : Entity(data, position, angle, scale), m_SpeedX(0.0f), m_SpeedY(0.0f) {}

    void SetSpeedX(int speed) { m_SpeedX = speed; }
    void SetSpeedY(int speed) { m_SpeedY = speed; }
};
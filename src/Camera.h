#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Entity.h"

class Camera {
private:
    const Entity *m_FocusedEntity;

    glm::vec2 m_CamOffset;

    const float m_CameraZ = 0.0f; 
public:
    Camera(const Entity *focused, int midX, int midY);
    ~Camera();

    void SetFocusedEntity(const Entity *entity) { m_FocusedEntity = entity; }

    glm::mat4 GetViewMatrix();
};
#include "Camera.h"


Camera::Camera(const Entity *focused, int midX, int midY)
    : m_FocusedEntity(focused), m_CamOffset(glm::vec2(midX, midY)) {}

Camera::~Camera() {}

glm::mat4 Camera::GetViewMatrix() {
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(
        m_CamOffset.x-m_FocusedEntity->GetPosition().x, 
        m_CamOffset.y-m_FocusedEntity->GetPosition().y, 
        m_CameraZ));
    
    return view;
}
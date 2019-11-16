#include "Camera.h"
#include <iostream>

const float TEX_TO_PIX = 10.0f; 

Camera::Camera(const Entity *focused, int midX, int midY)
    : m_FocusedEntity(focused), m_CamOffset(glm::vec2(midX, midY) / (TEX_TO_PIX * 2.0f)) {}

Camera::~Camera() {}

glm::mat4 Camera::GetViewMatrix() {
    glm::mat4 view = glm::scale(glm::mat4(1.0f), glm::vec3(TEX_TO_PIX));
    view = glm::translate(view, glm::vec3(
        m_CamOffset.x-m_FocusedEntity->GetPosition().x, 
        m_CamOffset.y-m_FocusedEntity->GetPosition().y, 
        m_CameraZ));
    
    return view;
}
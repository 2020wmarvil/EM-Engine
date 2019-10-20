#pragma once

#include "Entity.h"
#include "Shader.h"

class Renderer {
public:
    void Draw(const Entity& entity, const Shader& shader) const;
    void Clear() const;
};


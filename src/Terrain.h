
#pragma once

#include "Entity.h"

class Terrain : public Entity {
public:
    Terrain(const std::string& texPath, int texRows, int texCols, glm::vec3 position, float angle)
    : Entity(texPath, texRows, texCols, position, angle) {}
};
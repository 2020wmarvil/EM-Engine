
#pragma once

#include "Entity.h"

std::vector<float> terrainVertices = {
    -300,  30, 0.0, 1.0, 
     300,  30, 1.0, 1.0, 
     300, -30, 1.0, 0.0, 
    -300, -30, 0.0, 0.0 
};

class Terrain : public Entity {
public:
    Terrain(const std::string& texPath, int texRows, int texCols,
        glm::vec3 position, float angle, glm::vec3 scale)
    : Entity(terrainVertices, 600, 60, texPath, texRows, texCols, position, angle, scale) {}
};
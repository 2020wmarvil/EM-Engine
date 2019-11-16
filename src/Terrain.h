
#pragma once

#include "Entity.h"

std::vector<float> terrainVertices = {
    -25,  2, 0.0, 1.0, 
     25,  2, 1.0, 1.0, 
     25, -2, 1.0, 0.0, 
    -25, -2, 0.0, 0.0 
};

class Terrain : public Entity {
public:
    Terrain(const std::string& texPath, int texRows, int texCols, glm::vec3 position, float angle)
    : Entity(terrainVertices, 50, 4, texPath, texRows, texCols, position, angle) {}
};

#pragma once

#include "Entity.h"

std::vector<float> terrain_vertices = {
    -200,  200, 0.0,   0.3333,  
     200,  200, 0.125, 0.3333,  
     200, -200, 0.125, 0.0,  
    -200, -200, 0.0,   0.0
};

class Terrain : public Entity {
public:
    Terrain(const std::string& texPath, int texRows, int texCols,
        glm::vec3 position, float angle, glm::vec3 scale)
    : Entity(terrain_vertices, texPath, texRows, texCols, position, angle, scale) {}
};
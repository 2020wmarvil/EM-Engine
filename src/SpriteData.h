#pragma once

#include <vector>

class SpriteData {
private:
public:
    std::vector<float> vertices = {
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
    };

	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3
	};

    SpriteData() {}
    ~SpriteData() {}
};
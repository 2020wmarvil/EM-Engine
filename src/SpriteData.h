#pragma once

#include <vector>

class SpriteData {
private:
public:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;

    SpriteData(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
		m_vertices = vertices;
		m_indices = indices;
	}

    ~SpriteData() {}
};
#pragma once

#include "Entity.h"

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Collider {
private:
	glm::vec2 Collision(int x1,int y1, int w1,int h1, int x2,int y2, int w2, int h2) { //x and y are top left corner coordinates
		if(((y1>(y2-h2))&&((y1-h1)<y2))&&((x2<(x1+w1))&&(x1<(x2+w2)))) {
			return glm::vec2(((x2+(w2/2))-(x1+(w1/2))),((y2-(h2/2))-(y1-(h1/2))));
		}
		return glm::vec2(0);
	}
public:
	std::vector<const Entity*>* m_Entities;

	Collider(std::vector<const Entity*>* entities) {
		m_Entities = entities;
	}
	~Collider() {}

	std::vector<const Entity*> Collide(Entity* entity) {
		std::vector<const Entity*> collided;

		int count = 0;
		for (int i=0; i<m_Entities->size(); i++) {
			if ((*m_Entities)[i] == entity) { continue; }

			count++;
		} std::cout << count << std::endl;

		return collided;		
	}
};

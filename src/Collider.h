#pragma once

#include "Entity.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

class Collider {
private:
	int Collision(const Entity* e1, const Entity* e2) {
		glm::vec2 a1 = e1->GetTopLeft();
		glm::vec2 a2 = e1->GetBottomRight();
		glm::vec2 b1 = e2->GetTopLeft();
		glm::vec2 b2 = e2->GetBottomRight();

		if((b2.x < a1.x) || (a2.x < b1.x)) { return 0; }
		if((b2.y > a1.y) || (a2.y > b1.y)) { return 0; }

		int inter_x1 = a1.x > b1.x ? a1.x : b1.x;
		int inter_x2 = a2.x < b2.x ? a2.x : b2.x;

		int inter_y1 = a2.y > b2.y ? a2.y : b2.y;
		int inter_y2 = a1.y < b1.y ? a1.y : b1.y;

		return 1;
	}
public:
	std::vector<const Entity*>* m_Entities;

	Collider(std::vector<const Entity*>* entities) : m_Entities(entities) {}
	~Collider() {}

	std::vector<int> Collide(Entity* entity) {
		std::vector<int> collided;

		for (int i=0; i<m_Entities->size(); i++) {
			if ((*m_Entities)[i] == entity) continue;

			collided.push_back(Collision(entity, (*m_Entities)[i]));
		} return collided;		
	}
};

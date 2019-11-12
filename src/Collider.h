#pragma once

#include "Entity.h"

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Collider {
private:
	int Collision(const Entity* e1, const Entity* e2) {
		int ax = e1->GetX() - e1->GetWidth() / 2;
		int ay = e1->GetY() + e1->GetHeight() / 2;
		int ax1 = e1->GetX() + e1->GetWidth() / 2;
		int ay1 = e1->GetY() - e1->GetHeight() / 2;

		int bx = e2->GetX() - e2->GetWidth() / 2;
		int by = e2->GetY() + e2->GetHeight() / 2;
		int bx1 = e2->GetX() + e2->GetWidth() / 2;
		int by1 = e2->GetY() - e2->GetHeight() / 2;

		if((bx1 < ax) || (ax1 < bx))
			return 0;
		if((by1 > ay) || (ay1 > by))
			return 0;

		int inter_x0 = ax > bx ? ax : bx;
		int inter_x1 = ax1 < bx1 ? ax1 : bx1;

		int inter_y0 = ay1 > by1 ? ay1 : by1;
		int inter_y1 = ay < by ? ay : by;

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

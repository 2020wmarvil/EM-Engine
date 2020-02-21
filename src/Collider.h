#pragma once

#include "Entity.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

class Collider {
private:
	int CollidePP(const Entity* e1, const Entity* e2) {
		glm::vec2 a1 = glm::vec2((int)e1->GetTopLeft().x, (int)e1->GetTopLeft().y);
		glm::vec2 a2 = glm::vec2((int)e1->GetBottomRight().x, (int)e1->GetBottomRight().y);
		glm::vec2 b1 = glm::vec2((int)e2->GetTopLeft().x, (int)e2->GetTopLeft().y);
		glm::vec2 b2 = glm::vec2((int)e2->GetBottomRight().x, (int)e2->GetBottomRight().y);

		if((b2.x < a1.x) || (a2.x < b1.x)) { return 0; }
		if((b2.y > a1.y) || (a2.y > b1.y)) { return 0; }

		int inter_x1 = a1.x > b1.x ? a1.x : b1.x;
		int inter_x2 = a2.x < b2.x ? a2.x : b2.x;

		int inter_y1 = a2.y > b2.y ? a2.y : b2.y;
		int inter_y2 = a1.y < b1.y ? a1.y : b1.y;

		for (int y=inter_y2; y>inter_y1; y--) {
			for (int x=inter_x1; x<inter_x2; x++) {
				if (!e1->isPixelTransparent(x - a1.x, e1->GetHeight() - (y - a2.y)) && 
					!e2->isPixelTransparent(x - b1.x, e2->GetHeight() - (y - b2.y))) {
					return 1;
				}
			}
		} return 0;
	}
	int CollideBB(const Entity* e1, const Entity* e2) {
		glm::vec2 a1 = glm::vec2((int)e1->GetTopLeft().x,     (int)e1->GetTopLeft().y);
		glm::vec2 a2 = glm::vec2((int)e1->GetBottomRight().x, (int)e1->GetBottomRight().y);
		glm::vec2 b1 = glm::vec2((int)e2->GetTopLeft().x,     (int)e2->GetTopLeft().y);
		glm::vec2 b2 = glm::vec2((int)e2->GetBottomRight().x, (int)e2->GetBottomRight().y);

		if((b2.x <= a1.x) || (a2.x <= b1.x)) { return 0; }
		if((b2.y >= a1.y) || (a2.y >= b1.y)) { return 0; }

		return 1;
	}
public:
	std::vector<const Entity*>* m_Entities;

	Collider(std::vector<const Entity*>* entities) : m_Entities(entities) {}
	~Collider() {}

	std::vector<int> CollideEntities(Entity* entity) {
		std::vector<int> collided;

		for (int i=0; i<m_Entities->size(); i++) {
			if ((*m_Entities)[i] == entity) continue;

			collided.push_back(CollidePP(entity, (*m_Entities)[i]));
		} return collided;		
	}

	void Resolve(Entity* e, std::vector<int>& collisions) {
		glm::vec3 cur= e->GetPosition();
		glm::vec3 prev = e->GetPreviousPosition();
		for (int i=0; i<collisions.size(); i++) {
			if (collisions[i] == 1) {
				 e->SetPosition(prev); return;

				float dx = (cur.x - prev.x) / 2.0f;
				float dy = (cur.y - prev.y) / 2.0f;

				glm::vec3 mid = glm::vec3(cur.x - dx, cur.y - dy, cur.z);
				
				cur = mid;

				while (dx > 1 && dy > 1) {
					dx = (cur.x - prev.x) / 2.0f;
					dy = (cur.y - prev.y) / 2.0f;

					mid = glm::vec3(cur.x - dx, cur.y - dy, cur.z);

					cur = mid;
				} e->SetPosition(mid);
			}
		}
	}
};

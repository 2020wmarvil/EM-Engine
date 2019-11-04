#pragma once

#include "Entity.h"

#include <vector>

class Collider {
private:
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

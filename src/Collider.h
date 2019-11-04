#pragma once

#include "Entity.h"

#include <vector>

class Collider {
private:
public:
	std::vector<const Entity*> m_Entities;

	Collider(std::vector<const Entity*>& entities) {
		m_Entities = entities;
	}
	~Collider() {}

	//std::vector<Entity> Collide(Entity entity) {
	//	std::vector<Entity> collided;

	//	return collided;		
	//}
};

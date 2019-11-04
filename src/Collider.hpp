#pragma once
#include <vector>
class Collider {
	private:
		std::vector<const Entity*> m_Entities;
	protected:

	public:
		Collider(const &std::vector<const Entity*> in) {
			m_Entities=in;
		}
		std::vector<const Entity*> collide(const &Entity in) {
			std::vector<const Entity*> out;
			
		}
};

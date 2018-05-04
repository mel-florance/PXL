
#include "particle.h"

 Particle::Particle(const glm::vec3 & position, const glm::vec3 & velocity, float gravity, float life, float rotation, float scale) {


}

bool Particle::update(double delta) {

	m_velocity.y += m_gravity * delta;
	glm::vec3 change = glm::vec3(m_velocity);
	change *= delta;
	m_position += change;
	m_elapsedTime += delta;

	return m_elapsedTime < m_life;
}

 Particle::~Particle() {


}


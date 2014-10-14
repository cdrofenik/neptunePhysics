#ifndef NEPTUNE_BALLISTIC_H
#define NEPTUNE_BALLISTIC_H

#include "particle.hpp"

namespace neptune
{
	class BallisticProjectile {

	public:
		enum ProjectileType
		{
			PISTOL,
			ARTILLERY,
			FIREBALL,
			LASER,
			UNUSED
		};

		ProjectileType projType;
		Particle particle;
		unsigned startTime;

		BallisticProjectile(ProjectileType type) : projType(type) {}

		void fire(unsigned lastFrameTimestamp);

		void update(float duration, unsigned lastFrameTimestamp);

		void render();
	};
}

#endif
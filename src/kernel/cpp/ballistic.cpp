#include "../h/ballistic.h"

namespace neptune
{
	void BallisticProjectile::fire(unsigned lastFrameTimestamp)
	{
		// Set the properties of the particle
		switch (projType)
		{
			case PISTOL:
				particle.setMass(2.0f); // 2.0kg
				particle.setVelocity(0.0f, 0.0f, 35.0f); // 35m/s
				particle.setAcceleration(0.0f, -1.0f, 0.0f);
				particle.setDamping(0.99f);
				break;

			case ARTILLERY:
				particle.setMass(200.0f); // 200.0kg
				particle.setVelocity(0.0f, 30.0f, 40.0f); // 50m/s
				particle.setAcceleration(0.0f, -20.0f, 0.0f);
				particle.setDamping(0.99f);
				break;

			case FIREBALL:
				particle.setMass(1.0f); // 1.0kg - mostly blast damage
				particle.setVelocity(0.0f, 0.0f, 10.0f); // 5m/s
				particle.setAcceleration(0.0f, 0.6f, 0.0f); // Floats up
				particle.setDamping(0.9f);
				break;

			case LASER:
				particle.setMass(0.1f); // 0.1kg - almost no weight
				particle.setVelocity(0.0f, 0.0f, 100.0f); // 100m/s
				particle.setAcceleration(0.0f, 0.0f, 0.0f); // No gravity
				particle.setDamping(0.99f);
				break;
		}

		// Set the data common to all particle types
		particle.setPosition(0.0f, 1.5f, 0.0f);
		startTime = lastFrameTimestamp;

		// Clear the force accumulators
		particle.clearAccumulator();
	}

	void BallisticProjectile::update(float duration, unsigned lastFrameTimestamp)
	{
		if (projType != UNUSED)
		{
			// Run the physics
			particle.integrate(duration);

			// Check if the particle is now invalid
			if (particle.getPosition().y < 0.0f || startTime + 5000 < lastFrameTimestamp ||
				particle.getPosition().z > 200.0f)
			{
				// We simply set the shot type to be unused, so the
				// memory it occupies can be reused by another shot.
				projType = UNUSED;
			}
		}
	}

	void BallisticProjectile::render()
	{

	}

}



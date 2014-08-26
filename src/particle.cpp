#include <math.h>
#include <assert.h>

#include "../include/precision.hpp"
#include "../include/particle.h"

namespace neptune
{
	void Particle::integrate(real duration)
	{
		if (inverseMass <= 0.0f) return;

		assert(duration > 0.0);

		position.addScaledVector(velocity, duration);

		Vector3 resultingAcc = acceleration;

		velocity.addScaledVector(resultingAcc, duration);

		velocity *= pow(damping, duration);

		clearAccumulator();
	}

	void Particle::clearAccumulator()
	{
		//TODO: Clear accumulator
	}

}



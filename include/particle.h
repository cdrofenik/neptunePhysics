#ifndef NEPTUNE_PARTICLE_H
#define NEPTUNE_PARTICLE_H

#include "core.h"

namespace neptune
{
	class Particle {

	protected:
		Vector3 position;	//position of the particle
		Vector3 velocity;	//velocity of the particle
		Vector3 acceleration;	//acceleration of the particle

		real damping;		//damping
		real inverseMass;	//inverse mass


	public:
		//! Integrates the values based on the duration given
		/*!
		Integrated the particle forward in time by the given amount.
		Uses Newton-Euler integration - linear approximation to the correct integral.
		*/
		void integrate(real duration);

		void clearAccumulator();

		//Getters
		Vector3 getPosition() const { return position; };
		Vector3 getVelocity() const { return velocity; };
		Vector3 getAcceleration() const { return acceleration; };

		real geDamping() const { return damping; };
		real getMass() const { return inverseMass*-1; };

		//Setters
		void setPosition(const Vector3& v) { position = v; };
		void setPosition(const real& x, const real& y, const real& z) { position.x = x; position.y = y; position.z = z; };

		void setVelocity(const Vector3& v) { velocity = v; };
		void setVelocity(const real& x, const real& y, const real& z) { velocity.x = x; velocity.y = y; velocity.z = z; };

		void setAcceleration(const Vector3& v) { acceleration = v; };
		void setAcceleration(const real& x, const real& y, const real& z) { acceleration.x = x; acceleration.y = y; acceleration.z = z; };

		void setDamping(const real& dampValue) { damping = dampValue; };
		void setMass(const real& mass) { inverseMass = -1 * mass; };

	};
}

#endif // NEPTUNE_PARTICLE_H
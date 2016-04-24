#ifndef NEPTUNE_NPPARTICLE_H
#define NEPTUNE_NPPARTICLE_H

#include "../math/npVector3.hpp"

namespace NeptunePhysics {

	class npParticle
	{
	public:
		npParticle(npVector3 pos, npVector3 velocity,
			npVector3 acc, npReal damp, npReal inMass) :
			m_position(pos),
			m_velocity(velocity),
			m_acceleration(acc),
			m_dampening(damp),
			m_inverseMass(inMass) {};
		
		~npParticle() {};

		void integrate(npReal duration);

		void addForce(const npVector3& force);
		void clearAccum();

	//private:
		npVector3 m_position;
		npVector3 m_velocity;
		npVector3 m_acceleration;

		npReal m_dampening;
		npReal m_inverseMass;

		npVector3 m_forceAccum;
	};
}

#endif
#ifndef NEPTUNE_NPPARTICLE_H
#define NEPTUNE_NPPARTICLE_H

#include "../math/npVector3.hpp"

namespace NeptunePhysics {

	class npParticle
	{
	public:
		npParticle(npVector3r pos, npVector3r velocity,
			npVector3r acc, npReal damp, npReal inMass) :
			m_position(pos),
			m_velocity(velocity),
			m_acceleration(acc),
			m_dampening(damp),
			m_inverseMass(inMass) {};
		
		~npParticle() {};

		void integrate(npReal duration);

		void addForce(const npVector3r& force);
		void clearAccum();

	//private:
		npVector3r m_position;
		npVector3r m_velocity;
		npVector3r m_acceleration;

		npReal m_dampening;
		npReal m_inverseMass;

		npVector3r m_forceAccum;
	};
}

#endif
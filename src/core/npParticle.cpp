#include "core\npParticle.h"

#include <assert.h>

namespace NeptunePhysics {

	void npParticle::integrate(npReal duration) {
		if (m_inverseMass <= 0.0f) return;

		assert(duration > 0.0f);

		//Update linear position
		m_position.addScaledVector(m_velocity, duration);

		//Update acceleration
		npVector3r resultingAcc = m_acceleration;
		resultingAcc.addScaledVector(m_forceAccum, duration);

		//Update velocity
		m_velocity.addScaledVector(resultingAcc, duration);

		//Impose drag
		m_velocity *= powf(m_dampening, duration);

		clearAccum();
	}

	void npParticle::addForce(const npVector3r &force) {
		m_forceAccum += force;
	}

	void npParticle::clearAccum() {
		m_forceAccum = npVector3r(0, 0, 0);
	}
}
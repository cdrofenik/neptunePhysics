#include "core/npForceGenerator.h"

#include <algorithm>

namespace NeptunePhysics {

	//----- npParticleGravity

	void npParticleGravity::updateForce(npParticle* particle, npReal duration)
	{
		if (particle->m_inverseMass == 0) return;

		npVector3r val = m_gravity * particle->m_inverseMass;

		particle->addForce(val);
	}

	//----- npParticleSpring

	void npParticleSpring::updateForce(npParticle* particle, npReal duration)
	{
		npVector3r force;
		force = particle->m_position;
		force -= m_other->m_position;


		npReal magnitude = force.length();
		magnitude = fabsf(magnitude - m_realLength);
		magnitude += m_springConstant;

		force.normalize();
		force *= -magnitude;
		particle->addForce(force);
	}

	//----- npParticleAnchoredSpring

	void npParticleAnchoredSpring::updateForce(npParticle* particle, npReal duration)
	{
		npVector3r force;
		force = particle->m_position;
		force -= m_anchor;


		npReal magnitude = force.length();
		magnitude = (m_restLength - magnitude) * m_springConstant;

		force.normalize();
		force *= magnitude;
		particle->addForce(force);
	}

	//----- npParticleBungee

	void npParticleBungee::updateForce(npParticle* particle, npReal duration)
	{
		npVector3r force;
		force = particle->m_position;
		force -= m_other->m_position;


		npReal magnitude = force.length();
		if (magnitude <= m_restLength) return;

		magnitude = m_springConstant * (m_restLength - magnitude);

		force.normalize();
		force *= -magnitude;
		particle->addForce(force);
	}

	//----- npParticleBouyancy

	void npParticleBouyancy::updateForce(npParticle* particle, npReal duration)
	{
		npReal depth = particle->m_position.y;

		if (depth >= m_waterHeight + m_maxDepth) return;

		npVector3r force;

		if (depth <= m_waterHeight - m_maxDepth)
		{
			force.y = m_liquidDensirt * m_volume;
			particle->addForce(force);
			return;
		}

		force.y = m_liquidDensirt * m_volume * (depth - m_maxDepth - m_waterHeight) / 2 * m_maxDepth;
		particle->addForce(force);
	}

	//----- npParticleForceRegistry

	void npParticleForceRegistry::add(npParticle* particle, npParticleForceGenerator * generator)
	{
		registration.push_back(npParticleForceRegistration(generator, particle));
	}

	void npParticleForceRegistry::clear()
	{
		registration.clear();
	}

	void npParticleForceRegistry::updateForces(npReal duration)
	{
		std::vector<npParticleForceRegistration>::iterator iter;
		for (iter = registration.begin(); iter != registration.end(); iter++) {
			iter->fg->updateForce(iter->particle, duration);
		}
	}

	npParticle* npParticleForceRegistry::getParticle(int _index)
	{
		std::vector<npParticleForceRegistration>::iterator iter;
		int counter = 0;
		for (iter = registration.begin(); iter != registration.end(); iter++) {
			if (counter == _index) {
				return iter->particle;
			}
			counter++;
		}
		return nullptr;
	}

	//----- npGravityForce
	void npGravityForce::updateForce(npRigidBody *_body, npReal duration)
	{
		if (_body->getInverseMass() == 0) return;

		npVector3r val = m_gravity * _body->getInverseMass();

		_body->addForce(val);
	}

	//----- npForceRegistry

	void npForceRegistry::add(npRigidBody* _rigidBody, npForceGenerator *_generator)
	{
		registration.push_back(npForceRegistration(_generator, _rigidBody));
	}

	void npForceRegistry::clear()
	{
		registration.clear();
	}

	void npForceRegistry::updateForces(npReal duration)
	{
		std::vector<npForceRegistration>::iterator iter;
		for (iter = registration.begin(); iter != registration.end(); iter++) {
			iter->fg->updateForce(iter->rigidBody, duration);
		}
	}

	npRigidBody* npForceRegistry::getRigidBody(int _index)
	{
		std::vector<npForceRegistration>::iterator iter;
		int counter = 0;
		for (iter = registration.begin(); iter != registration.end(); iter++) {
			if (counter == _index) {
				return iter->rigidBody;
			}
			counter++;
		}
		return nullptr;
	}

}
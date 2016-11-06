#include "collision/npParticleContact.h"

namespace NeptunePhysics {

	void npParticleContact::resolve(npReal duration)
	{
		resolveVelocity(duration);
		resolveInterpenetration(duration);
	}

	npReal npParticleContact::calculateSeparatingVelocity() const
	{
		npVector3 relativeVelocity = particle[0]->m_velocity;
		if (particle[1]) relativeVelocity -= particle[1]->m_velocity;
		return contactNormal * relativeVelocity;
	}

	void npParticleContact::resolveVelocity(npReal duration)
	{
		npReal separatingVelocity = calculateSeparatingVelocity();

		if (separatingVelocity > 0)
		{
			return;
		}

		npReal newSepVelocity = -separatingVelocity * restitution;

		npVector3 accCausedVelocity = particle[0]->m_acceleration;
		if (particle[1]) accCausedVelocity -= particle[1]->m_acceleration;
		npReal accCausedSepVelocity = accCausedVelocity * contactNormal * duration;
		if (accCausedSepVelocity < 0)
		{
			newSepVelocity += restitution * accCausedSepVelocity;
			if (newSepVelocity < 0) newSepVelocity = 0;
		}

		npReal deltaVelocity = newSepVelocity - separatingVelocity;

		npReal totalInverseMass = particle[0]->m_inverseMass;
		if (particle[1]) totalInverseMass += particle[1]->m_inverseMass;

		if (totalInverseMass <= 0) return;

		npReal impulse = deltaVelocity / totalInverseMass;

		npVector3 impulsePerMass = contactNormal * impulse;

		particle[0]->m_velocity = particle[0]->m_velocity + impulsePerMass * particle[0]->m_inverseMass;
		if (particle[1])
		{
			particle[1]->m_velocity = particle[1]->m_velocity + impulsePerMass * -particle[1]->m_inverseMass;
		}
	}

	void npParticleContact::resolveInterpenetration(npReal duration)
	{
		if (penetration <= 0) return;

		npReal totalInverseMass = particle[0]->m_inverseMass;
		if (particle[1]) totalInverseMass += particle[1]->m_inverseMass;

		if (totalInverseMass <= 0) return;

		npVector3 movePerIMass = contactNormal * (penetration / totalInverseMass);

		npVector3 particleMovement0 = movePerIMass *  particle[0]->m_inverseMass;
		npVector3 particleMovement1;
		if (particle[1])
		{
			npVector3 particleMovement1 = movePerIMass *  -particle[1]->m_inverseMass;
		}

		particle[0]->m_position = particle[0]->m_position + particleMovement0;
		if (particle[1])
		{
			particle[1]->m_position = particle[1]->m_position + particleMovement1;
		}
	}

}
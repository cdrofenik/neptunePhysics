#ifndef NEPTUNE_NPPARTICLECONTACT_H
#define NEPTUNE_NPPARTICLECONTACT_H

#include "core/npParticle.h"

namespace NeptunePhysics {

	class npParticleContact
	{
	public:
		npParticle* particle[2];
		npVector3r contactNormal;
		npReal restitution;
		npReal penetration;

		void resolve(npReal duration);
		npReal calculateSeparatingVelocity() const;		

	private:
		void resolveVelocity(npReal duration);
		void resolveInterpenetration(npReal duration);
	};
}

#endif
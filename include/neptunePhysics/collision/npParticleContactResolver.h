#ifndef NEPTUNE_NPPARTICLECONTACTRESOLVER
#define NEPTUNE_NPPARTICLECONTACTRESOLVER

#include "npParticleContact.h"

namespace NeptunePhysics {

	class npParticleContactResolver
	{

	public:
		npParticleContactResolver(unsigned iterations);

	protected:
		unsigned iterations;
		unsigned iterationsUsed;

	private:
		void setIterations(unsigned iterations);
		void resolveContacts(npParticleContact* contactArray,
			unsigned numContacts,
			npReal duration);
	};
}

#endif
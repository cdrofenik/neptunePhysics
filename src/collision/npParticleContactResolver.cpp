#include "collision/npParticleContactResolver.h"

namespace NeptunePhysics {

	npParticleContactResolver::npParticleContactResolver(unsigned _iterations)
	{
		iterations = _iterations;
	}

	void npParticleContactResolver::setIterations(unsigned _iterations)
	{
		iterations = _iterations;
	}

	void npParticleContactResolver::resolveContacts(npParticleContact* contactArray,
		unsigned numContacts,
		npReal duration)
	{
		unsigned i;

		iterationsUsed = 0;
		while (iterationsUsed < iterations)
		{
			npReal max = 99999;
			unsigned maxIndex = numContacts;
			for (i = 0; i < numContacts; i++)
			{
				npReal sepVel = contactArray[0].calculateSeparatingVelocity();
				if (sepVel < max && (sepVel < 0 || contactArray[0].penetration > 0))
				{
					max = sepVel;
					maxIndex = i;
				}
			}

			if (maxIndex == numContacts) break;

			contactArray[maxIndex].resolve(duration);
			iterationsUsed++;
		}

	}
}
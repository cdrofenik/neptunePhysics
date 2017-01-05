#ifndef NEPTUNE_NPCOLLISIONALGORITHM_H
#define NEPTUNE_NPCOLLISIONALGORITHM_H

#include "../npCollisionObject.h"

namespace NeptunePhysics {

	struct npCollisionInfo
	{
	public:
		npVector3r contactPoint;
		npVector3r contactNormal;
		npReal penetration;

		void setCollisionObjects(npCollisionObject* object0, npCollisionObject* object1) {
			obj0 = object0;
			obj1 = object1;
		}

	private:
		npCollisionObject* obj0;
		npCollisionObject* obj1;
	};

	class npCollisionAlgorithm
	{
	public:
		npCollisionAlgorithm();
		~npCollisionAlgorithm();

		static int processCollision(npCollisionObject* obj0, npCollisionObject* obj1, npCollisionInfo &_cInfo);
	};
}
#endif
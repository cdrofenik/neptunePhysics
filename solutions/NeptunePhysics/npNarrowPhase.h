#ifndef NEPTUNE_NPNARROWSEARCH_H
#define NEPTUNE_NPNARROWSEARCH_H

#include "npCollisionShape.h"

namespace NeptunePhysics {

	namespace NarrowPhase {
	
		void ClosestPtPointAABB(const npVector3& p, const npAABB& b, npVector3& q);

		int TestAABB_AABB(const npAABB& a, const npAABB& b);

		int TestSphere_AABB(const npSphere& b, const npAABB& a);

		int TestSphere_Sphere(const npSphere& a, const npSphere& b);
	}
}

#endif
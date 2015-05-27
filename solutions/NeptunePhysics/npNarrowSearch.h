#ifndef NEPTUNE_NPNARROWSEARCH_H
#define NEPTUNE_NPNARROWSEARCH_H

#include "npCollisionShape.h"

namespace neptunePhysics {

	namespace narrowSearch {
	
		int TestAABB_AABB(npAABB a, npAABB b);

		int TestAABB_Sphere(npAABB a, npSphere b);

		int TestShere_Sphere(npSphere a, npSphere b);

	}
}

#endif
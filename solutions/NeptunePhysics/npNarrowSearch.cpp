#include "npNarrowSearch.h"

namespace neptunePhysics {

	namespace narrowSearch {

		int TestAABB_AABB(npAABB& a, npAABB& b) {
			int r;
			r = a.halfX + b.halfX; if ((unsigned int)(a.c.x - b.c.x + r) > r + r) return 0;
			r = a.halfY + b.halfY; if ((unsigned int)(a.c.y - b.c.y + r) > r + r) return 0;
			r = a.halfZ + b.halfZ; if ((unsigned int)(a.c.z - b.c.z + r) > r + r) return 0;
			return 1;
		}

		int TestAABB_Sphere(npAABB a, npSphere b) {
			//implement
			return 1;
		}

		int TestSphere_Sphere(npSphere& a, npSphere& b) {
			npVector3 d = a.c - b.c;
			float dist2 = d * d;
			float radiusSum = a.r + b.r;
			return dist2 <= radiusSum * radiusSum;
		}

		//int TestOBB_OBB(npOBB& a, npOBB& b){
			//TODO
		//}
	}
}
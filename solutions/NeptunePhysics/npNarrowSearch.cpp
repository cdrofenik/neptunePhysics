#include "npNarrowSearch.h"

namespace neptunePhysics {

	namespace narrowSearch {

		void ClosestPtPointAABB(const npVector3& p, const npAABB& b, npVector3& q)
		{
			
		}

		int TestAABB_AABB(const npAABB& a, const npAABB& b) {
			if (abs(a.c.x - b.c.x) > abs(a.halfX + b.halfX)) return 0;
			if (abs(a.c.y - b.c.y) > abs(a.halfY + b.halfY)) return 0;
			if (abs(a.c.z - b.c.z) > abs(a.halfZ + b.halfZ)) return 0;
			return 1;
		}

		int TestSphere_AABB(const npSphere& s, const npAABB& a) {

			npVector3 p;
			//Closest point p on AABB that is closest to the sphere center
			ClosestPtPointAABB(s.c, a, p);

			npVector3 v = p - s.c;
			return (v * v) <= (s.r * s.r);
		}

		int TestSphere_Sphere(const npSphere& a, const npSphere& b) {
			/*npVector3 d = a.c - b.c;
			float dist2 = d * d;
			float radiusSum = a.r + b.r;*/
			return (a.c - b.c) * (a.c - b.c) <= (a.r) * (b.r);
		}
	}
}
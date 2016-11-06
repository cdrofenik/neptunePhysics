#include "collision\npNarrowPhase.h"

namespace NeptunePhysics {

	namespace NarrowPhase {

		//void ClosestPtPointAABB(const npVector3& p, const npAABB& b, npVector3& q)
		//{
		//	float v = p.x;
		//	if (v < (b.c.x - b.halfX)) v = fmaxf(v, b.c.x - b.halfX); // v = (b.c.x - b.halfX);
		//	if (v > (b.c.x + b.halfX)) v = fminf(v, b.c.x - b.halfX); // v = (b.c.x + b.halfX);
		//	q.x = v;

		//	v = p.y;
		//	if (v < (b.c.y - b.halfY)) v = fmaxf(v, b.c.y - b.halfY);
		//	if (v > (b.c.y + b.halfY)) v = fminf(v, b.c.y - b.halfY);
		//	q.y = v;

		//	v = p.z;
		//	if (v < (b.c.z - b.halfZ)) v = fmaxf(v, b.c.z - b.halfZ);
		//	if (v > (b.c.z + b.halfZ)) v = fminf(v, b.c.z - b.halfZ);
		//	q.z = v;
		//}

		//int TestAABB_AABB(const npAABB& a, const npAABB& b) {
		//	if (abs(a.c.x - b.c.x) > abs(a.halfX + b.halfX)) return 0;
		//	if (abs(a.c.y - b.c.y) > abs(a.halfY + b.halfY)) return 0;
		//	if (abs(a.c.z - b.c.z) > abs(a.halfZ + b.halfZ)) return 0;
		//	return 1;
		//}

		//int TestSphere_AABB(const npSphere& s, const npAABB& a) {

		//	npVector3 p;
		//	ClosestPtPointAABB(s.c, a, p); //Closest point p on AABB that is closest to the sphere center

		//	npVector3 v = p - s.c;
		//	return (v * v) <= (s.r * s.r);
		//}

		//int TestSphere_Sphere(const npSphere& a, const npSphere& b) {
		//	npVector3 d = a.c - b.c;
		//	float dist2 = d * d;
		//	float radiusSum = a.r + b.r;
		//	return dist2 <= (radiusSum * radiusSum);
		//}
	}
}
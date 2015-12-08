#include "gtest\gtest.h"

#include "../NeptunePhysics/npNarrowPhase.h"

using namespace NeptunePhysics;
using namespace NeptunePhysics::NarrowPhase;

TEST(npNarrowPhase, ClosestPtPointAABB) {

	npVector3<npReal> cntr(2, 2, 4);
	npAABB a1(cntr, 1.0f, 2.0f, 4.0f);

	npVector3<npReal> pnt(0, 3, 0);

	npVector3<npReal> res;
	ClosestPtPointAABB(pnt, a1, res);

	EXPECT_FLOAT_EQ(a1.c.x, 2.0f);
	EXPECT_FLOAT_EQ(a1.c.y, 2.0f);
	EXPECT_FLOAT_EQ(a1.c.z, 4.0f);
	EXPECT_FLOAT_EQ(a1.halfX, 1.0f);
	EXPECT_FLOAT_EQ(a1.halfY, 2.0f);
	EXPECT_FLOAT_EQ(a1.halfZ, 4.0f);

	EXPECT_FLOAT_EQ(pnt.x, 0.0f);
	EXPECT_FLOAT_EQ(pnt.y, 3.0f);
	EXPECT_FLOAT_EQ(pnt.z, 0.0f);

	EXPECT_FLOAT_EQ(res.x, 1.0f);
	EXPECT_FLOAT_EQ(res.y, 3.0f);
	EXPECT_FLOAT_EQ(res.z, 0.0f);
}

TEST(npNarrowPhase, AABB_AABB) {
	npAABB a1(npVector3<npReal>(2, 2, 4), 1.0f, 2.0f, 4.0f);
	npAABB a2(npVector3<npReal>(4, -2, 11), 1.0f, 1.0f, 1.0f);
	int r1 = TestAABB_AABB(a1, a2); //don't collide

	EXPECT_FLOAT_EQ(a1.c.x, 2.0f);
	EXPECT_FLOAT_EQ(a1.c.y, 2.0f);
	EXPECT_FLOAT_EQ(a1.c.z, 4.0f);
	EXPECT_FLOAT_EQ(a1.halfX, 1.0f);
	EXPECT_FLOAT_EQ(a1.halfY, 2.0f);
	EXPECT_FLOAT_EQ(a1.halfZ, 4.0f);

	EXPECT_FLOAT_EQ(a2.c.x, 4.0f);
	EXPECT_FLOAT_EQ(a2.c.y, -2.0f);
	EXPECT_FLOAT_EQ(a2.c.z, 11.0f);
	EXPECT_FLOAT_EQ(a2.halfX, 1.0f);
	EXPECT_FLOAT_EQ(a2.halfY, 1.0f);
	EXPECT_FLOAT_EQ(a2.halfZ, 1.0f);

	EXPECT_EQ(r1, 0.0f);

	a2 = npAABB(npVector3<npReal>(0, 1, 3), 2.0f, 3.0f, 3.0f);
	r1 = TestAABB_AABB(a1, a2); //collide

	EXPECT_EQ(r1, 1.0f);
}

TEST(npNarrowPhase, TestSphere_AABB) {
	npAABB a1(npVector3<npReal>(2.0f, 2.0f, 4.0f), 1.0f, 2.0f, 4.0f);
	npSphere s1(npVector3<npReal>(15.0f, 15.0f, 15.0f), 2.0f);
	int r1 = TestSphere_AABB(s1, a1); //don't collide

	EXPECT_FLOAT_EQ(s1.c.x, 15.0f);
	EXPECT_FLOAT_EQ(s1.c.y, 15.0f);
	EXPECT_FLOAT_EQ(s1.c.z, 15.0f);
	EXPECT_FLOAT_EQ(s1.r, 2.0f);

	EXPECT_FLOAT_EQ(a1.c.x, 2.0f);
	EXPECT_FLOAT_EQ(a1.c.y, 2.0f);
	EXPECT_FLOAT_EQ(a1.c.z, 4.0f);
	EXPECT_FLOAT_EQ(a1.halfX, 1.0f);
	EXPECT_FLOAT_EQ(a1.halfY, 2.0f);
	EXPECT_FLOAT_EQ(a1.halfZ, 4.0f);

	EXPECT_EQ(r1, 0);

	s1 = npSphere(npVector3<npReal>(3, 3, 3), 2.5f);
	r1 = TestSphere_AABB(s1, a1); //collide

	EXPECT_EQ(r1, 1);
}

TEST(npNarrowPhase, TestSphere_Sphere) {
	npSphere s1(npVector3<npReal>(0, 0, 0), 2.0f);
	npSphere s2(npVector3<npReal>(4, 4, 4), 0.5f);
	bool r1 = TestSphere_Sphere(s1, s2); //don't collide

	EXPECT_FLOAT_EQ(s1.c.x, 0.0f);
	EXPECT_FLOAT_EQ(s1.c.y, 0.0f);
	EXPECT_FLOAT_EQ(s1.c.z, 0.0f);
	EXPECT_FLOAT_EQ(s1.r, 2.0f);

	EXPECT_FLOAT_EQ(s2.c.x, 4.0f);
	EXPECT_FLOAT_EQ(s2.c.y, 4.0f);
	EXPECT_FLOAT_EQ(s2.c.z, 4.0f);
	EXPECT_FLOAT_EQ(s2.r, 0.5f);

	EXPECT_FALSE(r1, 2);

	npSphere s3 = npSphere(npVector3<npReal>(3, 3, 3), 2.5f);
	int r2 = TestSphere_Sphere(s2, s3); //collide

	EXPECT_TRUE(r2);
}
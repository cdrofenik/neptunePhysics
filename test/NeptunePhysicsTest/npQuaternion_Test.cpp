#include "gtest\gtest.h"

#include "neptunePhysics/math/npQuaternion.h"

using namespace NeptunePhysics;

TEST(npQuaternionTest, CONSTRUCTOR) {

	npQuarternion a(4, 1, 2, 3);
	EXPECT_FLOAT_EQ(a.r, 4);
	EXPECT_FLOAT_EQ(a.i, 1);
	EXPECT_FLOAT_EQ(a.j, 2);
	EXPECT_FLOAT_EQ(a.k, 3);
}

TEST(npQuaternionTest, NORMALIZE) {

	npQuarternion a(2, 2, 4, 3);
	EXPECT_FLOAT_EQ(a.r, 2);
	EXPECT_FLOAT_EQ(a.i, 2);
	EXPECT_FLOAT_EQ(a.j, 4);
	EXPECT_FLOAT_EQ(a.k, 3);

	a.normalize();
	EXPECT_NEAR(0.001, a.r, 0.348f);
	EXPECT_NEAR(0.001, a.i, 0.348f);
	EXPECT_NEAR(0.001, a.j, 0.696f);
	EXPECT_NEAR(0.001, a.k, 0.522f);
}

TEST(npQuaternionTest, MULTIPLY) {

	npQuarternion a(4, 1, 2, 3);
	EXPECT_FLOAT_EQ(a.r, 4);
	EXPECT_FLOAT_EQ(a.i, 1);
	EXPECT_FLOAT_EQ(a.j, 2);
	EXPECT_FLOAT_EQ(a.k, 3);

	npQuarternion b(3, 1, 3, 2);
	EXPECT_FLOAT_EQ(b.r, 3);
	EXPECT_FLOAT_EQ(b.i, 1);
	EXPECT_FLOAT_EQ(b.j, 3);
	EXPECT_FLOAT_EQ(b.k, 2);

	a *= b;

	EXPECT_FLOAT_EQ(b.r, 3);
	EXPECT_FLOAT_EQ(b.i, 1);
	EXPECT_FLOAT_EQ(b.j, 3);
	EXPECT_FLOAT_EQ(b.k, 2);

	EXPECT_FLOAT_EQ(a.r, -1);
	EXPECT_FLOAT_EQ(a.i, 2);
	EXPECT_FLOAT_EQ(a.j, 19);
	EXPECT_FLOAT_EQ(a.k, 18);
}

TEST(npQuaternionTest, ROTATE_BY_VECTOR) {

	npQuarternion a(4, 1, 2, 3);
	EXPECT_FLOAT_EQ(a.r, 4);
	EXPECT_FLOAT_EQ(a.i, 1);
	EXPECT_FLOAT_EQ(a.j, 2);
	EXPECT_FLOAT_EQ(a.k, 3);

	npVector3r b(3, 2, 3);

	EXPECT_FLOAT_EQ(b.x, 3);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 3);

	a.rotateByVector(b);

	EXPECT_FLOAT_EQ(b.x, 3);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 3);

	EXPECT_FLOAT_EQ(a.r, -16);
	EXPECT_FLOAT_EQ(a.i, 12);
	EXPECT_FLOAT_EQ(a.j, 14);
	EXPECT_FLOAT_EQ(a.k, 8);
}

TEST(npQuaternionTest, ADD_SCALED_VECTOR) {

	npQuarternion a(4, 1, 2, 3);
	EXPECT_FLOAT_EQ(a.r, 4);
	EXPECT_FLOAT_EQ(a.i, 1);
	EXPECT_FLOAT_EQ(a.j, 2);
	EXPECT_FLOAT_EQ(a.k, 3);

	npVector3r b(3, 2, 3);

	EXPECT_FLOAT_EQ(b.x, 3);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 3);

	a.addScaledVector(b, 4);

	EXPECT_FLOAT_EQ(b.x, 3);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 3);

	EXPECT_FLOAT_EQ(a.r, -28);
	EXPECT_FLOAT_EQ(a.i, 25);
	EXPECT_FLOAT_EQ(a.j, 6);
	EXPECT_FLOAT_EQ(a.k, 35);
}
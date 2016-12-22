#include "gtest\gtest.h"

#include "neptunePhysics/math/npPrecision.hpp"
#include "neptunePhysics/math/npVector3.hpp"

using namespace NeptunePhysics;

TEST(npVector3Test, ADDITION) {

	npVector3r a(1, 1, 1);
	npVector3r b(2, 2, 2);
	npVector3r c = a + b;

	EXPECT_FLOAT_EQ(a.x, 1);
	EXPECT_FLOAT_EQ(a.y, 1);
	EXPECT_FLOAT_EQ(a.z, 1);

	EXPECT_FLOAT_EQ(b.x, 2);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 2);

	EXPECT_FLOAT_EQ(c.x, 3);
	EXPECT_FLOAT_EQ(c.y, 3);
	EXPECT_FLOAT_EQ(c.z, 3);

	c += a;

	EXPECT_FLOAT_EQ(a.x, 1);
	EXPECT_FLOAT_EQ(a.y, 1);
	EXPECT_FLOAT_EQ(a.z, 1);

	EXPECT_FLOAT_EQ(c.x, 4);
	EXPECT_FLOAT_EQ(c.y, 4);
	EXPECT_FLOAT_EQ(c.z, 4);
}

TEST(npVector3Test, SUBTRACTION) {

	npVector3r a(5, 5, 5);
	npVector3r b(2, 2, 2);
	npVector3r c = a - b;

	EXPECT_FLOAT_EQ(a.x, 5);
	EXPECT_FLOAT_EQ(a.y, 5);
	EXPECT_FLOAT_EQ(a.z, 5);

	EXPECT_FLOAT_EQ(b.x, 2);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 2);

	EXPECT_FLOAT_EQ(c.x, 3);
	EXPECT_FLOAT_EQ(c.y, 3);
	EXPECT_FLOAT_EQ(c.z, 3);

	c -= a;

	EXPECT_FLOAT_EQ(a.x, 5);
	EXPECT_FLOAT_EQ(a.y, 5);
	EXPECT_FLOAT_EQ(a.z, 5);

	EXPECT_FLOAT_EQ(c.x, -2);
	EXPECT_FLOAT_EQ(c.y, -2);
	EXPECT_FLOAT_EQ(c.z, -2);
}

TEST(npVector3Test, SCALAR_MULTIPLICATION) {

	npReal sc = 0.25f;
	npVector3r a(5, 5, 5);
	npVector3r c = a * sc;

	EXPECT_FLOAT_EQ(a.x, 5);
	EXPECT_FLOAT_EQ(a.y, 5);
	EXPECT_FLOAT_EQ(a.z, 5);

	EXPECT_FLOAT_EQ(sc, 0.25f);

	EXPECT_FLOAT_EQ(c.x, 1.25f);
	EXPECT_FLOAT_EQ(c.y, 1.25f);
	EXPECT_FLOAT_EQ(c.z, 1.25f);

	c *= sc;

	EXPECT_FLOAT_EQ(sc, 0.25f);

	EXPECT_FLOAT_EQ(c.x, 0.3125f);
	EXPECT_FLOAT_EQ(c.y, 0.3125f);
	EXPECT_FLOAT_EQ(c.z, 0.3125f);

	npVector3r t1;
	EXPECT_FLOAT_EQ(t1.x, 0.0f);
	EXPECT_FLOAT_EQ(t1.y, 0.0f);
	EXPECT_FLOAT_EQ(t1.z, 0.0f);

	npVector3r t2(0.0, 1.0, 0.0);
	t2 = (npVector3r)(t2 * 0.023f) * 0.01f;
	EXPECT_FLOAT_EQ(t2.x, 0.0f);
	EXPECT_FLOAT_EQ(t2.y, 0.00023f);
	EXPECT_FLOAT_EQ(t2.z, 0.0f);

}

TEST(npVector3Test, VECTOR_MULTIPLICATION) {

	npVector3r a(5, 4, 3);
	npVector3r b(2, 1, 8);
	npVector3r c = a % b;

	EXPECT_FLOAT_EQ(a.x, 5);
	EXPECT_FLOAT_EQ(a.y, 4);
	EXPECT_FLOAT_EQ(a.z, 3);

	EXPECT_FLOAT_EQ(b.x, 2);
	EXPECT_FLOAT_EQ(b.y, 1);
	EXPECT_FLOAT_EQ(b.z, 8);

	EXPECT_FLOAT_EQ(c.x, 29);
	EXPECT_FLOAT_EQ(c.y, -34);
	EXPECT_FLOAT_EQ(c.z, -3);

	c %= b;

	EXPECT_FLOAT_EQ(b.x, 2);
	EXPECT_FLOAT_EQ(b.y, 1);
	EXPECT_FLOAT_EQ(b.z, 8);

	EXPECT_FLOAT_EQ(c.x, -269);
	EXPECT_FLOAT_EQ(c.y, -238);
	EXPECT_FLOAT_EQ(c.z, 97);
}

TEST(npVector3Test, VECTOR_VECTOR_TO_SCALAR) {

	npVector3r a(5, 4, 3);
	npVector3r b(2, 1, 8);
	npReal c = a * b;

	EXPECT_FLOAT_EQ(a.x, 5);
	EXPECT_FLOAT_EQ(a.y, 4);
	EXPECT_FLOAT_EQ(a.z, 3);

	EXPECT_FLOAT_EQ(b.x, 2);
	EXPECT_FLOAT_EQ(b.y, 1);
	EXPECT_FLOAT_EQ(b.z, 8);

	EXPECT_FLOAT_EQ(c, 38);
}

TEST(npVector3Test, COMPONENT_UPDATE) {

	npVector3r a(5, 4, 3);
	npVector3r b(2, 1, 8);
	a.componentProductUpdate(b);

	EXPECT_FLOAT_EQ(a.x, 10);
	EXPECT_FLOAT_EQ(a.y, 4);
	EXPECT_FLOAT_EQ(a.z, 24);

	EXPECT_FLOAT_EQ(b.x, 2);
	EXPECT_FLOAT_EQ(b.y, 1);
	EXPECT_FLOAT_EQ(b.z, 8);
}

TEST(npVector3Test, ADD_SCALER_VECTOR) {

	npVector3r a(5, 4, 3);
	npVector3r b(2, 1, 8);
	npReal c = 2;
	a.addScaledVector(b, c);

	EXPECT_FLOAT_EQ(a.x, 9);
	EXPECT_FLOAT_EQ(a.y, 6);
	EXPECT_FLOAT_EQ(a.z, 19);

	EXPECT_FLOAT_EQ(b.x, 2);
	EXPECT_FLOAT_EQ(b.y, 1);
	EXPECT_FLOAT_EQ(b.z, 8);

	EXPECT_FLOAT_EQ(c, 2);
}

TEST(npVector3Test, SQUARE_LENGTH) {

	npVector3r a(5, 4, 3);
	npReal r = a.squareLength();

	EXPECT_FLOAT_EQ(a.x, 5);
	EXPECT_FLOAT_EQ(a.y, 4);
	EXPECT_FLOAT_EQ(a.z, 3);

	EXPECT_FLOAT_EQ(r, 50);
}

TEST(npVector3Test, LENGTH) {

	npVector3r a(5, 4, 3);
	npReal r = a.length();

	EXPECT_FLOAT_EQ(a.x, 5);
	EXPECT_FLOAT_EQ(a.y, 4);
	EXPECT_FLOAT_EQ(a.z, 3);

	EXPECT_FLOAT_EQ(r, 7.0710678f);
}

TEST(npVector3Test, INVERT) {

	npVector3r a(5, 4, 3);
	a.invert();

	EXPECT_FLOAT_EQ(a.x, -5);
	EXPECT_FLOAT_EQ(a.y, -4);
	EXPECT_FLOAT_EQ(a.z, -3);
}

TEST(npVector3Test, NORMALIZE) {

	npVector3r a(5, 4, 3);
	a.normalize();

	EXPECT_FLOAT_EQ(a.x, 0.70710677f);
	EXPECT_FLOAT_EQ(a.y, 0.56568545f);
	EXPECT_FLOAT_EQ(a.z, 0.42426407f);
}

TEST(npVector3Test, GET_ANGLE_FROM_TWO_VECTORS) {

	npVector3r a1(1, 0, 0);
	npVector3r a2(1, 1, 0);
	npVector3r a3(0, 1, 0);
	npReal r = a1.angle(a3);

	EXPECT_FLOAT_EQ(a1.x, 1.0f);
	EXPECT_FLOAT_EQ(a1.y, 0.0f);
	EXPECT_FLOAT_EQ(a1.z, 0.0f);

	EXPECT_FLOAT_EQ(a3.x, 0.0f);
	EXPECT_FLOAT_EQ(a3.y, 1.0f);
	EXPECT_FLOAT_EQ(a3.z, 0.0f);

	EXPECT_FLOAT_EQ(90.0f, r);

	r = a1.angle(a2);

	EXPECT_FLOAT_EQ(a1.x, 1.0f);
	EXPECT_FLOAT_EQ(a1.y, 0.0f);
	EXPECT_FLOAT_EQ(a1.z, 0.0f);

	EXPECT_FLOAT_EQ(a2.x, 1.0f);
	EXPECT_FLOAT_EQ(a2.y, 1.0f);
	EXPECT_FLOAT_EQ(a2.z, 0.0f);

	EXPECT_FLOAT_EQ(45.0f, r);
}
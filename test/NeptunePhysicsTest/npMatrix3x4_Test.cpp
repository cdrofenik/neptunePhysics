#include "gtest\gtest.h"

#include "neptunePhysics/math/npVector3.hpp"
#include "neptunePhysics/math/npMatrix3x4.hpp"

using namespace NeptunePhysics;

TEST(npMatrix3x4Test, SINGLE_VARIABLE_CONSTRUCTOR) {

	npMatrix3x4 a(3);

	EXPECT_FLOAT_EQ(a.m[0], 3);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);
	EXPECT_FLOAT_EQ(a.m[3], 0);

	EXPECT_FLOAT_EQ(a.m[4], 0);
	EXPECT_FLOAT_EQ(a.m[5], 3);
	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);

	EXPECT_FLOAT_EQ(a.m[8], 0);
	EXPECT_FLOAT_EQ(a.m[9], 0);
	EXPECT_FLOAT_EQ(a.m[10], 3);
	EXPECT_FLOAT_EQ(a.m[11], 0);
}

TEST(npMatrix3x4Test, FULL_VARIABLE_CONSTRUCTOR) {

	npMatrix3x4 a(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3);

	EXPECT_FLOAT_EQ(a.m[0], 3);
	EXPECT_FLOAT_EQ(a.m[1], 3);
	EXPECT_FLOAT_EQ(a.m[2], 3);
	EXPECT_FLOAT_EQ(a.m[3], 3);

	EXPECT_FLOAT_EQ(a.m[4], 3);
	EXPECT_FLOAT_EQ(a.m[5], 3);
	EXPECT_FLOAT_EQ(a.m[6], 3);
	EXPECT_FLOAT_EQ(a.m[7], 3);

	EXPECT_FLOAT_EQ(a.m[8], 3);
	EXPECT_FLOAT_EQ(a.m[9], 3);
	EXPECT_FLOAT_EQ(a.m[10], 3);
	EXPECT_FLOAT_EQ(a.m[11], 3);
}

TEST(npMatrix3x4Test, MULTIPLICATION) {

	npMatrix3x4 a, c(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
		b(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3);
	a = c * b;

	EXPECT_FLOAT_EQ(a.m[0], 9);
	EXPECT_FLOAT_EQ(a.m[1], 9);
	EXPECT_FLOAT_EQ(a.m[2], 9);
	EXPECT_FLOAT_EQ(a.m[3], 10);

	EXPECT_FLOAT_EQ(a.m[4], 9);
	EXPECT_FLOAT_EQ(a.m[5], 9);
	EXPECT_FLOAT_EQ(a.m[6], 9);
	EXPECT_FLOAT_EQ(a.m[7], 10);

	EXPECT_FLOAT_EQ(a.m[8], 9);
	EXPECT_FLOAT_EQ(a.m[9], 9);
	EXPECT_FLOAT_EQ(a.m[10], 9);
	EXPECT_FLOAT_EQ(a.m[11], 10);

	EXPECT_FLOAT_EQ(b.m[0], 3);
	EXPECT_FLOAT_EQ(b.m[1], 3);
	EXPECT_FLOAT_EQ(b.m[2], 3);
	EXPECT_FLOAT_EQ(b.m[3], 3);

	EXPECT_FLOAT_EQ(b.m[4], 3);
	EXPECT_FLOAT_EQ(b.m[5], 3);
	EXPECT_FLOAT_EQ(b.m[6], 3);
	EXPECT_FLOAT_EQ(b.m[7], 3);

	EXPECT_FLOAT_EQ(b.m[8], 3);
	EXPECT_FLOAT_EQ(b.m[9], 3);
	EXPECT_FLOAT_EQ(b.m[10], 3);
	EXPECT_FLOAT_EQ(b.m[11], 3);

	EXPECT_FLOAT_EQ(c.m[0], 1);
	EXPECT_FLOAT_EQ(c.m[1], 1);
	EXPECT_FLOAT_EQ(c.m[2], 1);
	EXPECT_FLOAT_EQ(c.m[3], 1);

	EXPECT_FLOAT_EQ(c.m[4], 1);
	EXPECT_FLOAT_EQ(c.m[5], 1);
	EXPECT_FLOAT_EQ(c.m[6], 1);
	EXPECT_FLOAT_EQ(c.m[7], 1);

	EXPECT_FLOAT_EQ(c.m[8], 1);
	EXPECT_FLOAT_EQ(c.m[9], 1);
	EXPECT_FLOAT_EQ(c.m[10], 1);
	EXPECT_FLOAT_EQ(c.m[11], 1);

	c *= b;

	EXPECT_FLOAT_EQ(b.m[0], 3);
	EXPECT_FLOAT_EQ(b.m[1], 3);
	EXPECT_FLOAT_EQ(b.m[2], 3);
	EXPECT_FLOAT_EQ(b.m[3], 3);

	EXPECT_FLOAT_EQ(b.m[4], 3);
	EXPECT_FLOAT_EQ(b.m[5], 3);
	EXPECT_FLOAT_EQ(b.m[6], 3);
	EXPECT_FLOAT_EQ(b.m[7], 3);

	EXPECT_FLOAT_EQ(b.m[8], 3);
	EXPECT_FLOAT_EQ(b.m[9], 3);
	EXPECT_FLOAT_EQ(b.m[10], 3);
	EXPECT_FLOAT_EQ(b.m[11], 3);

	EXPECT_FLOAT_EQ(c.m[0], 9);
	EXPECT_FLOAT_EQ(c.m[1], 9);
	EXPECT_FLOAT_EQ(c.m[2], 9);
	EXPECT_FLOAT_EQ(c.m[3], 10);

	EXPECT_FLOAT_EQ(c.m[4], 9);
	EXPECT_FLOAT_EQ(c.m[5], 9);
	EXPECT_FLOAT_EQ(c.m[6], 9);
	EXPECT_FLOAT_EQ(c.m[7], 10);

	EXPECT_FLOAT_EQ(c.m[8], 9);
	EXPECT_FLOAT_EQ(c.m[9], 9);
	EXPECT_FLOAT_EQ(c.m[10], 9);
	EXPECT_FLOAT_EQ(c.m[11], 10);
}

TEST(npMatrix3x4Test, VECTOR_MULTIPLICATION) {

	npVector3r c, b(1, 2, 3);
	npMatrix3x4 a(1, 1, 2, 3, 1, 1, 1, 11, 1, 3, 1, 3);
	c = a * b;

	EXPECT_FLOAT_EQ(c.x, 12);
	EXPECT_FLOAT_EQ(c.y, 17);
	EXPECT_FLOAT_EQ(c.z, 13);

	EXPECT_FLOAT_EQ(b.x, 1);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 3);

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 1);
	EXPECT_FLOAT_EQ(a.m[2], 2);
	EXPECT_FLOAT_EQ(a.m[3], 3);

	EXPECT_FLOAT_EQ(a.m[4], 1);
	EXPECT_FLOAT_EQ(a.m[5], 1);
	EXPECT_FLOAT_EQ(a.m[6], 1);
	EXPECT_FLOAT_EQ(a.m[7], 11);

	EXPECT_FLOAT_EQ(a.m[8], 1);
	EXPECT_FLOAT_EQ(a.m[9], 3);
	EXPECT_FLOAT_EQ(a.m[10], 1);
	EXPECT_FLOAT_EQ(a.m[11], 3);

	c = a.transform(b);

	EXPECT_FLOAT_EQ(c.x, 12);
	EXPECT_FLOAT_EQ(c.y, 17);
	EXPECT_FLOAT_EQ(c.z, 13);

	EXPECT_FLOAT_EQ(b.x, 1);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 3);
}

TEST(npMatrix3x4Test, DETERMINANT) {

	npMatrix3x4 a(1, 2, 3, 9, 8, 11, 3, 3, 5, 4, 3, 1);
	npReal value = a.getDeterminant();

	EXPECT_FLOAT_EQ(value, -66);

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 2);
	EXPECT_FLOAT_EQ(a.m[2], 3);
	EXPECT_FLOAT_EQ(a.m[3], 9);

	EXPECT_FLOAT_EQ(a.m[4], 8);
	EXPECT_FLOAT_EQ(a.m[5], 11);
	EXPECT_FLOAT_EQ(a.m[6], 3);
	EXPECT_FLOAT_EQ(a.m[7], 3);

	EXPECT_FLOAT_EQ(a.m[8], 5);
	EXPECT_FLOAT_EQ(a.m[9], 4);
	EXPECT_FLOAT_EQ(a.m[10], 3);
	EXPECT_FLOAT_EQ(a.m[11], 1);
}

TEST(npMatrix3x4Test, INVERSE) {
	npMatrix3x4 a(1, 0, 9, -4, 2, -1, -2, 7, 0, 1, 3, -3);
	npReal value = a.getDeterminant();
	a.invert();

	EXPECT_FLOAT_EQ(value, 17);

	EXPECT_FLOAT_EQ(a.m[0], -0.05882353f);
	EXPECT_FLOAT_EQ(a.m[1], 0.52941179f);
	EXPECT_FLOAT_EQ(a.m[2], 0.52941179f);
	EXPECT_FLOAT_EQ(a.m[3], -2.3529413f);

	EXPECT_FLOAT_EQ(a.m[4], -0.35294119f);
	EXPECT_FLOAT_EQ(a.m[5], 0.17647059f);
	EXPECT_FLOAT_EQ(a.m[6], 1.1764706f);
	EXPECT_FLOAT_EQ(a.m[7], -0.88235295f);

	EXPECT_FLOAT_EQ(a.m[8], 0.11764706f);
	EXPECT_FLOAT_EQ(a.m[9], 0.05882353f);
	EXPECT_FLOAT_EQ(a.m[10], 0.05882353f);
	EXPECT_FLOAT_EQ(a.m[11], 0.70588237f);

	npMatrix3x4 b, c(1, 2, 2, 3,
		4, 5, 11, 5,
		1, 4, 4, 3);
	npReal value2 = c.getDeterminant();
	b = c.inverse();

	EXPECT_FLOAT_EQ(value2, -12);

	EXPECT_FLOAT_EQ(b.m[0], 2);
	EXPECT_FLOAT_EQ(b.m[1], 0);
	EXPECT_FLOAT_EQ(b.m[2], -1);
	EXPECT_FLOAT_EQ(b.m[3], -3);

	EXPECT_FLOAT_EQ(b.m[4], 0.41666669f);
	EXPECT_FLOAT_EQ(b.m[5], -0.16666667f);
	EXPECT_FLOAT_EQ(b.m[6], 0.25f);
	EXPECT_FLOAT_EQ(b.m[7], 1.1666667f);

	EXPECT_FLOAT_EQ(b.m[8], -0.91666669f);
	EXPECT_FLOAT_EQ(b.m[9], -0.5f);
	EXPECT_FLOAT_EQ(b.m[10], 1.0833334f);
	EXPECT_FLOAT_EQ(b.m[11], 1.1666667f);
}

TEST(npMatrix3x4Test, SET_ORIENTATION) {
	npMatrix3x4 a(1, 0, 9, -4, 2, -1, -2, 7, 0, 1, 3, -3);
	npQuarternion q(4, 0.5f, 1, 0.7f);
	npVector3r translation(1, 2, 3);

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 9);
	EXPECT_FLOAT_EQ(a.m[3], -4);

	EXPECT_FLOAT_EQ(a.m[4], 2);
	EXPECT_FLOAT_EQ(a.m[5], -1);
	EXPECT_FLOAT_EQ(a.m[6], -2);
	EXPECT_FLOAT_EQ(a.m[7], 7);

	EXPECT_FLOAT_EQ(a.m[8], 0);
	EXPECT_FLOAT_EQ(a.m[9], 1);
	EXPECT_FLOAT_EQ(a.m[10], 3);
	EXPECT_FLOAT_EQ(a.m[11], -3);

	EXPECT_FLOAT_EQ(q.r, 4);
	EXPECT_FLOAT_EQ(q.i, 0.5);
	EXPECT_FLOAT_EQ(q.j, 1);
	EXPECT_FLOAT_EQ(q.k, 0.7f);

	a.setOrientation(q, translation);

	EXPECT_FLOAT_EQ(a.m[0], -1.98f);
	EXPECT_FLOAT_EQ(a.m[1], 6.5999999f);
	EXPECT_FLOAT_EQ(a.m[2], -7.3000002f);

	EXPECT_FLOAT_EQ(a.m[3], 1);

	EXPECT_FLOAT_EQ(a.m[4], -4.5999999f);
	EXPECT_FLOAT_EQ(a.m[5], -0.48000002f);
	EXPECT_FLOAT_EQ(a.m[6], 5.4000001f);

	EXPECT_FLOAT_EQ(a.m[7], 2);

	EXPECT_FLOAT_EQ(a.m[8], 8.6999998f);
	EXPECT_FLOAT_EQ(a.m[9], -2.5999999f);
	EXPECT_FLOAT_EQ(a.m[10], -1.5f);

	EXPECT_FLOAT_EQ(a.m[11], 3);

	EXPECT_FLOAT_EQ(q.r, 4);
	EXPECT_FLOAT_EQ(q.i, 0.5);
	EXPECT_FLOAT_EQ(q.j, 1);
	EXPECT_FLOAT_EQ(q.k, 0.7f);
}

TEST(npMatrix3x4Test, TRANSFORM_INVERSE) {

	//za 3x3 matriko uporabi realna stevila za rotacijske vrednosti
	npMatrix3x4 a(1, 0, 9, -4, 2, -1, -2, 7, 0, 1, 3, -3);
	npVector3r translation(1, 2, 3);

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 9);
	EXPECT_FLOAT_EQ(a.m[3], -4);

	EXPECT_FLOAT_EQ(a.m[4], 2);
	EXPECT_FLOAT_EQ(a.m[5], -1);
	EXPECT_FLOAT_EQ(a.m[6], -2);
	EXPECT_FLOAT_EQ(a.m[7], 7);

	EXPECT_FLOAT_EQ(a.m[8], 0);
	EXPECT_FLOAT_EQ(a.m[9], 1);
	EXPECT_FLOAT_EQ(a.m[10], 3);
	EXPECT_FLOAT_EQ(a.m[11], -3);

	EXPECT_FLOAT_EQ(translation.x, 1);
	EXPECT_FLOAT_EQ(translation.y, 2);
	EXPECT_FLOAT_EQ(translation.z, 3);

	npVector3r c = a.transformInverse(translation);

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 9);
	EXPECT_FLOAT_EQ(a.m[3], -4);

	EXPECT_FLOAT_EQ(a.m[4], 2);
	EXPECT_FLOAT_EQ(a.m[5], -1);
	EXPECT_FLOAT_EQ(a.m[6], -2);
	EXPECT_FLOAT_EQ(a.m[7], 7);

	EXPECT_FLOAT_EQ(a.m[8], 0);
	EXPECT_FLOAT_EQ(a.m[9], 1);
	EXPECT_FLOAT_EQ(a.m[10], 3);
	EXPECT_FLOAT_EQ(a.m[11], -3);

	EXPECT_FLOAT_EQ(a.m[8], 0);
	EXPECT_FLOAT_EQ(a.m[9], 1);
	EXPECT_FLOAT_EQ(a.m[10], 3);
	EXPECT_FLOAT_EQ(a.m[11], -3);

	EXPECT_FLOAT_EQ(translation.x, 1);
	EXPECT_FLOAT_EQ(translation.y, 2);
	EXPECT_FLOAT_EQ(translation.z, 3);

	EXPECT_FLOAT_EQ(c.x, 5);
	EXPECT_FLOAT_EQ(c.y, 1);
	EXPECT_FLOAT_EQ(c.z, 14);

}